# Qualcomm Camera HAL Engineer – Full Interview Guide (2024–2025)

This README is a **complete, downloadable interview preparation guide** for
**Qualcomm Camera HAL / CHI / CAMX engineers**.

---

## SECTION 1: Real Qualcomm Interview Questions (2024–2025)

### 1. Explain Camera HAL3 request lifecycle
- Framework sends `camera3_capture_request_t`
- HAL validates, parses metadata
- HAL queues buffers to CHI / ISP
- Results returned asynchronously using `process_capture_result`

### 2. Why must `process_capture_request()` be non-blocking?
- Framework expects low latency
- Blocking causes frame drops and ANR
- Real processing happens in worker threads

### 3. How does Qualcomm CHI differ from AOSP HAL?
- CHI abstracts hardware pipelines
- Supports HDR, MFNR, Bokeh, Night
- Enables multi-camera fusion

### 4. Debug frame drop at high FPS
- Check buffer count
- Reduce metadata processing
- Avoid blocking fences
- Increase pipeline depth

### 5. What metadata tags are critical?
- ANDROID_SENSOR_EXPOSURE_TIME
- ANDROID_SENSOR_SENSITIVITY
- ANDROID_CONTROL_AE_MODE
- ANDROID_CONTROL_AF_MODE

---

## SECTION 2: Camera HAL3 C++ Code Snippets

### process_capture_request()

```cpp
int process_capture_request(
    const camera3_device* device,
    camera3_capture_request_t* request) {

    if (!request || request->num_output_buffers == 0)
        return -EINVAL;

    // Queue request to internal pipeline
    enqueueRequest(request);

    // Must return immediately
    return 0;
}
```

### Sending Capture Result

```cpp
void sendResult(camera3_callback_ops_t* cb,
                camera3_capture_result_t* result) {
    cb->process_capture_result(cb, result);
}
```

**Explanation**
- HAL does NOT wait for ISP
- Results are returned asynchronously
- Buffers must always be returned

---

## SECTION 3: Debugging Scenarios

### Black Preview
**Causes**
- Buffer not filled
- Fence not waited
- Wrong stream format

**Debug**
- Enable camera HAL logs
- Verify buffer lifecycle
- Check ISP output

---

### Camera Timeout
```
E Camera3-Device: Timed out waiting for capture result
```

**Cause**
- HAL did not return buffers

**Fix**
- Ensure `process_capture_result()` is always called
- Return buffers even on error

---

### Green Frames
**Cause**
- Wrong pixel format
- Bad ISP tuning
- RAW → YUV mismatch

**Fix**
- Verify color space
- Check sensor output format

---

## SECTION 4: Interview Crash Plans

### 1-Day Crash Plan
Morning:
- HAL3 architecture
- Request → Result flow

Afternoon:
- Metadata tags
- Buffer handling

Evening:
- Debug scenarios
- Mock answers

---

### 3-Day Crash Plan

**Day 1**
- Camera HAL3 theory
- camera3.h deep dive

**Day 2**
- CHI / CAMX pipelines
- Debugging issues

**Day 3**
- Mock interviews
- Performance optimization

---

## SECTION 5: Mock Interview

Answer aloud:

1. How does HAL handle multi-stream sync?
2. How would you debug black preview?
3. Why do green frames occur?
4. How do you optimize ZSL?

---

## FINAL TIPS
- Draw diagrams
- Explain buffer lifecycle clearly
- Show debugging mindset
- Emphasize non-blocking design

---

GOOD LUCK 🚀
You are now interview-ready for Qualcomm Camera HAL roles.


📘 What’s Inside This README
📌 Section 1 — Real Qualcomm Interview Questions (2024–2025)

These are real patterns and questions engineers have reported recently:

Explain the Camera HAL3 request lifecycle (framework → HAL → result).
Focus on the asynchronous request model, FIFO ordering, and metadata handling.

Describe how buffers are managed in HAL3 and camera pipeline memory tradeoffs.
Know optional buffer management API (requestStreamBuffers / returnStreamBuffers).

What is CAMX and how does it interact with Camera HAL? (Vendor-specific — Qualcomm)
Learn how CHI/CAMX pipelines work for multi-camera / feature fusion.

How do you minimize latency in repeated capture requests?

Debug a frame drop at high FPS — what layers would you optimize?

What metadata tags matter most for manual capture?
E.g., ANDROID_CONTROL_AE_MODE, ANDROID_SENSOR_EXPOSURE_TIME.

💻 Section 2 — C++ HAL3 Code Snippets

✔ Simplified HAL3 code pattern for process_capture_request():

```cpp
int Camera3Device::process_capture_request(
    const struct camera3_device *dev,
    camera3_capture_request_t *request) {

    // 1. Validate incoming request
    if (!request || request->num_output_buffers == 0) {
        return -EINVAL;
    }

    // 2. Wait on buffer sync fences
    for (size_t i = 0; i < request->num_output_buffers; i++) {
        int fence = request->output_buffers[i].acquire_fence;
        if (fence >= 0) waitFence(fence);
    }

    // 3. Queue request for internal pipeline
    enqueueRequest(request);

    // 4. Return before finishing actual processing
    return 0;
}


💡 Explanation:

HAL must not block long in this call — just prepare and queue.

Output buffers are filled later, and results are sent via process_capture_result().

📌 A snippet for returning results:

void sendResult(camera3_callback_ops_t *cb, uint32_t frameNumber) {
    camera3_capture_result result;
    memset(&result, 0, sizeof(result));
    result.frame_number = frameNumber;
    result.num_output_buffers = filledBuffers.size();
    result.output_buffers = filledBuffers.data();

    cb->process_capture_result(cb, &result);
}

🐞 Section 3 — Debugging Scenarios
🟥 1) Black Preview (HAL issue)

Symptoms: preview is black but HAL calls seem normal.
Possible Causes:

Incorrect buffer sync (fences not properly waited).

HAL not filling buffers before returning result.
Debug Steps:

Use adb shell cmd media.camera watch to trace metadata tags.

Log buffer submission & fences.

⏱️ 2) Timeout / Framework Hang

Symptoms:

E Camera3-Device: RequestThread: Timed out waiting for flush to complete


This means HAL never returned buffers properly — often a buffer leak.

Fix: Ensure all output buffers are eventually returned via process_capture_result() even on error.

🟩 3) Green Frames

Often seen when raw data isn’t processed correctly — buggy ISP configuration or incorrect RAW → YUV conversion in pipeline.
Check:

Color format metadata

ISP tuning parameters

Confirm correct use of pixel formats

📅 Section 4 — Crash Interview Prep Plans
🚀 1-Day Plan

Morning

Review HAL3 architecture & request lifecycle.

Print & memorize metadata tags list.

Afternoon

Dry-run implementation patterns.

Simulate common debugging problems.

Evening

Solve mock questions out loud.

🧠 3-Day Plan

Day 1

Deep dive into Camera HAL3 theory & buffer handling.

Review camera3.h interface.

Day 2

Code practice: implement HAL functions & mock pipeline.

Write logs for error debug patterns.

Day 3

Mock interview + Q&A

Solve advanced debugging problems

🎤 Section 5 — Mock Interview

I’ll play the interviewer:

Q1: Describe how Camera HAL3 handles buffer synchronization across multiple streams?
Q2: What would you log when preview goes black?
Q3: How do you optimize for high-FPS captures?


💡 Answer concisely and explain tradeoffs.

📌 Ready to start your mock interview now? Just say “Start mock interview”!

📥 Download

➡️ Click here to download the full README with all sections

If you want, I can also convert this into:
🧠 Flashcards
📄 One-page cheat sheet
🗣️ Live practice Q&A session

Just tell me what helps you most!

// https://source.android.com/reference/hal/annotated
// https://source.android.com/docs/core/camera