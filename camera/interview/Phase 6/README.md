# Phase 6 - Camera HAL3

> Embedded Camera & Real-Time Systems Interview Masterclass (Simplified Edition)

This guide dives deep into the **Android Camera HAL3** interface, detailing the core structure of `camera3.h`, the HAL state machine, stream and buffer models, hardware synchronization using sync fences, metadata manipulation, and the vendor tag system. It is written in simple, clear English with detailed ASCII diagrams and code-level definitions.

---

## Table of Contents
1. [The Camera HAL3 API & Header Definitions](#1-the-camera-hal3-api--header-definitions)
2. [Camera HAL3 State Machine](#2-camera-hal3-state-machine)
3. [Streams & Buffers in HAL3](#3-streams--buffers-in-hal3)
4. [Metadata Management (`camera_metadata_t`)](#4-metadata-management-camera_metadata_t)
5. [The Capture Request & Result Lifecycle (HAL-side)](#5-the-capture-request--result-lifecycle-hal-side)
6. [Vendor Tag & Debugging Subsystems](#6-vendor-tag--debugging-subsystems)
7. [30 Camera HAL3 Interview Questions & Answers](#7-30-camera-hal3-interview-questions--answers)
8. [Study & Memory Masterclass Strategies](#8-study--memory-masterclass-strategies)

---

## 1. The Camera HAL3 API & Header Definitions

The interface between the Android Camera Service and the vendor camera HAL is defined in the header file `<hardware/camera3.h>`. It is a C-based struct interface utilizing function pointers to act as an Object-Oriented contract.

### 1.1 Core Struct Relations

```
     +-------------------------------------------------+
     |                 camera3_device_t                |  <- Represents the physical camera
     +-------------------------------------------------+
       |                                             |
       v (contains ops pointer)                      v (contains private data)
+-----------------------------------+        +-----------------------------------+
|       camera3_device_ops_t        |        |         private_device_t          |
+-----------------------------------+        +-----------------------------------+
  - initialize()                               - Vendor-defined context
  - configure_streams()                        - Driver file descriptors
  - process_capture_request()                  - Custom pipeline threads
  - flush()                                    - State variables
```

### 1.2 Core Interface Structs

1. **`camera3_device_t`**: Represents the camera hardware instance. It contains:
   * `common`: The standard Android hardware module struct (`hw_device_t`).
   * `ops`: A pointer to `camera3_device_ops_t` containing the interface function pointers.
   * `priv`: A private vendor-defined pointer used to hold the HAL's internal state context.

2. **`camera3_device_ops_t`**: The table of function pointers the framework calls:
   * `initialize()`: Registers framework callback functions with the HAL.
   * `configure_streams()`: Sets up input/output streams (resolutions, formats, usages).
   * `construct_default_request_settings()`: Requests templates (e.g., Preview, Snapshot, Video) with default parameters.
   * `process_capture_request()`: Submits a new frame capture request to the HAL.
   * `dump()`: Dumps vendor HAL debug state information.
   * `flush()`: Aborts all active/queued capture requests.

3. **`camera3_callback_ops_t`**: The table of callbacks the HAL uses to communicate back to the framework:
   * `process_capture_result()`: Returns metadata and filled buffers for a capture request.
   * `notify()`: Sends asynchronous events like shutter exposure timestamps or error codes.

---

## 2. Camera HAL3 State Machine

The Camera HAL operates in a strict state sequence. If the framework calls operations out of order, the HAL must return errors or block.

```
       +---------------------------------------------+
       |                UNINITIALIZED                |
       +---------------------------------------------+
                              |
                              |  initialize()
                              v
       +---------------------------------------------+
       |                 UNCONFIGURED                |
       +---------------------------------------------+
                              |
       +----------------------+----------------------+
       | configure_streams()  ^                      | configure_streams()
       v                      | (Teardown)           v (Reconfigure)
       +---------------------------------------------+
       |                  CONFIGURED                 |
       +---------------------------------------------+
                              |
                              |  process_capture_request()
                              v
       +---------------------------------------------+
       |                    ACTIVE                   |
       +---------------------------------------------+
                              |
                              |  flush() / Done
                              v
       +---------------------------------------------+
       |                    ERROR                    |  <- Recovery: close device
       +---------------------------------------------+
```

### 2.1 State Transitions
* **UNINITIALIZED**: The camera service has loaded the HAL library, but hasn't called `initialize()` yet. The device is closed or sleeping.
* **UNCONFIGURED**: `initialize()` has been called. The HAL has registered the framework callbacks. No streams are active.
* **CONFIGURED**: The framework has called `configure_streams()`. The HAL has allocated buffers, mapped drivers, and initialized the ISP hardware.
* **ACTIVE**: The framework is actively sending capture requests. The pipeline is running.
* **ERROR**: An unrecoverable hardware or driver error has occurred. The HAL calls `notify()` with `ERROR_DEVICE`. The only recovery is to close and re-open the camera.

---

## 3. Streams & Buffers in HAL3

A **Stream** represents a flow of image buffers. A **Buffer** is the individual physical memory container.

### 3.1 `camera3_stream_t`
The framework defines this struct during stream configuration:
```c
typedef struct camera3_stream {
    int stream_type;          // CAMERA3_STREAM_OUTPUT, INPUT, or BIDIRECTIONAL
    uint32_t width;           // Image width in pixels
    uint32_t height;          // Image height in pixels
    int format;               // HAL_PIXEL_FORMAT_RAW16, YV12, IMPLEMENTATION_DEFINED, etc.
    uint32_t usage;           // Gralloc usage flags (e.g. GRALLOC_USAGE_HW_CAMERA_WRITE)
    uint32_t max_buffers;     // Max buffers HAL might dequeue concurrently
    void *priv;               // Framework private pointer
} camera3_stream_t;
```

### 3.2 `camera3_stream_buffer_t`
Exchanged during requests and results to describe the state of an individual buffer:
```c
typedef struct camera3_stream_buffer {
    camera3_stream_t *stream;     // Pointer to the stream this buffer belongs to
    buffer_handle_t *buffer;      // Gralloc memory pointer (physical memory descriptors)
    int status;                   // CAMERA3_BUFFER_STATUS_OK or STATUS_ERROR
    int acquire_fence;            // Sync file descriptor (wait before writing)
    int release_fence;            // Sync file descriptor (wait before reading)
} camera3_stream_buffer_t;
```

### 3.3 Hardware Synchronization (Sync Fences)
Sync Fences prevent race conditions between the CPU, GPU, and ISP without stalling the processors.
* **`acquire_fence`**: Provided by the framework. The HAL (or the ISP hardware driver) must wait until this fence is signaled (indicating the consumer has finished reading it) before writing new data into it.
* **`release_fence`**: Set by the HAL when returning a completed buffer. The framework (or consumer like the screen/encoder) must wait until this fence is signaled (indicating the ISP has finished writing the pixels) before reading the buffer.

---

## 4. Metadata Management (`camera_metadata_t`)

Android Camera controls are driven entirely by dynamic metadata tables. Metadata is compiled into a flat binary blob (`camera_metadata_t`) to optimize memory layouts and speed up IPC transfers.

```
       +---------------------------------------------+
       |              camera_metadata_t              |  <- Flattened Binary Blob
       +---------------------------------------------+
       |   Header: Counts, Entry capacity, Offsets   |
       +---------------------------------------------+
       |   Index Table: Sorted Array of Entries      |
       |   - Tag (e.g., ANDROID_SENSOR_EXPOSURE_TIME)|
       |   - Type (Byte, Int32, Float, Rational, etc)|
       |   - Count (Number of values in entry)       |
       |   - Value / Data Offset                     |
       +---------------------------------------------+
       |   Data Heap: Variable-length raw values     |
       +---------------------------------------------+
```

### 4.1 Accessing and Modifying Metadata
To work with the flat C-struct without causing segmentation faults, the Android framework provides the helper library `<system/camera_metadata.h>`:
*   `get_camera_metadata_entry()`: Retrieves values matching a specific tag.
*   `add_camera_metadata_entry()`: Appends a new tag and its data array.
*   `update_camera_metadata_entry()`: Replaces values of an existing tag.

#### Example C++ usage inside HAL:
```cpp
// Read exposure time set by the framework
camera_metadata_entry_t entry;
status_t rc = find_camera_metadata_entry(request->settings, ANDROID_SENSOR_EXPOSURE_TIME, &entry);
if (rc == OK && entry.count > 0) {
    int64_t exposure_ns = entry.data.i64[0];
    // Program exposure time to physical sensor via driver (ioctl)
    set_sensor_exposure(exposure_ns);
}
```

---

## 5. The Capture Request & Result Lifecycle (HAL-side)

When the framework submits a request via `process_capture_request`, the HAL processes it asynchronously to prevent blocking the IPC thread.

### 5.1 Request-Result Sequence diagram

```
Framework API Thread                 HAL Request Thread                  ISP Driver/Sensor
====================                 ==================                  =================
         |                                   |                                   |
  process_capture_request()                  |                                   |
-------->| (Queue request, return quickly)   |                                   |
         |---------------------------------->| (Dequeue request)                 |
         |                                   |  Apply settings via ioctl         |
         |                                   |---------------------------------->|
         |                                   |                                   | (Hardware exposure)
         |                                   |<----------------------------------| (V4L2 SOF Interrupt)
         |                                   |                                   |
         |        notify(SHUTTER)            |                                   |
         |<----------------------------------|                                   |
         |                                   |                                   | (DMA writes pixels to Gralloc)
         |                                   |<----------------------------------| (V4L2 EOF Interrupt)
         |                                   |                                   |
         |   process_capture_result()        |                                   |
         |   (Metadata & Buffer output)      |                                   |
         |<----------------------------------|                                   |
```

### 5.2 Step-by-Step Processing
1. **The Request Arrives**: The framework calls `process_capture_request()`. The HAL parses the settings, packages the request into an internal queue, and immediately returns success (`0`).
2. **The Worker Loop**: An internal HAL thread pulls the request from the queue, extracts the metadata controls, and communicates them to the camera sensor and ISP driver using system calls (`ioctl`).
3. **Start of Frame (SOF)**: The sensor starts exposure. The kernel driver triggers a hardware interrupt. The HAL captures this timestamp and immediately calls the `notify()` callback with `CAMERA3_MSG_SHUTTER` to send the frame timing metadata to the framework.
4. **Processing & DMA**: The sensor streams raw pixels to the ISP. The ISP scales, filters, color-corrects, and writes the output directly into the provided Gralloc buffer via DMA.
5. **End of Frame (EOF)**: The buffer write finishes. The driver triggers an EOF interrupt.
6. **Result Return**: The HAL package compiles the metadata settings actually used into a `camera_metadata_t` object. It wraps the completed buffer and metadata into a `camera3_capture_result_t` struct and returns it to the framework via the `process_capture_result()` callback.

---

## 6. Vendor Tag & Debugging Subsystems

A key component of the HAL is allowing vendors to write customized camera features (such as portrait modes, beauty filters, or dual-lens depth processing) without altering the core Android APIs.

### 6.1 Vendor Tag Subsystem
Android categorizes metadata keys by namespaces (e.g., `android.control`, `android.sensor`). Values outside the standard SDK are designated as **Vendor Tags**.
*   The vendor tag manager uses `vendor_tag_query_ops_t` to declare tag sections (e.g., `qualcomm.bokeh.ops`).
*   The HAL reports its custom tags to the framework during initialization.
*   The system learns the tag name, type, and ID, allowing apps to access these custom features using the generic key-value API (`CaptureRequest.set(Key, Value)`).

### 6.2 Debugging with `dumpsys`
When a camera hangs or drops frames, you can query its running state:
```bash
adb shell dumpsys media.camera
```
This command calls the `dump()` function pointer inside `camera3_device_ops_t`. The HAL writes its internal thread statuses, queue depths, register prints, and memory usages directly to the terminal output.

---

## 7. 30 Camera HAL3 Interview Questions & Answers

### Q1: What is `camera3_device_ops_t` and what are its key function pointers?
**Ans**: It is a C struct containing function pointers that the Android Camera Service uses to interact with the vendor camera device. The key function pointers are:
*   `initialize()`: Register framework callbacks (result/notify).
*   `configure_streams()`: Set up input/output streams for the pipeline.
*   `construct_default_request_settings()`: Get template settings (preview, record, etc.).
*   `process_capture_request()`: Submit capture request.
*   `dump()`: Print debug statements.
*   `flush()`: Cancel all pending requests.

### Q2: Explain the structure of `camera3_stream_t`. What are the different stream types (INPUT, OUTPUT, BIDIRECTIONAL)?
**Ans**: `camera3_stream_t` defines a single image stream.
*   **OUTPUT**: The HAL writes data into this stream (e.g. Preview, JPEG).
*   **INPUT**: The HAL reads data from this stream (typically used for reprocessing previously captured RAW/YUV images).
*   **BIDIRECTIONAL**: The stream acts as both input and output. The HAL can write a frame to it, and later read it back to perform recursive processing.

### Q3: How does the HAL notify the framework about a frame's exposure timestamp, and why is this done before returning the result?
**Ans**: The HAL calls `notify()` with a message of type `CAMERA3_MSG_SHUTTER` containing the frame number and the exposure start timestamp (in nanoseconds). This is done before returning the capture result to allow the framework's synchronization layer (like audio/video muxing or UI preview matching) to register frame timing immediately.

### Q4: Explain the role of `acquire_fence` and `release_fence` in `camera3_stream_buffer_t`. Who sets them and who waits on them?
**Ans**:
*   **`acquire_fence`**: Set by the framework. The HAL must wait until this fence is signaled before writing to the buffer.
*   **`release_fence`**: Set by the HAL. The framework/consumer must wait until this fence is signaled before reading from the buffer.
They are sync file descriptors representing hardware execution sync points.

### Q5: What is `flush()` in HAL3? How must a HAL implement it to ensure it doesn't leak buffers or block the system?
**Ans**: `flush()` is called by the framework to abort all active or queued requests. The HAL must immediately halt hardware pipelines, cancel pending requests, and return all buffers from those cancelled requests to the framework via `process_capture_result` with status set to `CAMERA3_BUFFER_STATUS_ERROR`. All cancelled metadata results must also be returned with null settings. The `flush()` call must return quickly and must not block.

### Q6: What is a partial capture result (`camera3_capture_result.partial_result`), and why is it useful?
**Ans**: It allows the HAL to send pieces of metadata back to the framework before the full capture result is ready. For example, 3A metadata (AE/AWB state) is determined early by the ISP, while other lens positions or frame stats take longer. Sending partial results allows the framework to update UI indicators (like focus lock) or run control loops with lower latency.

### Q7: How does a vendor define and register custom vendor tags?
**Ans**: The vendor HAL defines custom tag IDs (starting at `0x80000000`), names, and types. During boot, the `cameraserver` queries the vendor HAL's implementation of `vendor_tag_ops_t` (or AIDL equivalent `IVendorTagProvider`). The service loads these tags into the global namespace, enabling standard applications to pass custom settings down to the HAL.

### Q8: Explain the lifecycle of buffer ownership inside `process_capture_request`.
**Ans**: 
1. **Framework Ownership**: The framework allocates the buffer and owns it.
2. **Transition to HAL**: The framework calls `process_capture_request`, passing buffer ownership to the HAL.
3. **HAL/ISP Processing**: The HAL owns the buffer while processing the capture.
4. **Transition to Framework**: The HAL calls `process_capture_result`, returning buffer ownership back to the framework.

### Q9: What templates (e.g. PREVIEW, STILL_CAPTURE) must `construct_default_request_settings()` support?
**Ans**: The HAL must support:
*   `CAMERA3_TEMPLATE_PREVIEW`: Balanced settings for high frame rates.
*   `CAMERA3_TEMPLATE_STILL_CAPTURE`: Maximize image quality (slower, high noise reduction).
*   `CAMERA3_TEMPLATE_VIDEO_RECORD`: Stable frame rates, continuous autofocus.
*   `CAMERA3_TEMPLATE_VIDEO_SNAPSHOT`: Capture still frame while recording video.
*   `CAMERA3_TEMPLATE_ZERO_SHUTTER_LAG`: High-resolution continuous buffering.
*   `CAMERA3_TEMPLATE_MANUAL`: Direct raw controls, bypass automated settings.

### Q10: How does the HAL handle camera configuration changes (e.g. moving from photo to video recording)?
**Ans**: The framework calls `configure_streams()` with a new set of streams. The HAL is expected to tear down existing ISP pipelines, free cached resources, configure new hardware pipelines, allocate new gralloc buffers, and prepare the sensor for the new stream configurations.

### Q11: Explain how `camera_metadata_t` is structured in memory. Why is it a flat binary blob?
**Ans**: It is a contiguous block of memory containing a header, an index table of entries (tag, type, count, offset/value), and a data heap containing the raw values. It is flat to prevent pointer serialization overhead during IPC (Binder) transfers; the entire blob can be copied across processes in a single memory block transfer.

### Q12: What is the difference between a physical stream and a logical stream in logical multi-cameras?
**Ans**:
*   **Logical Stream**: Linked to the logical camera device ID visible to the application (e.g., combines zoom/wide outputs).
*   **Physical Stream**: Linked to a specific physical sensor (e.g., direct ultra-wide sensor RAW output). The HAL can stream from individual physical cameras concurrently within a logical session.

### Q13: How does the HAL implement 3A state reporting through metadata?
**Ans**: For every request, the ISP hardware analyzes the incoming raw frames and calculates exposure, white balance, and focus errors. The HAL reads these statistics from the ISP driver and populates the matching metadata tags (e.g., `ANDROID_CONTROL_AE_STATE`, `ANDROID_CONTROL_AF_STATE`) inside the `CaptureResult` returned to the framework.

### Q14: What is the role of `register_stream_buffers()`? Is it deprecated?
**Ans**: `register_stream_buffers()` was used in early HAL3 to register all buffers upfront with the HAL. It is deprecated since Camera HAL v3.2 because registering all buffers at initialization caused slow startup delays and high memory usage. Now, buffers are registered implicitly as they are passed inside capture requests.

### Q15: Explain how a HAL can support offline processing of capture requests.
**Ans**: With Android 11+, the HAL can support `switchToOfflineSession()`. This allows the HAL to take over remaining uncompleted requests from a live session, copy their states to a background offline session object, and allow the live session to close immediately. The HAL processes the queued frames offline and reports results to an offline callback interface.

### Q16: What is the purpose of the `max_buffers` field in `camera3_stream_t`?
**Ans**: It is calculated by the HAL during `configure_streams()` to tell the framework the maximum number of buffers the HAL needs to hold at the same time for that stream. If the HAL needs to run multi-frame noise reduction, it may set `max_buffers = 4`, meaning the framework must allocate at least 4 buffers to prevent the stream from starving.

### Q17: How does the HAL handle pipeline latency? What is the `ANDROID_REQUEST_PIPELINE_MAX_DEPTH` tag?
**Ans**: Since the HAL processes requests asynchronously, there can be multiple requests in flight. `ANDROID_REQUEST_PIPELINE_MAX_DEPTH` defines the maximum number of frames that can be inside the HAL pipeline at once (typically 3–4 frames). This tag is queried by the framework to predict frame-delay latency.

### Q18: What are the differences between `camera3_device_t` and `camera_device_t`?
**Ans**:
*   `camera_device_t` is the legacy base device struct defined in the Android HAL interface system.
*   `camera3_device_t` is the camera-specific struct version 3 that contains camera metadata ops and the updated request-result pipeline interface.

### Q19: How are camera errors reported using the `notify()` callback?
**Ans**: The HAL calls `notify()` with a `camera3_notify_msg` struct. It sets type to `CAMERA3_MSG_ERROR` and populates the error code:
*   `CAMERA3_MSG_ERROR_DEVICE`: Hardware critical failure.
*   `CAMERA3_MSG_ERROR_REQUEST`: Failed to process request (frame number provided).
*   `CAMERA3_MSG_ERROR_RESULT`: Failed to generate result metadata (frame number provided).
*   `CAMERA3_MSG_ERROR_BUFFER`: Failed to fill buffer for a specific stream (frame number and stream pointer provided).

### Q20: What is the relationship between V4L2 device nodes and the Camera HAL3 interface?
**Ans**: V4L2 device nodes (e.g. `/dev/video0`, `/dev/v4l-subdev*`) are the OS kernel-level interfaces to control the sensor and video buffers. The Camera HAL3 operates in user space and acts as a translator: it translates higher-level Android framework Binder calls into lower-level V4L2 `ioctl()` commands (e.g., `VIDIOC_S_CTRL`, `VIDIOC_QBUF`) to communicate with the kernel drivers.

### Q21: Explain how dynamic sensor mode switching (binning vs full resolution) is handled in the HAL.
**Ans**: When the stream configuration calls for high-resolution output (e.g., 50MP snapshot) versus low-resolution output (e.g., 12.5MP binned preview), the HAL intercepts this during `configure_streams()`. The HAL communicates with the sensor driver to modify the sensor crop registers and toggle pixel binning modes over the $\text{I}^2\text{C}$ bus before restarting the streaming pipeline.

### Q22: What are "reprocess" streams from the HAL's perspective?
**Ans**: During reprocessing, the framework passes an input buffer (usually RAW/YUV) containing image data to the HAL inside a request. The HAL configures the ISP to route this input buffer (via DMA read) into the ISP front-end, runs the requested image processing steps, and writes the output to the requested destination buffer (e.g. compiling RAW to JPEG).

### Q23: Why must capture results be returned in strict frame-number order?
**Ans**: The Camera Service and application framework require results in strict order (e.g., frame 1, frame 2, frame 3) to coordinate frame displays and synchronization. Even if frame 3 completes hardware processing before frame 2 (due to changing exposure settings or processing loads), the HAL must cache the result of frame 3 and wait to return it until frame 2 is completed and returned.

### Q24: What is the role of `ANDROID_CONTROL_AE_REGIONS` and `ANDROID_CONTROL_AF_REGIONS` metadata?
**Ans**: They contain coordinates defining specific spatial weight matrices on the screen. The framework sets these regions based on user focus-tapping. The HAL parses these regions, calculates the corresponding area coordinates on the image sensor, and configures the ISP's 3A statistics hardware to prioritize exposure and focus calculations within those specific pixel coordinates.

### Q25: How does the HAL communicate lens shading map capabilities?
**Ans**: The HAL exposes the lens shading capabilities in the static characteristics metadata. During live capturing, if requested, the HAL calculates the lens shading correction gains applied across the sensor grid to fix vignetting (dark corners) and returns this correction array inside the `CaptureResult` using the `ANDROID_LENS_SHADING_MAP` tag.

### Q26: Are `process_capture_request()` calls thread-safe or re-entrant?
**Ans**: `process_capture_request()` is called by the framework under a single-threaded binder dispatcher, so the HAL does not need to handle concurrent re-entrant calls to it. However, the HAL must ensure it returns from the function call immediately (non-blocking) and handles the actual processing asynchronously on its own dedicated worker threads to prevent stalling the framework's binder threads.

### Q27: How does the HAL handle raw sensor output storage format (like RAW10 vs RAW_OPAQUE)?
**Ans**:
*   `RAW10` is a packed format where four 10-bit pixels are stored in 5 bytes. The layout is standard and readable by standard applications.
*   `RAW_OPAQUE` is a vendor-specific format where the sensor writes RAW data in its native alignment (unprocessed). The layout is hidden from standard apps and can only be decoded by the vendor's own ISP reprocessing pipeline, saving packing/unpacking latency.

### Q28: How is `ANDROID_SENSOR_TIMESTAMP` synchronized with system boot time?
**Ans**: The exposure start timestamp of the frame must match the system's `CLOCK_BOOTTIME` clock source. The HAL reads the hardware interrupt timing registers or kernel SOF driver logs, which are calibrated against the kernel's boot timer, ensuring that camera frames can be synchronized with IMU sensors, audio recordings, and other system-wide sensors.

### Q29: What is the significance of the `override_layout` in buffer configuration?
**Ans**: The `override_layout` is set by the HAL during stream configuration to suggest optimal stride and alignment constraints for memory buffers. This ensures that the allocated Gralloc buffers match the alignment expectations of the ISP's DMA hardware (e.g., aligning strides to 64-byte or 128-byte boundaries), avoiding memory read/write bottlenecks.

### Q30: How does a developer debug a crash inside the Vendor HAL using `dumpsys` and `debuggerd`?
**Ans**:
1. Check the `dumpsys media.camera` output to locate the last successfully processed frame number and state.
2. If the HAL crashes, `debuggerd` generates a tombstone file in `/data/tombstones/`.
3. The developer uses toolsets like `addr2line` or `ndk-stack` to map the crash program counter (PC) address from the tombstone stack trace to the exact line of code in the vendor's shared library (`.so`) source code.

---

## 8. Study & Memory Masterclass Strategies

### 8.1 The "Restaurant Kitchen" Mental Model
*   **The Waiter** is the **Framework Binder Thread**.
*   **`process_capture_request()`** is the action of the waiter dropping an order ticket onto the kitchen counter and returning to the tables immediately.
*   **The Ticket Holder** is the **HAL Request Queue**.
*   **The Head Chef** is the **HAL Request Worker Thread**, coordinating the work.
*   **The Griddle / Ovens** are the **ISP & Sensor drivers**.
*   **The Sync Fence** is the "Order Timer". The chef cannot place ingredients onto the pan (`acquire_fence`) until the dishwasher has cleaned it. Once the dish is cooked, the chef rings the bell (`release_fence`), alerting the waiter that the food is ready to serve.

### 8.2 Duality Matrix: Streams vs. Buffers

| Feature | Stream (`camera3_stream_t`) | Buffer (`camera3_stream_buffer_t`) |
| :--- | :--- | :--- |
| **Lifecycle** | Created once during `configure_streams()`. | Passed continuously with requests/results. |
| **Nature** | Abstract pipe (width, height, format). | Physical pointer to memory (`buffer_handle_t`). |
| **Ownership** | Managed globally by framework & HAL. | Ownership changes dynamically during runtime. |
| **Sync** | None. | Synchronized using hardware sync fences. |

### 8.3 The Asynchronous Callback Ordering
Remember the strict completion sequence for a capture request:
1.  **Request Input**: `process_capture_request(frame N)`
2.  **Hardware Sync**: Driver waits on `acquire_fence` $\rightarrow$ Sensor opens.
3.  **Timing Pulse**: HAL invokes `notify(SHUTTER, frame N, timestamp)`.
4.  **Data Completion**: ISP completes DMA write $\rightarrow$ Signals `release_fence`.
5.  **Result Output**: HAL invokes `process_capture_result(frame N)` returning metadata + buffers.
