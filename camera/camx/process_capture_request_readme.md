# ⚡ Qualcomm CamX & CHI: `process_capture_request` Deep Dive

> **Reference Repositories:**
> - [CamX Source Tree (11se)](https://github.com/comprehensive9/vendor_qcom_proprietary/tree/11se/camx)
> - [CHI-CDK Source Tree (11se)](https://github.com/comprehensive9/vendor_qcom_proprietary/tree/11se/chi-cdk)

---

## 📑 Table of Contents
1. [Overview & Role in Android Camera HAL3](#1-overview--role-in-android-camera-hal3)
2. [Key Source Files & Locations](#2-key-source-files--locations)
3. [End-to-End Function Call Stack (ASCII Sequence Flow)](#3-end-to-end-function-call-stack-ascii-sequence-flow)
4. [Step-by-Step Execution Breakdown](#4-step-by-step-execution-breakdown)
   - [Phase 1: Request Entry & Parameter Parsing](#phase-1-request-entry--parameter-parsing)
   - [Phase 2: Android Acquire Fence to Synx Translation](#phase-2-android-acquire-fence-to-synx-translation)
   - [Phase 3: Usecase & FeatureGraph Dispatch](#phase-3-usecase--featuregraph-dispatch)
   - [Phase 4: CamX Session & Pipeline Request Scheduling](#phase-4-camx-session--pipeline-request-scheduling)
   - [Phase 5: Node Execution & Command Buffer Generation](#phase-5-node-execution--command-buffer-generation)
   - [Phase 6: CSL Hardware Submission (Kernel V4L2)](#phase-6-csl-hardware-submission-kernel-v4l2)
   - [Phase 7: Hardware Interrupts & Completion Signaling](#phase-7-hardware-interrupts--completion-signaling)
5. [Core Data Structures Map](#5-core-data-structures-map)
6. [Real-World Code Trace Example](#6-real-world-code-trace-example)
7. [⏱️ 1-Minute Quick Revision](#7-️-1-minute-quick-revision)

---

## 1. Overview & Role in Android Camera HAL3

Every single frame captured by the camera (whether a 60 FPS preview frame, video recording frame, or high-resolution RAW/HDR snapshot) is initiated by Android CameraService calling `ICameraDeviceSession::processCaptureRequest()`.

In Qualcomm CamX/CHI, `process_capture_request` is responsible for:
1. **Request Unpacking**: Reading `frame_number`, 3A dynamic control metadata (exposure, gain, zoom, lens focus), input buffer (for reprocessing), and target output stream buffers.
2. **Asynchronous Fence Management**: Translating Android sync fence file descriptors (`acquire_fence`) into kernel-level Qualcomm **Synx** synchronization objects to prevent CPU blocking.
3. **Usecase Routing**: Routing requests to Real-Time (RT) Pipelines (Sensor $\to$ IFE $\to$ IPE) or Offline Reprocessing Pipelines (BPS $\to$ IPE $\to$ JPEG).
4. **Command Packet Generation**: Translating 3A tuning parameters into ISP hardware register configuration packets (CSL Command Buffers).
5. **Topological HW Scheduling**: Submitting command packets to the Linux kernel / TITAN driver in node dependency order.

---

## 2. Key Source Files & Locations

| Component | Source File Path | Key Functions / Classes |
| :--- | :--- | :--- |
| **HAL Entry** | `camx/src/core/camxhwdevice.cpp` | `HwDevice3::ProcessCaptureRequest()` |
| **CHI Context** | `chi-cdk/core/chi/chi.cpp` | `ChiContext::ProcessCaptureRequest()` |
| **CHI Extension** | `chi-cdk/core/chiframework/chxextensioninterface.cpp` | `ExtensionModule::ProcessCaptureRequest()` |
| **Usecase Dispatch** | `chi-cdk/core/chiframework/chxusecase.cpp`<br>`chi-cdk/core/chiframework/chxusecaseutils.cpp` | `Usecase::ProcessCaptureRequest()`, `Usecase::ValidateRequest()` |
| **Feature Graph** | `chi-cdk/core/chiframework/chxfeaturegraph.cpp` | `FeatureGraph::ProcessCaptureRequest()`, `FeatureGraph::Execute()` |
| **Sync / Fence Manager** | `camx/src/core/camxsyncmanager.cpp`<br>`camx/src/core/camxfencemanager.cpp` | `SyncManager::RegisterFences()`, `SyncManager::CreateSyncObject()`, `Synx::ImportFence()` |
| **CamX Session** | `camx/src/core/camxsession.cpp` | `Session::ProcessCaptureRequest()`, `Session::ScheduleRequest()` |
| **CamX Pipeline** | `camx/src/core/camxpipeline.cpp` | `Pipeline::ProcessCaptureRequest()`, `Pipeline::ScheduleFrame()`, `Pipeline::CreatePacket()` |
| **CamX Node Engine** | `camx/src/core/camxnode.cpp`<br>`camx/src/core/camxnodeport.cpp` | `Node::Execute()`, `Node::ProcessRequest()`, `NodePort::AttachBuffer()` |
| **Hardware Nodes** | `camx/src/hwl/ife/camxifenode.cpp`<br>`camx/src/hwl/bps/camxbpsnode.cpp`<br>`camx/src/hwl/ipe/camxipenode.cpp` | Formats hardware-specific ISP configuration registers for exposure, lens shading, noise reduction, and scaling. |
| **CSL Interface** | `camx/src/csl/camxcsl.cpp`<br>`camx/src/csl/camxcslhw.cpp` | `CSL::SubmitCommands()`, `CSL::EnqueueHwRequest()`, IOCTL `VIDIOC_MSM_CAM_CSL_SUBMIT_REQ` |

---

## 3. End-to-End Function Call Stack (ASCII Sequence Flow)

```
Android CameraService (Framework)
 │
 └─> ICameraDeviceSession::processCaptureRequest(camera3_capture_request_t* request)
      │
      └─> [camxhwdevice.cpp] CamX::HwDevice3::ProcessCaptureRequest()
           │
           └─> [chi.cpp] ChiContext::ProcessCaptureRequest()
                │
                └─> [chxusecase.cpp] Usecase::ProcessCaptureRequest()
                     │
                     ├─> Phase 1: [chxusecase.cpp] Usecase::ValidateRequest()
                     │            Parses frame_number, target streams, 3A metadata settings
                     │
                     ├─> Phase 2: [camxsyncmanager.cpp] SyncManager::RegisterFences()
                     │            Converts Android acquire_fence FDs into Synx sync objects
                     │
                     ├─> Phase 3: [chxfeaturegraph.cpp] FeatureGraph::ProcessCaptureRequest()
                     │            Determines if feature nodes (HDR/MFNR/Night) need activation
                     │
                     ├─> Phase 4: [camxsession.cpp] CamX::Session::ProcessCaptureRequest()
                     │    │
                     │    └─> [camxpipeline.cpp] CamX::Pipeline::ProcessCaptureRequest()
                     │         │
                     │         ├─> [camxpipeline.cpp] Pipeline::CreatePacket()
                     │         │    Creates CamX::Packet descriptor for this frame
                     │         │
                     │         ├─> [camxnode.cpp] Pipeline::ExecuteNodes()
                     │         │    Iterates through pipeline DAG nodes in dependency order:
                     │         │    ├── [camxsensornode.cpp] SensorNode::Execute()
                     │         │    ├── [camxifenode.cpp]    IFENode::Execute()
                     │         │    ├── [camxbpsnode.cpp]    BPSNode::Execute() (If offline)
                     │         │    └── [camxipenode.cpp]    IPENode::Execute()
                     │         │
                     │         └─> [camxcsl.cpp] CamX::CSL::SubmitCommands()
                     │              Submits formatted command buffers & Synx sync points to KMD
                     │
                     └─> Kernel TITAN Driver / Hardware ISP
                          Executes DMA read/write and triggers interrupt on completion
```

---

## 4. Step-by-Step Execution Breakdown

### Phase 1: Request Entry & Parameter Parsing
1. Android CameraService passes `camera3_capture_request_t`:
   - `frame_number`: Unique sequential frame identifier.
   - `settings`: `camera_metadata_t` containing 3A requests (manual exposure time, sensitivity/ISO, zoom ratio, flash mode, lens focus distance).
   - `input_buffer`: Non-null for reprocessing (e.g. RAW $\to$ JPEG).
   - `num_output_buffers` & `output_buffers`: Destination gralloc handles (`buffer_handle_t*`) and `acquire_fence` descriptors.
2. `CamX::HwDevice3` wraps the structure into `CHICAPTUREREQUEST` and passes it to the CHI layer.

### Phase 2: Android Acquire Fence to Synx Translation
- **File**: `camx/src/core/camxsyncmanager.cpp`
- **Method**: `SyncManager::RegisterFences()`
- **Why this is critical**:
  - The Android Framework passes an `acquire_fence` file descriptor indicating when the app/display consumer has finished with the buffer.
  - Instead of blocking a CPU worker thread with `sync_wait()`, CamX imports the Linux fence FD into Qualcomm's **Synx** kernel framework (`Synx::ImportFence()`).
  - The hardware ISP engines will hold execution at the hardware DMA level until the Synx fence is signaled by the GPU or display subsystem.

### Phase 3: Usecase & FeatureGraph Dispatch
- **File**: `chi-cdk/core/chiframework/chxusecase.cpp`
- **Method**: `Usecase::ProcessCaptureRequest()`
- **Mechanism**:
  - Checks whether the frame is a standard real-time streaming frame (Preview / Video) or an offline snapshot frame (HDR / Burst / MFNR).
  - If multi-frame capture is triggered (e.g., 5-frame burst for Night Mode), CHI's `FeatureGraph` holds the capture request and dispatches 5 sequential sub-requests to CamX with varying exposure brackets.

### Phase 4: CamX Session & Pipeline Request Scheduling
- **File**: `camx/src/core/camxpipeline.cpp`
- **Method**: `Pipeline::ProcessCaptureRequest()`
- **Mechanism**:
  - Instantiates a `CamX::Packet` data structure representing all tasks for this frame.
  - Binds the physical ION/Gralloc memory addresses of the output buffers to the corresponding Pipeline Output Ports.
  - Resolves internal scratch buffers (e.g. IFE output buffer mapped to IPE input buffer).

### Phase 5: Node Execution & Command Buffer Generation
- **Files**: `camx/src/hwl/ife/camxifenode.cpp`, `camx/src/hwl/ipe/camxipenode.cpp`
- **Method**: `Node::Execute()`
- **Mechanism**:
  - Each Node converts high-level 3A and image processing settings into hardware register command lists:
    - **`SensorNode`**: Prepares I2C exposure time and analog gain commands.
    - **`IFENode`**: Prepares Black Level Correction, Lens Shading Correction (LSC) mesh tables, and Demosaic filter registers.
    - **`IPENode`**: Prepares Color Correction Matrix (CCM), Temporal Filter (TF) denoising parameters, and Hardware Scalar crop/zoom tables.
  - Register values are written into contiguous CSL Command Buffers (`CamX::CmdBuffer`).

### Phase 6: CSL Hardware Submission (Kernel V4L2)
- **File**: `camx/src/csl/camxcsl.cpp`
- **Method**: `CSL::SubmitCommands()`
- **Mechanism**:
  - Packages command buffers and Synx dependency handles into a CSL submission request.
  - Issues kernel IOCTL `VIDIOC_MSM_CAM_CSL_SUBMIT_REQ` to the Qualcomm TITAN camera driver.
  - The kernel driver programs the Hardware Command DMA engines (IFE/IPE hardware engines).

### Phase 7: Hardware Interrupts & Completion Signaling
1. Hardware finishes pixel processing and DMA writes output frames to RAM.
2. TITAN ISP hardware fires an End-Of-Frame (EOF) interrupt to the Linux kernel.
3. Synx signals the hardware output fence.
4. CamX receives the V4L2 event and initiates the **`process_capture_result`** callback sequence.

---

## 5. Core Data Structures Map

```
+-------------------------------------------------------------------------+
|                      camera3_capture_request_t                          |
|  - uint32_t frame_number;                                               |
|  - const camera_metadata_t* settings;                                   |
|  - camera3_stream_buffer_t* input_buffer;                               |
|  - uint32_t num_output_buffers;                                         |
|  - const camera3_stream_buffer_t* output_buffers;                        |
+-------------------------------------------------------------------------+
                                    │ (Wrapped by HAL3 device)
                                    ▼
+-------------------------------------------------------------------------+
|                          CHICAPTUREREQUEST                              |
|  - UINT32 frameNumber;                                                  |
|  - const CHIMETAHANDLE pMetadata;                                       |
|  - CHISTREAMBUFFER* pInputBuffers;                                      |
|  - UINT numOutputBuffers;                                               |
|  - CHISTREAMBUFFER* pOutputBuffers;                                     |
+-------------------------------------------------------------------------+
                                    │ (Parsed into CamX Engine)
                                    ▼
+-------------------------------------------------------------------------+
|                            CamX::Packet                                 |
|  - UINT64 frameNumber;                                                  |
|  - CmdBuffer* pCmdBuffers[];      (Hardware ISP Register Dumps)         |
|  - SynxHandle waitFences[];       (Inbound Acquire Fences)              |
|  - SynxHandle signalFences[];     (Outbound Completion Fences)          |
|  - PortBufferMapping portBuffers[];                                     |
+-------------------------------------------------------------------------+
```

---

## 6. Real-World Code Trace Example

Here is a simplified pseudocode representation of what happens inside `ChiContext::ProcessCaptureRequest()`:

```cpp
// Simplified representation of CHI process_capture_request flow
CHIRESULT ChiContext::ProcessCaptureRequest(
    CHICAPTUREREQUEST* pCaptureRequest) 
{
    // 1. Retrieve the active usecase
    Usecase* pUsecase = GetActiveUsecase();
    
    // 2. Validate request parameters and settings
    pUsecase->ValidateRequest(pCaptureRequest);
    
    // 3. Register and convert Android acquire fences to Synx sync handles
    CamX::SyncManager::GetInstance()->RegisterFences(
        pCaptureRequest->pOutputBuffers,
        pCaptureRequest->numOutputBuffers);
        
    // 4. Check for Feature Graph overrides (e.g. HDR / Night multi-frame bracketing)
    if (pUsecase->IsFeatureActive(FEATURE_HDR)) {
        pUsecase->GetFeatureGraph()->ProcessCaptureRequest(pCaptureRequest);
    }
    
    // 5. Dispatch request to the CamX Real-Time Pipeline
    CamX::Pipeline* pPipeline = pUsecase->GetPipeline(PIPELINE_REALTIME);
    pPipeline->ProcessCaptureRequest(pCaptureRequest);
    
    return CHIRESULT_SUCCESS;
}
```

---

## 7. ⏱️ 1-Minute Quick Revision

- **Purpose**: Receive per-frame capture requests from Android Framework, format ISP register commands, and trigger hardware processing.
- **Entry Point**: `HwDevice3::ProcessCaptureRequest()` in `camx/src/core/camxhwdevice.cpp`.
- **Fence Translation**: Android `acquire_fence` FDs are converted into Qualcomm **Synx** sync objects (`SyncManager::RegisterFences()`) so hardware waits without CPU stalling.
- **Usecase Routing**: `Usecase::ProcessCaptureRequest()` directs the frame to Real-Time (streaming) or Offline (snapshot) pipelines.
- **Packet Assembly**: `Pipeline::ProcessCaptureRequest()` generates a `CamX::Packet` associating stream buffers with pipeline ports.
- **Node Execution**: `SensorNode`, `IFENode`, and `IPENode` format hardware register command buffers (`CamX::CmdBuffer`) for 3A exposure, noise reduction, and scaling.
- **Kernel Dispatch**: `CSL::SubmitCommands()` submits command buffers to the kernel TITAN driver via V4L2 ioctls.
