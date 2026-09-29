# 🛠️ Qualcomm CamX & CHI: `configure_streams` Deep Dive

> **Reference Repositories:**
> - [CamX Source Tree (11se)](https://github.com/comprehensive9/vendor_qcom_proprietary/tree/11se/camx)
> - [CHI-CDK Source Tree (11se)](https://github.com/comprehensive9/vendor_qcom_proprietary/tree/11se/chi-cdk)

---

## 📑 Table of Contents
1. [Overview & Role in Android Camera HAL3](#1-overview--role-in-android-camera-hal3)
2. [Key Source Files & Locations](#2-key-source-files--locations)
3. [End-to-End Function Call Stack (ASCII Sequence Flow)](#3-end-to-end-function-call-stack-ascii-sequence-flow)
4. [Step-by-Step Execution Breakdown](#4-step-by-step-execution-breakdown)
   - [Phase 1: Entry & Stream Classification](#phase-1-entry--stream-classification)
   - [Phase 2: Usecase Selection (XML Matching)](#phase-2-usecase-selection-xml-matching)
   - [Phase 3: Feature Graph Construction (Feature2 Engine)](#phase-3-feature-graph-construction-feature2-engine)
   - [Phase 4: CamX Session & Pipeline Instantiation](#phase-4-camx-session--pipeline-instantiation)
   - [Phase 5: Node Creation & Port Linking](#phase-5-node-creation--port-linking)
   - [Phase 6: Memory & Buffer Pool Setup (ION/SMMU)](#phase-6-memory--buffer-pool-setup-ionsmmu)
   - [Phase 7: Sensor Mode Selection & CSL HW Init](#phase-7-sensor-mode-selection--csl-hw-init)
5. [Core Data Structures Map](#5-core-data-structures-map)
6. [Real-World Code Trace Example](#6-real-world-code-trace-example)
7. [⏱️ 1-Minute Quick Revision](#7-️-1-minute-quick-revision)

---

## 1. Overview & Role in Android Camera HAL3

When an Android application opens a camera and configures camera output surfaces (e.g. `SurfaceView` for Preview, `MediaRecorder` for Video, `ImageReader` for JPEG/RAW), Android CameraService calls `ICameraDeviceSession::configureStreams()`.

In the Qualcomm CamX/CHI architecture, `configure_streams` is responsible for:
1. **Analyzing App Streams**: Formats, resolutions, rotation, usage flags, and dynamic framerates.
2. **Matching Usecase**: Picking the best topology from `camxusecases.xml` / `chiusecases.xml` (e.g., Preview+Video, ZSL Snapshot, Super Slow Motion, Dual Camera).
3. **Building Feature Graphs**: Integrating algorithmic features (HDR, MFNR, EIS, Bokeh).
4. **Instantiating Pipelines & Nodes**: Creating Hardware Nodes (`IFENode`, `BPSNode`, `IPENode`, `SensorNode`) and Software Nodes (`ChiNode`).
5. **Port Linking & Buffer Allocation**: Connecting Node Ports (wiring the DAG) and allocating internal intermediate scratch buffers in ION/DMA-BUF.
6. **Configuring Kernel HW via CSL**: Programming SMMU context banks and V4L2 subdevice pipelines.

---

## 2. Key Source Files & Locations

| Component | Source File Path | Key Functions / Classes |
| :--- | :--- | :--- |
| **HAL Entry** | `camx/src/core/camxhwdevice.cpp` | `HwDevice3::ConfigureStreams()` |
| **CHI Context** | `chi-cdk/core/chi/chi.cpp` | `ChiContext::ConfigureStreams()`, `ChiContext::CreatePipeline()` |
| **CHI Extension** | `chi-cdk/core/chiframework/chxextensioninterface.cpp` | `ExtensionModule::ConfigureStreams()` |
| **Usecase Selector** | `chi-cdk/core/chiframework/chxusecase.cpp`<br>`chi-cdk/core/chiframework/chxusecaseutils.cpp` | `Usecase::Create()`, `Usecase::SelectUsecase()`, `Usecase::Initialize()` |
| **Feature Graph** | `chi-cdk/core/chiframework/chxfeaturegraph.cpp`<br>`chi-cdk/core/chiframework/chxfeature2graphfactory.cpp` | `FeatureGraphFactory::Create()`, `FeatureGraph::Build()`, `FeatureGraph::Initialize()` |
| **CamX Session** | `camx/src/core/camxsession.cpp` | `Session::Create()`, `Session::Initialize()`, `Session::StreamOn()` |
| **CamX Pipeline** | `camx/src/core/camxpipeline.cpp` | `Pipeline::Create()`, `Pipeline::LinkNodes()`, `Pipeline::Finalize()` |
| **CamX Nodes** | `camx/src/core/camxnode.cpp`<br>`camx/src/core/camxnodeport.cpp` | `Node::Create()`, `Node::Initialize()`, `NodePort::Create()` |
| **HWL Nodes** | `camx/src/hwl/sensor/camxsensornode.cpp`<br>`camx/src/hwl/ife/camxifenode.cpp`<br>`camx/src/hwl/bps/camxbpsnode.cpp`<br>`camx/src/hwl/ipe/camxipenode.cpp` | Hardware-specific node construction, capability querying, and HW register programming. |
| **Buffer Management**| `camx/src/core/camxbufferpool.cpp`<br>`camx/src/core/camxbufferpoolmanager.cpp` | `BufferPoolManager::AllocateBuffers()`, `BufferPool::Create()` |
| **CSL Interface** | `camx/src/csl/camxcsl.cpp`<br>`camx/src/csl/camxcslhw.cpp` | `CSL::OpenContext()`, `CSL::MapBuffersToSmmu()`, `CSL::ConfigurePipeline()` |

---

## 3. End-to-End Function Call Stack (ASCII Sequence Flow)

```
Android CameraService (Framework)
 │
 └─> ICameraDeviceSession::configureStreams(camera3_stream_configuration_t* stream_list)
      │
      └─> [camxhwdevice.cpp] CamX::HwDevice3::ConfigureStreams()
           │
           └─> [chi.cpp] ChiContext::ConfigureStreams()
                │
                └─> [chxextensioninterface.cpp] ExtensionModule::ConfigureStreams()
                     │
                     ├─> Phase 1: [chxusecaseutils.cpp] UsecaseUtils::SelectUsecase()
                     │            Matches streams against XML definitions (Preview/Video/ZSL)
                     │
                     ├─> Phase 2: [chxusecase.cpp] Usecase::Create()
                     │            Instantiates specific usecase object (e.g. UsecaseZSL, UsecasePreview)
                     │
                     ├─> Phase 3: [chxfeature2graphfactory.cpp] FeatureGraphFactory::Create()
                     │            Builds Feature Graph (attaching HDR/MFNR/EIS/Bokeh nodes)
                     │
                     ├─> Phase 4: [chi.cpp] ChiContext::CreatePipeline()
                     │    │
                     │    └─> [camxsession.cpp] CamX::Session::Create()
                     │         │
                     │         └─> [camxpipeline.cpp] CamX::Pipeline::Create()
                     │              │
                     │              ├─> [camxnode.cpp] CamX::Node::Create()
                     │              │    ├── CamX::SensorNode::Create()
                     │              │    ├── CamX::IFENode::Create()
                     │              │    ├── CamX::BPSNode::Create()
                     │              │    └── CamX::IPENode::Create()
                     │              │
                     │              ├─> [camxpipeline.cpp] CamX::Pipeline::LinkNodes()
                     │              │    Connects OutPorts of upstream nodes to InPorts of downstream nodes
                     │              │
                     │              └─> [camxpipeline.cpp] CamX::Pipeline::Finalize()
                     │
                     ├─> Phase 5: [camxbufferpoolmanager.cpp] BufferPoolManager::AllocateInternalBuffers()
                     │            Allocates intermediate scratch buffers (RDI, Full-size YUV, DS4/DS16)
                     │
                     └─> Phase 6: [camxcsl.cpp] CamX::CSL::ConfigurePipeline()
                                  Programs SMMU pages, sets sensor mode, opens V4L2 streaming subdevs
```

---

## 4. Step-by-Step Execution Breakdown

### Phase 1: Entry & Stream Classification
1. Android CameraService sends `camera3_stream_configuration_t`:
   - Array of `camera3_stream_t*` pointers.
   - Stream attributes: `format` (`HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED`, `RAW10`, `BLOB`), `width`, `height`, `usage` flags.
2. `CamX::HwDevice3::ConfigureStreams()` wraps Android structs into `CHISTREAMCONFIG` structures for the CHI layer.

### Phase 2: Usecase Selection (XML Matching)
- **File**: `chi-cdk/core/chiframework/chxusecaseutils.cpp`
- **Method**: `UsecaseUtils::SelectUsecase()`
- **Mechanism**:
  - The engine reads XML files (`g_chiusecases.xml`, `camxusecases.xml`).
  - Evaluates matching rules based on:
    - Number of output streams.
    - Presence of RAW streams (indicates RAW/Pro Mode or Offline Reprocessing).
    - Presence of Video encoder flags (`GRALLOC_USAGE_HW_VIDEO_ENCODER`).
    - Max resolution / aspect ratio.
  - Matches to specific usecase IDs: `UsecaseId::Preview`, `UsecaseId::ZSL`, `UsecaseId::DualCameraPreviewVideo`, etc.

### Phase 3: Feature Graph Construction (Feature2 Engine)
- **File**: `chi-cdk/core/chiframework/chxfeature2graphfactory.cpp`
- **Mechanism**:
  - If features like HDR, MFNR, or SuperResolution are requested, the `FeatureGraph` engine splices feature nodes into the base pipeline.
  - Generates a **Pipeline Topology Descriptor**: a list of nodes, input/output port IDs, and dependency links.

```
 Base Preview Topology:
 [Sensor] ---> [IFE] ---> [IPE] ---> (Preview Surface)

 Feature Graph with HDR/MFNR:
 [Sensor] ---> [IFE] ---> [RAW Dump / DDR]
                            │
                            v
                         [BPS Node] ---> [IPE Node] ---> (Preview / Snapshot)

Where is HDR/MFNR graph here?  

```

### Phase 4: CamX Session & Pipeline Instantiation
- **File**: `camx/src/core/camxsession.cpp` & `camx/src/core/camxpipeline.cpp`
- **Mechanism**:
  - `Session::Create()` creates a container managing one or more pipelines.
  - Usually, two pipelines are created inside a Session:
    1. **Real-Time (RT) Pipeline**: Handles continuous live preview / video frames from the sensor.
    2. **Offline (Non-RT) Pipeline**: Handles memory-to-memory post-processing (e.g. RAW $\to$ BPS $\to$ IPE $\to$ JPEG).

### Phase 5: Node Creation & Port Linking
- **File**: `camx/src/core/camxpipeline.cpp`
- **Method**: `Pipeline::LinkNodes()`
- **Mechanism**:
  - Each Node advertises available Ports:
    - `IFENode`: `InPort_SensorRaw`, `OutPort_FullRaw`, `OutPort_FullYuv`, `OutPort_DS4`, `OutPort_Stats3A`.
    - `IPENode`: `InPort_FullYuv`, `OutPort_DisplayYuv`, `OutPort_VideoYuv`, `OutPort_FDYuv`.
  - `LinkNodes()` establishes buffer forwarding pointers and creates synchronization dependency handles between ports.

### Phase 6: Memory & Buffer Pool Setup (ION/SMMU)
- **File**: `camx/src/core/camxbufferpoolmanager.cpp`
- **Mechanism**:
  - For intra-pipeline transfers (e.g. IFE output $\to$ IPE input), internal buffers are needed.
  - CamX BufferPoolManager queries each node's format/stride alignment requirements.
  - Allocates contiguous memory blocks via ION / DMA-BUF.
  - Invokes `CSL::MapBuffersToSmmu()` so the ISP hardware MMU can access physical RAM pages directly without CPU involvement.

### Phase 7: Sensor Mode Selection & CSL HW Init
- **File**: `camx/src/hwl/sensor/camxsensornode.cpp` & `camx/src/csl/camxcsl.cpp`
- **Mechanism**:
  - Sensor driver queries sensor capability XML to select optimal sensor mode (resolution, binning, frame rate, MIPI lanes).
  - Programs sensor registers via I2C/CCI through CSL.
  - Powers on ISP clock domains (Titan IFE/IPE hardware clocks) and prepares V4L2 video device nodes for streaming.

---

## 5. Core Data Structures Map

```
+-------------------------------------------------------------------------+
|                  camera3_stream_configuration_t                         |
|  - uint32_t num_streams;                                                |
|  - camera3_stream_t** streams;                                          |
|  - uint32_t operation_mode;                                             |
+-------------------------------------------------------------------------+
                                    │ (Wrapped by HAL adapter)
                                    ▼
+-------------------------------------------------------------------------+
|                          CHISTREAMCONFIG                                |
|  - CHISTREAM* pStreams;                                                 |
|  - UINT numStreams;                                                     |
|  - CHICAMERAPROPERTY property;                                          |
+-------------------------------------------------------------------------+
                                    │ (Parsed into Pipeline creation)
                                    ▼
+-------------------------------------------------------------------------+
|                          CamX::PipelineInfo                             |
|  - CHAR pipelineName[64];                                               |
|  - UINT numNodes;                                                       |
|  - NodeInfo nodeInfoList[];                                             |
|  - PortLink linkList[];                                                 |
|  - BufferPool* pBufferPools[];                                          |
+-------------------------------------------------------------------------+
```

---

## 6. Real-World Code Trace Example

Here is a simplified pseudocode representation of what happens inside `ChiContext::ConfigureStreams()`:

```cpp
// Simplified representation of CHI configure_streams flow
CHIRESULT ChiContext::ConfigureStreams(
    CHISTREAMCONFIG* pStreamConfig,
    CHIDRIVERCONFIG* pDriverConfig) 
{
    // 1. Identify usecase
    UsecaseId usecaseId = UsecaseUtils::SelectUsecase(pStreamConfig);
    
    // 2. Instantiate Usecase object
    Usecase* pUsecase = Usecase::Create(usecaseId, pStreamConfig);
    
    // 3. Build Feature Graph
    FeatureGraph* pFeatureGraph = FeatureGraphFactory::Create(pStreamConfig, pUsecase);
    
    // 4. Create CamX Pipeline Definition
    CHIPIPELINECREATEINFO pipelineInfo = {};
    pFeatureGraph->GetPipelineCreateInfo(&pipelineInfo);
    
    // 5. Instantiate CamX Session and Pipeline
    CamX::Session* pSession = CamX::Session::Create();
    CamX::Pipeline* pPipeline = pSession->CreatePipeline(&pipelineInfo);
    
    // 6. Allocate internal buffer pools for nodes
    CamX::BufferPoolManager::GetInstance()->AllocateBuffers(pPipeline);
    
    // 7. Initialize CSL kernel context
    CamX::CSL::GetInstance()->ConfigurePipeline(pPipeline);
    
    return CHIRESULT_SUCCESS;
}
```

---

## 7. ⏱️ 1-Minute Quick Revision

- **Purpose**: Prepare camera HW, feature topologies, pipelines, and memory pools for active streaming.
- **Entry Point**: `HwDevice3::ConfigureStreams()` in `camx/src/core/camxhwdevice.cpp`.
- **Usecase Match**: `UsecaseUtils::SelectUsecase()` parses stream list against XML definitions in `chi-cdk/core/chiframework/chxusecaseutils.cpp`.
- **Feature Graph**: `FeatureGraphFactory::Create()` dynamically attaches HDR/MFNR/EIS sub-graphs into the pipeline.
- **Pipeline & Node Creation**: `CamX::Pipeline::Create()` instantiates `SensorNode`, `IFENode`, `BPSNode`, `IPENode` and calls `Pipeline::LinkNodes()` to bind ports into a DAG.
- **Memory Setup**: `BufferPoolManager` allocates intermediate zero-copy ION buffers and maps them to SMMU via CSL.
- **Hardware Init**: `SensorNode` sets optimal sensor mode (binning/fps) and powers up ISP hardware clock rails.
