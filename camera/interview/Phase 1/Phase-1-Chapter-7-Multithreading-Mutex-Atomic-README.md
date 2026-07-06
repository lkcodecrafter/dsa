# Phase 1 - Chapter 7: Multithreading, Mutex, Atomic & Synchronization

> Embedded Camera Interview Masterclass (Condensed Edition)

## Objectives
- Understand processes vs threads
- Create threads using `std::thread`
- Protect shared data with mutexes
- Learn atomics and condition variables
- Relate threading concepts to Camera HAL

---

# 1. Process vs Thread

| Process | Thread |
|---|---|
| Own memory space | Shares process memory |
| Heavyweight | Lightweight |
| IPC required | Easy communication |

```
Process
 ├── Thread 1
 ├── Thread 2
 └── Thread 3
```

---

# 2. Creating a Thread

```cpp
#include <thread>
#include <iostream>

void worker() {
    std::cout << "Worker\n";
}

int main() {
    std::thread t(worker);
    t.join();
}
```

`join()` waits for completion.

---

# 3. join() vs detach()

- `join()` : caller waits.
- `detach()` : thread runs independently.

Avoid `detach()` unless the lifetime is carefully managed.

---

# 4. Race Condition

```cpp
int counter = 0;

// Two threads execute:
counter++;
```

Both threads may read the same value before writing.

---

# 5. Mutex

```cpp
std::mutex m;

void inc() {
    std::lock_guard<std::mutex> lock(m);
    ++counter;
}
```

Mutex ensures only one thread enters the critical section.

---

# 6. lock_guard vs unique_lock

| lock_guard | unique_lock |
|---|---|
| Simple | Flexible |
| Always owns lock | Can unlock/relock |

---

# 7. Deadlock

```
Thread A : Lock M1 -> waits for M2
Thread B : Lock M2 -> waits for M1
```

Prevention:
- Lock in a consistent order.
- Keep critical sections short.

---

# 8. condition_variable

Producer waits until data is consumed.

```cpp
std::condition_variable cv;
cv.wait(lock);
cv.notify_one();
```

---

# 9. Atomic

```cpp
std::atomic<int> count{0};
count++;
```

Useful for simple shared variables without a mutex.

---

# 10. Producer-Consumer

```
Producer ---> Queue ---> Consumer
```

Producer:
- Captures frames.

Consumer:
- Processes frames.

This pattern is common in Camera HAL pipelines.

---

# 11. Camera HAL Example

```
Camera Sensor
      |
Capture Thread
      |
Buffer Queue
      |
ISP Thread
      |
HAL Thread
      |
Application
```

Multiple threads process frames concurrently.

---

# 12. Common Bugs

- Race condition
- Deadlock
- Starvation
- Data corruption
- Forgotten join()

---

# 13. Debug Exercise

Question:
Two threads increment the same integer and the final value is incorrect.

Answer:
Protect the shared variable with a mutex or use std::atomic<int>.

---

# 14. Interview Questions

1. Process vs thread?
2. What is a race condition?
3. What is a mutex?
4. What is a critical section?
5. join() vs detach()?
6. What is deadlock?
7. How do you avoid deadlock?
8. What is starvation?
9. What is livelock?
10. What is std::atomic?
11. Mutex vs atomic?
12. What is lock_guard?
13. What is unique_lock?
14. Why condition_variable?
15. notify_one vs notify_all?
16. Producer-consumer problem?
17. Thread-safe queue?
18. Why multithreading in Camera HAL?
19. Buffer synchronization?
20. Best practices for thread safety?

## Revision

- Use `join()` unless you have a good reason not to.
- Protect shared state.
- Prefer `lock_guard` for simple locking.
- Use `atomic` for simple counters.
- Avoid deadlocks with consistent lock ordering.
