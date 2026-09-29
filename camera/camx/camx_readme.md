# 📷 Qualcomm CamX & CHI Architecture Deep Dive

> **Reference Repositories:**
> - [CamX Source Tree (11se)](https://github.com/comprehensive9/vendor_qcom_proprietary/tree/11se/camx)
> - [CHI-CDK Source Tree (11se)](https://github.com/comprehensive9/vendor_qcom_proprietary/tree/11se/chi-cdk)

---

## 📑 Table of Contents
1. [Architecture Overview: CamX vs. CHI-CDK](#1-architecture-overview-camx-vs-chi-cdk)
2. [Layered Architecture & Component Stack](#2-layered-architecture--component-stack)
3. [Core HAL3 Lifecycle & Function Call Flows](#3-core-hal3-lifecycle--function-call-flows)
   - [3.1 configure_streams() Flow](#31-configure_streams-flow)
   - [3.2 process_capture_request() Flow](#32-process_capture_request-flow)
   - [3.3 process_capture_result() Flow](#33-process_capture_result-flow)
   - [3.4 flush() Flow](#34-flush-flow)
   - [3.5 close() Flow](#35-close-flow)
4. [Topology Management, Feature Graphs & Node Selection](#4-topology-management-feature-graphs--node-selection)
   - [4.1 Node, Port, Link & Pipeline Concept](#41-node-port-link--pipeline-concept)
   - [4.2 Core Hardware & Software Nodes](#42-core-hardware--software-nodes)
   - [4.3 Feature Graph Selection (Feature2 / Usecase Selection)](#43-feature-graph-selection-feature2--usecase-selection)
   - [4.4 Topology Real-Time vs Offline Pipelines (ASCII Diagrams)](#44-topology-real-time-vs-offline-pipelines)
5. [Buffer & Sync Management (Synx / Fences)](#5-buffer--sync-management-synx--fences)
6. [⏱️ 1-Minute Quick Revision](#6-️-1-minute-quick-revision)

---

## 1. Architecture Overview: CamX vs. CHI-CDK

Qualcomm introduced the **CamX-CHI** architecture starting in Snapdragon 845 (Titan ISP generation) to replace the legacy `mm-camera` monolithic HAL.

```
+-------------------------------------------------------------------------+
|                  Android Framework (CameraService)                      |
+-------------------------------------------------------------------------+
                                    | (HIDL / AIDL ICameraDevice@3.x)
                                    v
+-------------------------------------------------------------------------+
|                              CHI Layer                                  |
|  - chi-cdk/core/chi/chi.cpp (CHI Entry Points)                          |
|  - Usecase Selector (chi-cdk/core/chiframework/chxusecase.cpp)          |
|  - Feature Graphs (HDR, MFNR, Night, Bokeh, SuperResolution)           |
|  - Custom OEM / 3rd Party Algorithm Nodes (chxadvancedcameranode.cpp)   |
|  - CHI Override Engine (chxextensioninterface.cpp)                     |
+-------------------------------------------------------------------------+
                                    | (CamX <-> CHI CDK Interfaces)
                                    v
+-------------------------------------------------------------------------+
|                            CamX Core Engine                             |
|  - camx/src/core/camxhwdevice.cpp (HAL3 Device Adapter)                 |
|  - Session & Pipeline Engine (camxsession.cpp, camxpipeline.cpp)        |
|  - Node Engine (camxnode.cpp, camxnodeport.cpp)                         |
|  - Hardware Subsystem Nodes: IFE, BPS, IPE, EVA, FD, Sensor, JPEG       |
|  - Memory & Sync Engine (camxbufferpool.cpp, camxsyncmanager.cpp)       |
+-------------------------------------------------------------------------+
                                    | (IOCTL / Packet dispatch)
                                    v
+-------------------------------------------------------------------------+
|                 CSL (Camera System Library) & KMD                       |
|  - camx/src/csl/ (Kernel Interface Layer)                               |
|  - Linux V4L2 Subdevices + Synx Driver + SMMU                           |
|  - Hardware Engines (TITAN ISP: Spectra 380/480/580, Titan IFE/IPE/BPS) |
+-------------------------------------------------------------------------+
```

### Why the split?
1. **CamX (Camera Extension)**: Qualcomm's proprietary core HW control engine. It is responsible for hardware nodes (IFE, BPS, IPE), ISP firmware configuration, CSL/KMD command packet generation, and pipeline scheduling.
2. **CHI (Camera Hardware Interface) / CDK (Camera Development Kit)**: Vendor customization layer. OEMs (Samsung, Xiaomi, Motorola, etc.) can customize topologies, inject proprietary nodes, implement multi-frame algorithms (HDR, Night Mode), and configure feature graphs without touching closed-source CamX internals.

---

## 2. Layered Architecture & Component Stack

| Layer | Repository Path | Primary Responsibility |
| :--- | :--- | :--- |
| **CHI Entry** | `chi-cdk/core/chi/` | Implements `camera3_device_ops_t` interface, exports HAL entry symbols (`camera_module_t`). |
| **CHI Framework** | `chi-cdk/core/chiframework/` | Usecase selection (`chxusecase.cpp`), Extension manager, stream rule engine. |
| **CHI Nodes** | `chi-cdk/core/chinode/` | Custom SW nodes (e.g. Face Detect wrapper, HDR blend, multi-frame stacking). |
| **CamX Core** | `camx/src/core/` | Pipeline engine (`camxpipeline.cpp`), Node scheduler (`camxnode.cpp`), Port bindings (`camxnodeport.cpp`). |
| **Hardware Nodes**| `camx/src/hwl/` | Hardware abstraction for IFE (`camxifenode.cpp`), BPS (`camxbpsnode.cpp`), IPE (`camxipenode.cpp`), Sensor (`camxsensornode.cpp`). |
| **CSL & Driver** | `camx/src/csl/` | CamX System Library: manages kernel interactions, MMU mappings, and Synx fences. |

---

## 3. Core HAL3 Lifecycle & Function Call Flows

```
 +-----------------------------------------------------------------------------------+
 |                             LIFECYCLE TIMELINE                                    |
 |                                                                                   |
 |  [Open Device]                                                                    |
 |         |                                                                         |
 |         v                                                                         |
 |  [configure_streams()]  --> Build FeatureGraph -> Instantiate Pipelines & Nodes   |
 |         |                                                                         |
 |         +----------------+ (Repeat per frame)                                     |
 |         |                |                                                        |
 |         v                v                                                        |
 |  [process_capture_request()]  --> Validate -> Sync Fences -> Dispatch to Nodes   |
 |         |                |                                                        |
 |         v                v                                                        |
 |  [process_capture_result()]   <-- HW Completion -> Read 3A/Stats -> Return to App |
 |         |                |                                                        |
 |         +----------------+                                                        |
 |         |                                                                         |
 |  [flush()]              --> Cancel In-flight Fences & Drop Pending Requests       |
 |         |                                                                         |
 |         v                                                                         |
 |  [close()]              --> Tear Down Pipelines, Destroy Nodes, Power Off Sensor  |
 +-----------------------------------------------------------------------------------+
```

---

### 3.1 configure_streams() Flow

`configure_streams` is called when the camera session starts or stream resolutions/formats change (e.g. switching between Preview, Video Recording, and High-Res Snapshot).

#### Detailed Call Trace:
```
1. Android CameraService
   └─> ICameraDeviceSession::configureStreams(stream_list)
        └─> CamX::HwDevice3::ConfigureStreams() [camxhwdevice.cpp]
             └─> ChiContext::ConfigureStreams() [chi.cpp]
                  └─> ExtensionModule::ConfigureStreams() [chxextensioninterface.cpp]
                       │
                       ├─> 1. Match Stream Configuration:
                       │      chxusecase.cpp -> Identify Usecase (Preview, Video, ZSL, Snapshot)
                       │
                       ├─> 2. Build Feature Graph:
                       │      FeatureGraphFactory::Create() -> Resolves Features (HDR, MFNR, EIS)
                       │
                       ├─> 3. Topology & Pipeline Creation:
                       │      ChiContext::CreatePipeline()
                       │       └─> CamX::Session::Create() [camxsession.cpp]
                       │            └─> CamX::Pipeline::Create() [camxpipeline.cpp]
                       │                 ├─> CamX::Node::Create() (Sensor, IFE, BPS, IPE)
                       │                 └─> CamX::Pipeline::LinkNodes() (Port-to-Port wiring)
                       │
                       ├─> 4. Buffer & Memory Allocation:
                       │      CamX::BufferPoolManager::AllocateInternalBuffers()
                       │      CSL::RegisterBuffers() -> SMMU / ION page table setup
                       │
                       └─> 5. Sensor Power & Clock Initialization:
                              CamX::SensorNode::StartSensor() -> CSL driver stream ON preparation
```

#### Key Logic in `configure_streams`:
1. **Stream Classification**: Incoming `camera3_stream_t` outputs are inspected for format (RAW10, YUV_420_888, BLOB/JPEG), resolution, and usage flags.
2. **Usecase Resolution**: The system queries XML definitions (e.g. `camxusecases.xml` / `chiusecases.xml`) or programmatic rule engines to match a predefined topology.
3. **Pipeline Instantiation**:
   - **Real-Time (RT) Pipeline**: Handles high-frame-rate streaming (Sensor $\to$ IFE $\to$ IPE $\to$ Preview/Video).
   - **Offline (Non-Real-Time) Pipeline**: Handles memory-to-memory post-processing (BPS $\to$ IPE $\to$ JPEG).

---

### 3.2 process_capture_request() Flow

For every frame, the camera client sends a `camera3_capture_request_t` containing target output buffers, input buffer (for reprocessing), and 3A settings metadata.

#### Detailed Call Trace:
```
1. Android CameraService
   └─> ICameraDeviceSession::processCaptureRequest(request)
        └─> CamX::HwDevice3::ProcessCaptureRequest() [camxhwdevice.cpp]
             └─> ChiContext::ProcessCaptureRequest() [chi.cpp]
                  └─> ExtensionModule::ProcessCaptureRequest() [chxusecase.cpp]
                       │
                       ├─> 1. Request Parsing & Validation:
                       │      Extract frame_number, settings, output_buffers, acquire_fences
                       │
                       ├─> 2. Sync Fence Handling:
                       │      CamX::SyncManager::RegisterFences()
                       │      Convert Android sync fence FDs into internal Synx sync points
                       │
                       ├─> 3. Pipeline Dispatch:
                       │      CamX::Session::ProcessCaptureRequest() [camxsession.cpp]
                       │       └─> CamX::Pipeline::ProcessCaptureRequest() [camxpipeline.cpp]
                       │            │
                       │            ├─> Bind Input/Output Ports with Stream Buffers
                       │            ├─> Generate Hardware Command Buffers (CSL Packets)
                       │            └─> Schedule Node Execution Sequence (Topological Order)
                       │
                       └─> 4. Hardware Dispatch:
                              CamX::Node::Execute()
                               └─> CamX::CSL::SubmitCommands() -> Kernel V4L2 / TITAN Driver
```

#### Key Logic in `process_capture_request`:
- **Asynchronous Fence Management**: The CPU does not block waiting for app buffers. It passes `acquire_fence` down to Synx. Hardware units (IFE/IPE) start processing only when the upstream fence is signaled.
- **Node Execution Scheduling**: Nodes in the pipeline are triggered in dependency order:
  $$\text{Sensor} --> \text{IFE} --> (\text{Optional BPS}) --> \text{IPE} --> \text{Display/Encoder}$$

---

### 3.3 process_capture_result() Flow

As soon as hardware finishes processing a frame or generating 3A metadata, results are sent back to Android framework via callback.

#### Detailed Call Trace:
```
1. Hardware Engine (TITAN ISP / CSL)
   └─> CSL Interrupt Handler (V4L2 SOF / EOF / Buffer Done)
        └─> Synx Signals Frame Completion
             └─> CamX::Node::ProcessResult() [camxnode.cpp]
                  └─> CamX::Pipeline::NotifyFrameDone() [camxpipeline.cpp]
                       │
                       ├─> 1. Extract 3A & Sensor Metadata:
                       │      3A Stats Engine computes AE, AWB, AF convergence values
                       │      Package dynamic metadata (exposure time, ISO, lens focus dist)
                       │
                       ├─> 2. Early / Partial Metadata Callback:
                       │      camera3_callback_ops::process_capture_result(PARTIAL_METADATA)
                       │
                       ├─> 3. Output Buffer Completion:
                       │      Generate release_fence for output buffers
                       │      Mark buffer status (CAMERA3_BUFFER_STATUS_OK)
                       │
                       └─> 4. Final Result Callback:
                              ChiContext::ProcessCaptureResult() [chi.cpp]
                               └─> camera3_callback_ops::process_capture_result(FINAL_RESULT)
```

#### Key Logic in `process_capture_result`:
- **Partial Results (`CAMERA3_RESULT` Stages)**:
  1. **Partial Result 1**: Early 3A metadata (3A state, focus status) so Camera Framework can trigger auto-exposure/focus animations without waiting for heavy pixel pipelines.
  2. **Partial Result 2 / Final Result**: Final dynamic image metadata + rendered output buffers (YUV / RAW / JPEG).

---

### 3.4 flush() Flow

`flush()` is invoked when the application terminates, switches cameras, or stops video recording abruptly. All pending requests in the pipeline must be aborted immediately.

```
1. Android CameraService -> ICameraDeviceSession::flush()
   └─> CamX::HwDevice3::Flush()
        └─> ChiContext::Flush()
             └─> CamX::Session::Flush()
                  ├─> Abort all pending CSL hardware jobs
                  ├─> Signal all waiting Synx fences with error status
                  ├─> Return all pending buffers with CAMERA3_BUFFER_STATUS_ERROR
                  └─> Return empty metadata results with frame numbers to close framework queues
```

---

### 3.5 close() Flow

Shuts down the camera hardware device cleanly and releases all resources.

```
1. Android CameraService -> ICameraDeviceSession::close()
   └─> CamX::HwDevice3::Close()
        └─> ChiContext::Close()
             ├─> 1. Ensure all pipelines are flushed and idle
             ├─> 2. CamX::Pipeline::Destroy() (Free Node internal states, teardown links)
             ├─> 3. CamX::Session::Destroy()
             ├─> 4. Free allocated memory pools (ION/Gralloc buffers, CSL command buffers)
             └─> 5. CSL::Close() -> Power down ISP power domains, close camera subdevice nodes
```

---

## 4. Topology Management, Feature Graphs & Node Selection

### 4.1 Node, Port, Link & Pipeline Concept

CamX represents any image processing sequence as a **Directed Acyclic Graph (DAG)**.

```
  +------------------+                    +------------------+
  |    Node A (IFE)  |                    |    Node B (IPE)  |
  |                  |                    |                  |
  |  [InPort0]       |                    |  [InPort0]       |
  |                  |    Link (Wiring)   |                  |
  |  [OutPort_Full] -+====================+-> [InPort_YUV]   |
  |  [OutPort_DS4]  -+                    |                  |
  +------------------+                    +------------------+
```

- **Node**: A processing entity (Hardware engine like IFE/IPE or Software worker).
- **Port**: Endpoints on a node. Can be **Sink (Input)** or **Source (Output)**.
- **Link**: A virtual connection joining an Output Port of Node A to an Input Port of Node B.
- **Pipeline**: A collection of interconnected Nodes executed in a single operational context.
- **Session**: A collection of one or more Pipelines (e.g., RT Pipeline + Offline Snapshot Pipeline).

---

### 4.2 Core Hardware & Software Nodes

| Node Name | Source Location | Description & Hardware Role |
| :--- | :--- | :--- |
| **`SensorNode`** | `camx/src/hwl/sensor/` | Communicates with image sensor via CSL; programs exposure, gain, and streaming commands. |
| **`IFENode`** | `camx/src/hwl/ife/` | **Image Front End**: Processes raw sensor data. Performs black level subtraction, lens shading correction (LSC), demosaic, and generates 3A raw statistics. Outputs full/downscaled YUV or RDI raw. |
| **`BPSNode`** | `camx/src/hwl/bps/` | **Bayer Processing Segment**: Dedicated offline Bayer RAW processing node. Handles advanced noise reduction, multi-frame RAW stacking, and High Dynamic Range (HDR) fusion. |
| **`IPENode`** | `camx/src/hwl/ipe/` | **Image Processing Engine**: Operates in YUV domain. Handles temporal filter (TF), 2D spatial sharpening, color conversion, 2D lens distortion correction, and dual-output scalar (Display + Video). |
| **`EVANode`** | `camx/src/hwl/eva/` | **Enhanced Video Analytics**: Computes optical flow and motion vectors for Electronic Image Stabilization (EIS). |
| **`FDNode`** | `camx/src/hwl/fd/` | **Face Detection Node**: Dedicated hardware accelerator for real-time facial tracking and landmark detection. |
| **`ChiNode`** | `chi-cdk/core/chinode/` | **Custom OEM Node**: Allows injection of proprietary algorithms (e.g. AI Scene Detection, Custom Bokeh, Night Stacking) directly into the graph. |

---

### 4.3 Feature Graph Selection (Feature2 / Usecase Selection)

In Qualcomm's CHI architecture, a **Feature Graph** is a dynamic sub-graph representing specific algorithms like **ZSL (Zero Shutter Lag)**, **HDR (High Dynamic Range)**, **MFNR (Multi-Frame Noise Reduction)**, or **SuperResolution**.

```
                           [Incoming Stream Config]
                                      │
                                      ▼
                        [Usecase Selector (chxusecase.cpp)]
                                      │
                 ┌────────────────────┴────────────────────┐
                 ▼                                         ▼
       [Single Camera Mode]                        [Dual/Multi Camera Mode]
                 │                                         │
                 ├─> Feature: HDR?                         ├─> Feature: Optical Zoom?
                 ├─> Feature: MFNR?                        ├─> Feature: Bokeh / Depth?
                 └─> Feature: EIS?                         └─> Feature: Fusion?
                                      │
                                      ▼
                      [FeatureGraph Merging & Assembly]
                                      │
                 ┌────────────────────┴────────────────────┐
                 ▼                                         ▼
     [Real-Time Streaming Pipeline]           [Offline Post-Processing Pipeline]
     (Sensor -> IFE -> IPE -> Preview)         (BPS -> IPE -> JPEG Encoder)
```

#### How Selection Works:
1. **Static XML Profile Definition**: `camxusecases.xml` and `chiusecases.xml` define valid combinations of sensor streams, resolution caps, and target node connections.
2. **Dynamic Feature Activation**: When the app enables `CONTROL_ENABLE_ZSL` or `CONTROL_SCENE_MODE_HDR`, CHI's `Feature2` framework activates the corresponding feature sub-graph.
3. **Graph Stitching**: The CHI framework dynamically splices offline processing nodes (like BPS and custom ChiNodes) onto the active real-time IFE stream.

---

### 4.4 Topology Real-Time vs Offline Pipelines

#### 1. Standard Real-Time Preview & Video Pipeline
```
 +--------------+
 |  Image Sensor|
 +-------+------+
         | (MIPI RAW)
         v
 +-------+------+
 |   IFE Node   | ---> [3A Statistics Engine (AE / AWB / AF)]
 +-------+------+
         | (YUV Full Resolution)
         v
 +-------+------+
 |   IPE Node   |
 +---+------+---+
     |      |
     |      +-------------------------> [Video Encoder Stream (YUV)]
     v
 [Display / Preview Stream (SurfaceView)]
```

#### 2. Advanced Offline Snapshot Pipeline (HDR / MFNR with BPS)
```
 +--------------+
 | Image Sensor |
 +-------+------+
         |
         v
 +-------+------+
 |   IFE Node   | -------------------------------------> [Preview Display]
 +-------+------+
         | (Raw RDI Dump to Memory)
         v
 +-------+------+
 |  DDR Memory  |  (Holds N-RAW frames for burst / stacking)
 +-------+------+
         |
         v
 +-------+-----------------------+
 |  BPS Node (Offline Processing)| <--- HDR / Multi-frame Noise Reduction
 +-------+-----------------------+
         | (Demosaiced YUV)
         v
 +-------+-----------------------+
 |  IPE Node (Offline Processing)| <--- Color Correction, Edge Enhancement
 +-------+-----------------------+
         | (Final YUV)
         v
 +-------+-----------------------+
 |  JPEG / Hardware Encoder Node |
 +-------+-----------------------+
         |
         v
  [Compressed JPEG Output Buffer]
```

---

## 5. Buffer & Sync Management (Synx / Fences)

Modern camera pipelines process 60–120 FPS at 4K/8K resolutions. Copying pixel buffers between nodes is strictly prohibited. CamX achieves high efficiency via:

```
  Android App (Gralloc) <======== Zero-Copy Shared Memory (ION) ========> CamX / CSL Hardware
                                            |
                         +------------------+------------------+
                         |                                     |
                         v                                     v
                 [Acquire Fence]                        [Release Fence]
             (Waits for producer HW)                (Signals consumer app)
```

1. **Zero-Copy Memory (ION / DMA-BUF)**: Buffers are allocated in contiguous physical memory. Nodes pass pointers to physical page tables managed by the SMMU.
2. **Synx Framework (Qualcomm Kernel Sync Engine)**:
   - Replaces traditional Linux sync fences inside the ISP kernel driver.
   - Allows hardware-to-hardware triggering: IFE signals Synx $\to$ hardware starts BPS immediately without waking up the CPU.

---

## 6. ⏱️ 1-Minute Quick Revision

- **CamX vs CHI**: CamX = Core engine & HW execution (IFE, BPS, IPE, CSL); CHI = OEM customization, Usecase selection, and Feature Graphs.
- **`configure_streams`**: Classifies streams $\to$ Selects usecase $\to$ Builds FeatureGraph $\to$ Instantiates Pipelines, Nodes, and Links $\to$ Pre-allocates buffer pools.
- **`process_capture_request`**: Receives frame request $\to$ Converts Android fences to Synx $\to$ Dispatches command packets across pipeline nodes in topological order.
- **`process_capture_result`**: HW signals completion $\to$ Sends Partial Result 1 (3A early metadata) $\to$ Sends Final Result (rendered buffers + full metadata).
- **`flush` & `close`**: Cancels active CSL jobs, returns error buffers, tears down nodes/pipelines, and powers off sensor/ISP rails.
- **Key HW Nodes**:
  - **`SensorNode`**: Exposure & streaming control.
  - **`IFENode`**: Real-time Bayer demosaic, lens shading, 3A stats generation.
  - **`BPSNode`**: Offline Bayer processing, HDR fusion, noise reduction.
  - **`IPENode`**: YUV spatial/temporal filtering, color transforms, multi-resolution scaling.
- **Pipelines**: **Real-Time** (Sensor $\to$ IFE $\to$ IPE $\to$ Display) vs **Offline** (DDR RAW $\to$ BPS $\to$ IPE $\to$ JPEG).
