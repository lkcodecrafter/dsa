# Phase 12 - Design Patterns

> Embedded Camera & Real-Time Systems Interview Masterclass (Simplified Edition)

This guide explores **Design Patterns** adapted for embedded software development. It details patterns like Singleton, Observer, Finite State Machines (State), Strategy, and Active Object, focusing on implementations in C and resource-constrained C++ without dynamic memory allocations (`malloc`/`new`). It is written in simple, clear English with structured diagrams and code snippets.

---

## Table of Contents
1. [Design Patterns in Resource-Constrained Environments](#1-design-patterns-in-resource-constrained-environments)
2. [Key Embedded Design Patterns](#2-key-embedded-design-patterns)
3. [Finite State Machines (State Pattern)](#3-finite-state-machines-state-pattern)
4. [The Active Object Pattern (Concurrency)](#4-the-active-object-pattern-concurrency)
5. [30 Design Patterns Interview Questions & Answers](#5-30-design-patterns-interview-questions--answers)
6. [Study & Memory Masterclass Strategies](#6-study--memory-masterclass-strategies)

---

## 1. Design Patterns in Resource-Constrained Environments

Traditional software design patterns (e.g., Gang of Four) often assume dynamic memory allocations, standard library collections (like `std::vector`), and virtual function tables. In embedded platforms, these assumptions can introduce runtime uncertainty and memory overhead.

### 1.1 Core Constraints
*   **No Dynamic Allocation**: Objects should be allocated statically or on stack frames during initialization to prevent heap fragmentation.
*   **Virtual Table Overhead**: Virtual tables (`vtables`) consume memory and introduce indirect pointer hops, which can slow down real-time code execution.
*   **Memory Footprint**: Patterns must be scaled down to minimize RAM and Flash footprint.

---

## 2. Key Embedded Design Patterns

### 2.1 Singleton Pattern
Restricts a class to a single instance, providing a global point of access. Often used for hardware drivers (like `I2CDriver` or `FlashMemoryController`).

#### Non-Dynamic C++ Implementation:
```cpp
class I2CDriver {
private:
    I2CDriver() {} // Private constructor
    I2CDriver(const I2CDriver&) = delete; // Disable copy
    I2CDriver& operator=(const I2CDriver&) = delete; // Disable assignment

public:
    static I2CDriver& getInstance() {
        static I2CDriver instance; // Static allocation (guaranteed thread-safe in C++11)
        return instance;
    }
    void write(uint8_t addr, uint8_t reg, uint8_t data) {
        // Hardware control code
    }
};
```

### 2.2 Observer Pattern
Creates a one-to-many relationship where an object (Subject) notifies registered observers of state changes. Often used for distributing sensor readings or button events.

```
+--------------------+
|  Sensor (Subject)  |  <- Holds a static array of observer pointers
+--------------------+
  |  Notify()
  +------------------+
  |                  |
  v                  v
+------------------+ +------------------+
| Display Observer | |   SD Log Obs     |
+------------------+ +------------------+
```

To avoid `std::vector` allocations, use a fixed-size array of function pointers or abstract class pointers:
```cpp
#define MAX_OBSERVERS 4

class Observer {
public:
    virtual void onDataUpdate(int value) = 0;
};

class TempSensor {
private:
    Observer* observers[MAX_OBSERVERS] = {nullptr};
    int tempValue;

public:
    bool registerObserver(Observer* obs) {
        for (int i = 0; i < MAX_OBSERVERS; ++i) {
            if (observers[i] == nullptr) {
                observers[i] = obs;
                return true;
            }
        }
        return false; // Array is full
    }

    void notifyObservers() {
        for (int i = 0; i < MAX_OBSERVERS; ++i) {
            if (observers[i] != nullptr) {
                observers[i]->onDataUpdate(tempValue);
            }
        }
    }
};
```

---

## 3. Finite State Machines (State Pattern)

Embedded systems are highly state-driven (e.g., protocol parsers, camera capture modes, power states). The State Pattern allows an object to alter its behavior when its internal state changes.

### 3.1 State Transitions

```
                 +-----------------------+
                 |         INIT          |
                 +-----------------------+
                             |
                             | Boot Done / Init OK
                             v
                 +-----------------------+
        +------->|         IDLE          |<-------+
        |        +-----------------------+        |
        |                    |                    |
        | Capture Button     | Start Video        | Stop Recording
        |                    v                    |
+-----------------+   +-----------------+   +-----------------+
|  STILL_CAPTURE  |   | VIDEO_RECORDING |   |      ERROR      |
+-----------------+   +-----------------+   +-----------------+
        |                    |                    ^
        +---- Error --------+----- Error ---------+
```

### 3.2 C Table-Driven State Machine
Table-driven architectures are preferred in embedded systems because they are deterministic and separate transition logic from action code.

```c
typedef enum {
    STATE_IDLE,
    STATE_PREVIEW,
    STATE_CAPTURE,
    NUM_STATES
} State_t;

typedef enum {
    EVENT_START_PREVIEW,
    EVENT_TRIGGER_PHOTO,
    EVENT_STOP,
    NUM_EVENTS
} Event_t;

// State transition handler function pointer
typedef State_t (*StateHandler_t)(void);

// Transition Table Matrix
const StateHandler_t StateTable[NUM_STATES][NUM_EVENTS] = {
    // CURRENT STATE: IDLE
    [STATE_IDLE][EVENT_START_PREVIEW] = &DoStartPreview,
    [STATE_IDLE][EVENT_TRIGGER_PHOTO] = &DoNothing,
    [STATE_IDLE][EVENT_STOP]          = &DoNothing,

    // CURRENT STATE: PREVIEW
    [STATE_PREVIEW][EVENT_START_PREVIEW] = &DoNothing,
    [STATE_PREVIEW][EVENT_TRIGGER_PHOTO] = &DoCapturePhoto,
    [STATE_PREVIEW][EVENT_STOP]          = &DoStopPreview,
};
```

---

## 4. The Active Object Pattern (Concurrency)

The **Active Object** pattern decouples method execution from method invocation. It gives an object its own thread of execution and a message queue. Method calls are packaged as events, queued, and processed sequentially by the object's thread, eliminating lock contention.

```
  Client Threads                      Active Object Worker Thread
  ==============                      ===========================
        |
    Method Call (e.g., capture())
        |
        v
  +-----------+           +---------------+           +---------------+
  |  Proxy    |==========>| Message Queue |==========>|  Scheduler /  |
  +-----------+  Queues   +---------------+  Dequeues |  Worker Loop  |
                 Request                              +---------------+
                                                              |
                                                              | Executes
                                                              v
                                                      [Sensor Hardware]
```

### 4.1 Implementation inside Camera HAL3
When the Camera Service calls `process_capture_request()`, the HAL packages the request settings and buffer pointers into a command structure, queues it into the request queue, and returns immediately. A dedicated worker thread dequeues these requests and programs the hardware registers sequentially.

---

## 5. 30 Design Patterns Interview Questions & Answers

### Q1: What is the Singleton pattern, and why is it sometimes considered an anti-pattern in unit testing?
**Ans**: Singleton restricts instantiation to one instance and provides a global access point. It is considered an anti-pattern in testing because it introduces global state. Tests that modify the singleton can cause side-effects in subsequent tests, making it difficult to isolate test cases.

### Q2: How do you implement a thread-safe Singleton in C++11 without using a mutex lock?
**Ans**: You can declare a static variable local to the initialization method (often called "Meyers' Singleton"). C++11 guarantees that local static variables are initialized in a thread-safe manner, eliminating the need for manual mutex locks.

### Q3: Explain how the Observer pattern works without using dynamic allocation (`std::vector`).
**Ans**: Instead of dynamically allocating memory, the Subject holds a fixed-size array of observer base-class pointers (e.g., `Observer* observers[4]`). During registration, the Subject searches the array for a null slot and saves the pointer.

### Q4: What is the Factory pattern, and where is it used in device drivers?
**Ans**: The Factory pattern provides an interface for creating objects without specifying their concrete classes. In device drivers, it is used to instantiate driver instances based on device IDs (e.g., a `SensorFactory` returning an `IMX219` driver or an `OV5647` driver instance depending on the connected sensor detected on boot).

### Q5: Explain the difference between the State pattern and the Strategy pattern.
**Ans**:
*   **State Pattern**: The object's behavior changes dynamically based on its internal state, and states handle transitions to other states (e.g., a state machine).
*   **Strategy Pattern**: The client configures the object with a specific algorithm (strategy) at startup, and this strategy rarely changes during the object's lifecycle.

### Q6: What is the Active Object pattern, and how does it improve thread safety?
**Ans**: The Active Object pattern packages method requests as commands in a queue. A dedicated worker thread processes these commands sequentially. Because only the worker thread accesses the object's private data, lock synchronization is not needed, which prevents race conditions.

### Q7: What is the role of the Proxy pattern in IPC?
**Ans**: The Proxy pattern provides a local placeholder object that represents a remote object in a different address space. When client code calls a method on the local proxy, the proxy serializes the arguments, sends them across the IPC interface (e.g., Android Binder), and returns the results, hiding the IPC complexity.

### Q8: Explain how the Adapter pattern is used to wrap legacy C drivers in C++ classes.
**Ans**: The Adapter pattern wraps the interface of a class or function library to match a target interface. For example, a C++ `CameraInterface` class can wrap legacy C-style driver functions (`sensor_open()`, `sensor_set_exposure()`) inside its public member functions.

### Q9: What is the Command pattern, and how does it support undo/redo or execution queues?
**Ans**: The Command pattern encapsulates a request as an object, containing all information needed to execute the action. It stores the receiver instance, the target function pointer, and the parameters, allowing the request to be queued, delayed, or logged.

### Q10: How can the Decorator pattern be used in sensor data filtering?
**Ans**: The Decorator pattern dynamically adds responsibilities to an object. For sensor filtering, a base `RawSensor` reader can be wrapped with a `MovingAverageFilter` decorator, which is then wrapped with a `CalibrationOffset` decorator, filtering the data without altering the base reader class.

### Q11: What is the Template Method pattern?
**Ans**: The Template Method defines the skeleton of an algorithm in a base class method, delegating specific implementation steps to subclasses. For example, a base `Bootloader` class defines `boot_sequence()` (run self-tests, check flags, load app), while subclass boards override specific hardware setup functions.

### Q12: How does Policy-Based Design (Compile-time Strategy) avoid virtual table overhead?
**Ans**: Policy-based design uses C++ templates rather than inheritance. Algorithms are passed as template parameters, allowing the compiler to resolve function calls at compile time and inline the code, which eliminates virtual tables.

```cpp
template <typename FilterPolicy>
class SensorReader {
    FilterPolicy filter;
public:
    void read() {
        int raw = read_hw();
        int val = filter.apply(raw); // Resolved and inlined at compile time
    }
};
```

### Q13: What is the Prototype pattern, and is it useful in embedded systems?
**Ans**: The Prototype pattern creates new objects by copying an existing instance. In embedded systems, it is rarely used because dynamic duplication is slow and can cause heap issues; static initialization is preferred.

### Q14: Explain the Flyweight pattern.
**Ans**: The Flyweight pattern minimizes memory usage by sharing common data across multiple objects (e.g., storing font glyph layouts or common color palettes in a single shared read-only location instead of inside every sprite object).

### Q15: What is the Facade pattern, and how does it simplify interaction with an ISP?
**Ans**: The Facade pattern provides a simplified interface to a complex subsystem. Instead of exposing user space to individual subdevices (sensor, lens, ISP scaler, and output queues), a `CameraFacade` class exposes simple interfaces like `start_preview()` and `take_picture()`.

### Q16: How do you implement a State machine using State transition tables in C?
**Ans**: Define a 2D matrix array where the rows represent the current states, columns represent events, and the intersections hold function pointers to transition handlers. The state machine index is updated using `state = StateTable[state][event]();`.

### Q17: What is the main drawback of using the State pattern with individual class objects in embedded C++?
**Ans**: If every state is represented by a separate class instance, transitioning states requires allocating and deallocating memory, which can lead to memory fragmentation. Allocating all state instances statically at startup avoids this issue.

### Q18: What is the Bridge pattern, and how does it separate abstraction from implementation?
**Ans**: The Bridge pattern decouples an abstraction from its implementation so the two can vary independently. In device drivers, a `Camera` interface (Abstraction) references an underlying `CameraHALOps` pointer (Implementation), allowing the hardware implementation to change without affecting application code.

### Q19: Explain the Mediator pattern.
**Ans**: The Mediator pattern restricts direct communications between objects, forcing them to communicate through a mediator object. This reduces dependencies. For example, a `SystemPowerManager` acts as a mediator, coordinating sleep states between the Screen, Sensor, and CPU.

### Q20: What is the Chain of Responsibility pattern?
**Ans**: It passes a request along a chain of handlers. Each handler decides either to process the request or to pass it to the next handler in the chain. Often used in packet parsing to route packets to the correct decoder.

### Q21: Explain the Memento pattern and why it is rarely used in microcontrollers.
**Ans**: The Memento pattern captures and externalizes an object's internal state so it can be restored later. It is rarely used in microcontrollers because storing snapshots of memory structures consumes significant RAM.

### Q22: What is the Composite pattern?
**Ans**: The Composite pattern composes objects into tree structures to represent part-whole hierarchies, allowing clients to treat individual objects and compositions uniformly (e.g., grouping UI buttons and sliders into a single panel object).

### Q23: How do you implement the Strategy pattern in C using function pointers?
**Ans**: The context struct holds a function pointer member. The client registers the algorithm by setting this function pointer to the chosen implementation.

```c
struct Compressor {
    int (*compress)(uint8_t* src, uint8_t* dest);
};
```

### Q24: What is the Visitor pattern, and what is its overhead?
**Ans**: The Visitor pattern separates an algorithm from the object structure it operates on by using double dispatch. Its overhead includes indirect function calls and dependency cycles between classes, making it complex for embedded firmware.

### Q25: Explain the Object Pool pattern.
**Ans**: The Object Pool pattern pre-allocates a fixed array of objects at startup. When the system needs an object (e.g., a buffer frame or network packet), it leases it from the pool and returns it when finished, avoiding runtime allocation calls.

### Q26: Why is the Builder pattern useful when configuring complex camera streams?
**Ans**: The Builder pattern separates the construction of a complex object from its representation. For example, a `StreamConfigurationBuilder` allows setting width, height, format, and frame rate step-by-step, verifying configurations before applying them.

### Q27: How does the Observer pattern cause memory leaks if observers do not unregister?
**Ans**: If an observer is destroyed without unregistering, the Subject still holds a pointer to it. This can cause the Subject to write to invalid memory (a dangling pointer) when it notifies observers, leading to system crashes.

### Q28: What is the "Callback" mechanism, and how does it relate to the Observer pattern?
**Ans**: A Callback is a single function pointer passed to a module to notify a specific event. The Observer pattern is a generalization of the callback mechanism, supporting multiple listeners and richer event notification interfaces.

### Q29: Explain the Null Object pattern.
**Ans**: The Null Object pattern encapsulates the absence of an object by providing a default, do-nothing implementation. This eliminates the need for repetitive null-pointer checks (`if (ptr != nullptr)`) before calling methods.

### Q30: What is the Interceptor pattern?
**Ans**: The Interceptor pattern registers hooks or middleware that run automatically before and after a core framework method executes. Often used to log requests, measure execution times, or verify permissions.

---

## 6. Study & Memory Masterclass Strategies

### 6.1 The "Post Office" Mental Model for Active Object

*   **Traditional Method Call**: You walk into an office, ask the clerk to write a letter, and wait at the counter until they finish. This blocks you (the calling thread).
*   **Active Object Pattern**: You drop a letter into the mailbox (Message Queue) and go home. The post office worker (Active Object thread) processes letters sequentially in the background.

### 6.2 Duality Matrix: Strategy vs. Policy-Based Design

| Feature | Dynamic Strategy (Virtual Table) | Static Policy (Templates) |
| :--- | :--- | :--- |
| **Binding Time** | Runtime (Polymorphism). | Compile-time (Templates). |
| **Call Overhead** | Pointer indirect lookup (Slow). | Inlined execution (Fast). |
| **Memory Footprint**| Virtual table pointer in every object. | No runtime object overhead. |
| **Flexibility** | Strategy can change at runtime. | Fixed once compiled. |
