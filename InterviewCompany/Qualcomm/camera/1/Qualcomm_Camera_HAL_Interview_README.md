# Qualcomm Camera HAL Engineer – Interview Questions & Answers

This README is a **one‑stop revision guide** for Android **Qualcomm Camera HAL / CHI** interviews.

---

## 1. Camera HAL Overview

Camera HAL (Hardware Abstraction Layer) bridges **Android Camera Framework** and **camera hardware**.

**Flow**
```
Camera App
 → Camera Framework
 → Camera HAL (Qualcomm)
 → Kernel Driver (V4L2)
 → Sensor / ISP
```

---

## 2. Camera HAL1 vs HAL3

| Feature | HAL1 | HAL3 |
|------|------|------|
| Architecture | Legacy | Modern |
| Control | Limited | Full manual |
| Design | Preview based | Request based |
| Support | Deprecated | Actively used |

**Key point:** Qualcomm devices use **HAL3**.

---

## 3. Camera HAL3 Request Flow

```
process_capture_request()
 ├─ Validate request
 ├─ Parse metadata
 ├─ Queue buffers
 ├─ Send to ISP / CHI
 ├─ Return result asynchronously
```

**Important structs**
- camera3_capture_request_t
- camera3_capture_result_t

❗ `process_capture_request()` must be **non‑blocking**.

---

## 4. Camera Metadata

Metadata controls camera behavior.

**Examples**
- ANDROID_SENSOR_EXPOSURE_TIME
- ANDROID_CONTROL_AE_MODE
- ANDROID_CONTROL_AF_MODE

**Types**
- Request metadata
- Result metadata

---

## 5. Qualcomm CHI (Camera Hardware Interface)

CHI is Qualcomm’s proprietary camera layer.

**Responsibilities**
- Pipeline management
- Multi‑camera fusion
- HDR / Night / Bokeh features

```
Camera HAL → CHI → ISP → Sensor
```

---

## 6. ISP (Image Signal Processor)

ISP converts RAW data to final image.

**Tasks**
- Demosaicing
- Noise reduction
- AE / AF / AWB
- Color correction

ISP is **hardware / firmware**, not HAL code.

---

## 7. V4L2 in Camera HAL

V4L2 is Linux camera interface.

**Used for**
- Sensor streaming
- IOCTL calls
- Buffer queue/dequeue

HAL communicates with kernel via **V4L2 drivers**.

---

## 8. Buffer Management

Buffers are allocated by framework using **gralloc**.

**Lifecycle**
1. Framework allocates buffer
2. HAL receives handle
3. ISP fills image
4. HAL returns buffer

⚠️ Missing buffer return → camera freeze.

---

## 9. Multi‑Camera Support

Supports:
- Wide + Tele
- Depth cameras
- Logical cameras

**Techniques**
- Frame sync
- Timestamp alignment
- CHI fusion pipelines

---

## 10. Zero Shutter Lag (ZSL)

ZSL captures image from **already available preview buffers**.

**Benefits**
- Instant capture
- No shutter delay

Handled via **HAL + ISP pipeline**.

---

## 11. Threading Model

Camera HAL is **multi‑threaded**.

**Threads**
- Request thread
- Result thread
- Callback thread

Goal: **real‑time & non‑blocking** operation.

---

## 12. Sensor Bring‑Up

Steps:
- Device tree update
- Sensor driver
- Tuning files
- HAL configuration

Bad tuning → poor image quality.

---

## 13. Debugging Camera HAL Issues

**Tools**
- logcat
- dumpsys media.camera
- dmesg
- Qualcomm camera logs

**Common issues**
- Black preview
- Green frames
- Timeouts
- Metadata mismatch

---

## 14. Common Interview Scenario Question

**Q:** How do you reduce frame drops at high FPS?

**A:**
- Increase buffer count
- Avoid blocking calls
- Optimize metadata handling
- Use async callbacks

---

## 15. Interview Tips

✔ Draw request → result flow  
✔ Explain metadata clearly  
✔ Show debugging mindset  
✔ Know HAL3 lifecycle  

---

### Good Luck 🚀  
This guide is tailored for **Qualcomm Camera HAL Engineer interviews**.
