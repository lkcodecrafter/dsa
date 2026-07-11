# Phase 2 - Modern C++17: Templates, STL Internals, Lambdas, and Multithreading

> Embedded Camera & Real-Time Systems Interview Masterclass (Simplified Edition)

This guide breaks down advanced C++17 topics into simple, plain English with straightforward examples. If you are preparing for real-time systems or camera pipeline interviews, this will help you understand the core concepts without getting lost in overly academic jargon.

---

## Table of Contents
1. [Templates & Metaprogramming](#1-templates--metaprogramming)
2. [STL Internals & Advanced Containers](#2-stl-internals--advanced-containers)
3. [Lambdas & Functional Programming](#3-lambdas--functional-programming)
4. [Concurrency & Multithreading](#4-concurrency--multithreading)
5. [Step-by-Step Dry Runs & ASCII Diagrams](#5-step-by-step-dry-runs--ascii-diagrams)
6. [30 Core Interview Questions & Answers](#6-30-core-interview-questions--answers)
7. [Common Bugs, Debugging & Best Practices](#7-common-bugs-debugging--best-practices)

---

## 1. Templates & Metaprogramming

Templates are C++'s way of letting you write a "blueprint" for functions or classes. Instead of copying and pasting code to handle different data types (like `int`, `double`, or custom structures), you write a template once. 

In low-latency systems (such as camera pipelines), templates are preferred over virtual functions because template code is generated at **compile-time**. This means there is no runtime overhead (no "vtable" lookups) and the compiler can optimize the code much better.

### 1.1 Type vs. Non-Type Template Parameters
*   **Type Parameters**: You pass a type (like `int` or `float`) as a placeholder. We use `typename` or `class`.
*   **Non-Type Template Parameters (NTTP)**: You pass a constant value (like an integer size) instead of a type. This is extremely useful in embedded systems to define fixed-size arrays on the stack, avoiding slow heap allocation.
*   **C++17 Feature (`template <auto>`)**: Instead of specifying the exact type of the constant value, you let the compiler figure it out automatically using `auto`.

```cpp
#include <iostream>

// 1. Standard Type Parameter: T can be any type
template <typename T>
void printValue(T val) {
    std::cout << "Value: " << val << '\n';
}

// 2. Non-Type Template Parameter (NTTP): Size is a constant integer
template <typename T, int Size>
class FixedArray {
    T data[Size]; // Stack allocation, extremely fast!
};

// 3. C++17 auto NTTP: The compiler deduces the type of the constant Val
template <auto Val>
void printConstant() {
    std::cout << "Constant: " << Val << '\n';
}

int main() {
    printValue(3.14);          // Deduce T as double
    FixedArray<int, 10> arr;   // Size is 10, known at compile time
    
    printConstant<42>();       // Val is deduced as int
    printConstant<'A'>();      // Val is deduced as char
}
```

### 1.2 Template Specialization
Sometimes, the general template blueprint doesn't work for a specific type (e.g., you need to handle pointers differently than values). Specialization allows you to write custom code for those specific cases.

*   **Primary Template**: The general blueprint.
*   **Partial Specialization**: Specializing only a subset of cases (e.g., handling any pointer type `T*`). Note: Only class templates can be partially specialized; function templates cannot.
*   **Full Specialization**: Specializing for one exact type (e.g., `void*`).

```cpp
#include <iostream>

// Primary (generic) template
template <typename T>
struct MemoryManager {
    static void allocate() {
        std::cout << "Generic heap allocation (malloc/new)\n";
    }
};

// Partial specialization: This template handles ALL pointer types (T*)
template <typename T>
struct MemoryManager<T*> {
    static void allocate() {
        std::cout << "Specialized pointer handling\n";
    }
};

// Full specialization: This template handles exactly void*
template <>
struct MemoryManager<void*> {
    static void allocate() {
        std::cout << "Hardware DMA Buffer Mapping (hardware-specific code)\n";
    }
};

int main() {
    MemoryManager<int>::allocate();    // Prints "Generic heap allocation"
    MemoryManager<int*>::allocate();   // Prints "Specialized pointer handling"
    MemoryManager<void*>::allocate();  // Prints "Hardware DMA Buffer Mapping"
}
```

### 1.3 C++17 Fold Expressions
Before C++17, if you wanted to process a variable number of arguments (a "parameter pack") in a template, you had to write complex recursive functions. C++17 introduced **Fold Expressions**, which let you apply a math or logical operator to all arguments in a single line.

Think of it as turning a list of arguments `(a, b, c, d)` into `a + b + c + d` automatically.

```cpp
#include <iostream>

// A fold expression that sums all passed arguments
template <typename... Args>
auto sumAll(Args... args) {
    return (args + ...); // Right Fold: expands to (args1 + (args2 + args3))
}

// A fold expression using the comma operator to print multiple values
template <typename... Args>
void printAll(Args... args) {
    (std::cout << ... << args) << '\n';
}

int main() {
    std::cout << sumAll(1, 2, 3, 4, 5) << '\n'; // Prints 15
    printAll("Camera ", "Sensor ", 1, " initialized."); // Prints "Camera Sensor 1 initialized."
}
```

### 1.4 Class Template Argument Deduction (CTAD)
Before C++17, you always had to explicitly write the types when creating templates (e.g., `std::pair<int, double> p(1, 2.3)`). In C++17, the compiler can inspect the constructor arguments and guess the template types for you.

```cpp
#include <utility>
#include <mutex>

void example() {
    // Pre-C++17: Explicitly writing types
    std::pair<int, double> p1(1, 2.3);
    
    // C++17: Deduced automatically as std::pair<int, double>
    std::pair p2(1, 2.3); 
    
    std::mutex mtx;
    // C++17: Deduced automatically as std::lock_guard<std::mutex>
    std::lock_guard lock(mtx); 
}
```

---

## 2. STL Internals & Advanced Containers

In high-performance software, choosing the right container and understanding how it handles memory is the difference between a smooth real-time pipeline and a laggy application.

### 2.1 std::vector
A `std::vector` is a dynamic array stored as a contiguous (continuous) block of memory. 

*   **Three-Pointer Layout**: Under the hood, a vector is managed by three pointers:
    1.  `begin`: Points to the first element.
    2.  `end`: Points to the spot just after the last active element (determines `size`).
    3.  `end_of_storage`: Points to the end of the allocated memory block (determines `capacity`).
*   **Capacity Growth**: When the vector is full (`size == capacity`) and you try to add an item:
    1.  It allocates a new, larger memory block (usually $1.5\times$ or $2\times$ the old size).
    2.  It copies or moves all elements from the old block to the new block.
    3.  It deletes the old block.
*   **Embedded Performance Tip**: Moving elements to a new memory block takes time ($O(N)$ latency). In real-time loops (like camera frame acquisition), this causes frame drops. Always use `.reserve(ExpectedSize)` during initialization to pre-allocate memory.

```
std::vector Memory Layout:
[ begin ]                               [ end ]           [ end_of_storage ]
    |                                      |                      |
    v                                      v                      v
  +-----------+-----------+-----------+-----------+--------------+--------------+
  | Element 0 | Element 1 | Element 2 | Element 3 | Unused Slot  | Unused Slot  |
  +-----------+-----------+-----------+-----------+--------------+--------------+
  <---------------------- size = 4 --------------->
  <--------------------------------- capacity = 6 ------------------------------>
```

### 2.2 std::map vs. std::unordered_map
*   **`std::map` (Ordered)**:
    *   **Structure**: A Red-Black Tree (a self-balancing binary tree).
    *   **Lookup time**: $O(\log N)$ (increases slowly as the map grows).
    *   **Memory Layout**: High overhead. Every item is stored in a separate "node" on the heap. Each node contains pointers to its parent, left child, and right child.
    *   **Cache Locality**: Poor. Traversal requires "pointer-chasing" (jumping to random memory locations), which is slow for CPU caches.
*   **`std::unordered_map` (Unordered)**:
    *   **Structure**: A Hash Table (array of buckets).
    *   **Lookup time**: $O(1)$ on average.
    *   **Rehash Warning**: When the map becomes too full, it allocates a larger array of buckets and redistributes all keys. This operation is slow and unpredictable ($O(N)$ latency spike).

```
std::map (Red-Black Tree - scattered nodes, slow cache access):
        [Node A] 
       /        \
   [Node B]    [Node C] 

std::unordered_map (Hash Table - bucket array pointing to lists):
[ Bucket 0 ] -> [ Key1: Val1 ] -> [ Key2: Val2 ] (Collision Chain)
[ Bucket 1 ] -> nullptr
[ Bucket 2 ] -> [ Key3: Val3 ]
```

### 2.3 Iterator Invalidation Rules
An iterator is like a pointer pointing to an item in a container. If the container moves its items in memory, that iterator becomes a "dangling pointer" pointing to garbage memory. Using it causes undefined behavior (crashes).

| Container | Insertion | Deletion |
| :--- | :--- | :--- |
| **`std::vector`** | Invalidates **all** iterators if capacity grows; otherwise, invalidates from insertion point to end. | Invalidates iterators from deletion point to end. |
| **`std::list`** | None (items are linked, they never move in memory). | Only the deleted item's iterator is invalidated. |
| **`std::map`** | None. | Only the deleted item's iterator is invalidated. |
| **`std::unordered_map`**| Invalidates **all** if a rehash is triggered. | Only the deleted item's iterator is invalidated. |

### 2.4 Real-Time Custom Memory Allocator
In real-time systems, we cannot call `new` or `malloc` while processing data because the OS allocator is slow and unpredictable. A custom allocator lets us pre-allocate a chunk of memory (a pool) and manage it ourselves without talking to the OS.

Here is a simplified pool allocator that serves single items from a pre-allocated stack array:

```cpp
#include <iostream>
#include <memory>
#include <vector>

template <typename T, size_t MaxElements>
class SimplePoolAllocator {
private:
    alignas(T) uint8_t memoryPool_[MaxElements * sizeof(T)];
    bool slotUsed_[MaxElements] = {false};

public:
    using value_type = T;

    SimplePoolAllocator() noexcept = default;

    template <typename U>
    SimplePoolAllocator(const SimplePoolAllocator<U, MaxElements>&) noexcept {}

    T* allocate(size_t n) {
        if (n > 1) throw std::bad_alloc(); // Only allow single allocations for simplicity
        
        for (size_t i = 0; i < MaxElements; ++i) {
            if (!slotUsed_[i]) {
                slotUsed_[i] = true;
                return reinterpret_cast<T*>(&memoryPool_[i * sizeof(T)]);
            }
        }
        throw std::bad_alloc(); // Pool is out of memory!
    }

    void deallocate(T* p, size_t n) noexcept {
        ptrdiff_t offset = reinterpret_cast<uint8_t*>(p) - memoryPool_;
        size_t index = offset / sizeof(T);
        if (index < MaxElements) {
            slotUsed_[index] = false;
        }
    }
};
```

---

## 3. Lambdas & Functional Programming

A lambda is simply an anonymous (nameless) inline function that can "capture" variables from the code block surrounding it.

### 3.1 Captures and Memory Layout
When you write a lambda, the compiler turns it into a temporary object of a hidden class (called a **closure**). The captured variables become member variables of this class.

*   `[=]`: Capture by **value**. The lambda stores a copy of the variable.
*   `[&]`: Capture by **reference**. The lambda stores a reference (pointer) to the original variable. 
    *   *Warning*: If the original variable is destroyed before the lambda runs, calling the lambda will crash (Use-After-Free).
*   `[*this]` (C++17): Captures the current object by **copying** it. This is safe for asynchronous tasks, ensuring the lambda does not use a dead `this` pointer if the parent object is destroyed.

```cpp
#include <iostream>

struct Camera {
    int id = 101;
    
    auto getSafeCallback() {
        // C++17 [*this] copies the entire Camera object
        return [*this]() {
            std::cout << "Camera ID: " << id << '\n';
        };
    }
};
```

### 3.2 The `mutable` Keyword
By default, lambdas cannot modify variables captured by value. The compiler treats the lambda's call operator as `const`. Adding the `mutable` keyword removes this restriction.

```cpp
#include <iostream>

int main() {
    int counter = 0;

    // Without mutable, writing "counter++" would fail to compile
    auto increment = [counter]() mutable {
        counter++;
        std::cout << "Inside lambda: " << counter << '\n';
    };

    increment(); // Prints: Inside lambda: 1
    increment(); // Prints: Inside lambda: 2
    
    // The original counter remains unchanged
    std::cout << "Original counter: " << counter << '\n'; // Prints: 0
}
```

### 3.3 `std::function` Overhead vs. Direct Lambda
`std::function` is a generic wrapper that can hold any callable function or lambda. However, it is heavy:
1.  **Heap Allocation**: If the lambda's captured variables are larger than a small buffer (usually 16-32 bytes), `std::function` allocates memory on the heap.
2.  **Indirection**: It calls the lambda via pointers, preventing the compiler from making the call fast (inlining).
*   **Embedded Design Rule**: Pass lambdas using template parameters (`template <typename F> void run(F&& func)`) so the compiler can inline the code directly and avoid heap allocations.

---

## 4. Concurrency & Multithreading

Concurrency means letting your program do multiple things at the same time (e.g., one thread grabs frames from a camera sensor while another thread processes them).

### 4.1 std::thread Lifecycle
When you create a `std::thread`, a new OS thread is spawned immediately.
*   **The Join Rule**: Before a `std::thread` object is destroyed, you **must** call `.join()` (wait for it to finish) or `.detach()` (let it run in the background). 
*   If you forget, `std::terminate()` is called and your program crashes instantly.
*   **RAII Solution**: Write a helper class (like `ThreadGuard`) to automatically join the thread when it goes out of scope.

```cpp
#include <thread>
#include <iostream>

class ThreadGuard {
    std::thread t_;
public:
    explicit ThreadGuard(std::thread t) : t_(std::move(t)) {}
    ~ThreadGuard() {
        if (t_.joinable()) {
            t_.join(); // Safely joins thread before destruction
        }
    }
    // Disable copying
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
};

void workerTask() {
    std::cout << "Worker thread running...\n";
}

int main() {
    ThreadGuard guard(std::thread(workerTask));
    // Thread will be joined automatically when guard goes out of scope here
}
```

### 4.2 Mutexes & C++17 `std::scoped_lock`
A `std::mutex` (Mutual Exclusion) ensures that only one thread can access a shared resource at a time.
*   **Deadlock**: Happens when Thread A holds Mutex 1 and waits for Mutex 2, while Thread B holds Mutex 2 and waits for Mutex 1. Both threads freeze forever.
*   **`std::scoped_lock` (C++17)**: A safe lock manager that can lock multiple mutexes at once without causing a deadlock.

```cpp
#include <mutex>

std::mutex sensorMtx;
std::mutex bufferMtx;

void safeUpdate() {
    // Safely locks both mutexes simultaneously without deadlocking
    std::scoped_lock lock(sensorMtx, bufferMtx);
    // Safe to modify shared resources
}
```

### 4.3 std::atomic & Memory Models
If one thread reads a variable while another thread writes to it, it causes a **data race** (corrupted data). `std::atomic` variables prevent this without the slow overhead of a mutex.

#### CPU Reordering
To run faster, modern CPUs do not execute operations in the exact order you wrote them in code, and they write to memory asynchronously using buffers. `std::memory_order` constants let you control this behavior.

```
+--------------+                   +--------------+
|    CPU 1     |                   |    CPU 2     |
| +----------+ |                   | +----------+ |
| |Store Buf | |                   | |Store Buf | |
| +----+-----+ |                   | +----+-----+ |
+------|-------+                   +------|-------+
       |   (Asynchronous flush)           |
+------v----------------------------------v-------+
|                 Shared Cache                    |
+-------------------------------------------------+
```

1.  **`memory_order_seq_cst` (Default)**: Safest, but slowest. Forces a strict, global order across all threads.
2.  **`memory_order_relaxed`**: Fastest. Only guarantees that the atomic variable itself is updated safely. No restrictions on surrounding reads/writes. Great for counters.
3.  **`memory_order_acquire` (Read)** & **`memory_order_release` (Write)**: Ensures that anything written before the "release" is guaranteed to be visible to the thread doing the "acquire".

```cpp
#include <atomic>
#include <thread>
#include <cassert>

std::atomic<bool> ready{false};
int sensorData = 0;

void producer() {
    sensorData = 100; // Normal write
    ready.store(true, std::memory_order_release); // Release barrier: Flushes sensorData to memory
}

void consumer() {
    while (!ready.load(std::memory_order_acquire)) {
        // Spin lock: Wait for ready to become true
    }
    assert(sensorData == 100); // Guaranteed to succeed!
}
```

### 4.4 Condition Variables (`std::condition_variable`)
A condition variable lets a thread sleep (use 0% CPU) until another thread signals it to wake up.
*   **Spurious Wakeup**: A waiting thread can occasionally wake up by itself for no reason. 
*   **Solution**: Always pass a "condition check" (a predicate/lambda) to `wait()`.

```cpp
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool frameReady = false;

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    
    // Thread sleeps here. It wakes up when cv is notified, but stays awake
    // ONLY if frameReady is true. This protects against spurious wakeups.
    cv.wait(lock, [] { return frameReady; });
    
    // Process frame...
}

// when frameReady = true ? 
// write program when frameReady becomes true then it will notify to consumer thread
// and consumer thread will process the frame , consumer thread should be in wait state until 

void producer() {
    frameReady = true;
    cv.notify_all();
}


int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}
```

### 4.5 Futures and Promises
A `std::promise` (write end) and `std::future` (read end) form a one-way channel to pass values between threads. Calling `.get()` on a future blocks the thread until the promise has set the value.

```cpp
#include <future>
#include <iostream>
#include <thread>

void calculateValue(std::promise<int> prom) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    prom.set_value(42); // Send value
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    
    std::thread t(calculateValue, std::move(prom));
    
    std::cout << "Waiting for result...\n";
    int result = fut.get(); // Blocks until worker thread calls set_value()
    std::cout << "Result: " << result << '\n'; // Prints: Result: 42
    
    t.join();
}
```

---

## 5. Step-by-Step Dry Runs & ASCII Diagrams

### 5.1 Dry Run: Fold Expression Expansion
Let's see what the compiler does under the hood when you write:
```cpp
template <typename... Args>
auto sum(Args... args) {
    return (args + ...);
}
int result = sum(10, 20, 30);
```

#### Step 1: Instantiation (Compile-time)
The compiler sees three integer arguments and generates a concrete function:
```cpp
int sum(int arg1, int arg2, int arg3);
```

#### Step 2: AST Expansion (Compile-time)
The compiler expands the expression `(args + ...)` into:
```cpp
return (10 + (20 + 30));
```

#### Step 3: Execution (Runtime)
1.  Computes `20 + 30` which equals `50`.
2.  Computes `10 + 50` which equals `60`.
3.  Returns `60`.

---

### 5.2 Dry Run: Condition Variable Wait-Wake Sequence
How a Producer and Consumer interact using `std::condition_variable`:

```
Consumer Thread                                 Producer Thread
-----------------                               ---------------
1. Locks the mutex.
2. Calls cv.wait(lock, predicate).
3. Predicate fails (no data ready).
4. cv.wait automatically unlocks 
   the mutex and puts the thread to sleep.
                                                5. Locks the mutex.
                                                6. Prepares the data.
                                                7. Sets predicate = true.
                                                8. Unlocks the mutex.
                                                9. Calls cv.notify_one().
10. Consumer wakes up.
11. Re-acquires the mutex.
12. Checks predicate again (succeeds).
13. cv.wait() returns successfully.
14. Processes data and unlocks mutex.
```

---

## 6. 30 Core Interview Questions & Answers

### Q1: Why can we not partially specialize a function template?
**Ans**: C++ rules do not allow it because overload resolution rules are already too complex. Instead, you can overload functions, or if you must have partial specialization, wrap the function inside a helper class template (which *can* be partially specialized).

### Q2: What is Class Template Argument Deduction (CTAD) and how do you write a custom deduction guide?
**Ans**: CTAD (C++17) allows the compiler to guess template types from constructor arguments. If the compiler needs help, you write a custom deduction guide:
```cpp
template <typename T>
struct Buffer {
    Buffer(T* data, size_t size) {}
};
// Guide: If constructor is called with (T*, size_t), deduce Buffer<T>
template <typename T>
Buffer(T*, size_t) -> Buffer<T>;
```

### Q3: Explain compile-time recursion vs. Fold Expressions.
**Ans**: Compile-time recursion instantiates a new template function for every recursive step, making compiler memory usage high and compile times slow. Fold expressions (C++17) generate a single flat expression directly in the syntax tree, making compiles faster and code cleaner.

### Q4: What is the difference between `std::vector::reserve` and `std::vector::resize`?
**Ans**:
*   `reserve(n)`: Allocates raw memory block for $n$ elements, but does not construct objects. `size` is unchanged, `capacity` becomes $n$.
*   `resize(n)`: Changes `size` to $n$. If $n > size$, default-constructs new elements. If $n < size$, deletes excess elements.

### Q5: How does `std::unordered_map` handle hash collisions?
**Ans**: It uses separate chaining. When multiple keys hash to the same bucket index, the map chains them together into a linked list at that bucket.

### Q6: What is iterator invalidation? Give an example.
**Ans**: Iterator invalidation is when an iterator points to a memory location that has been moved or deleted.
```cpp
std::vector<int> v = {1, 2};
auto it = v.begin();
v.push_back(3); // Might trigger reallocation! 
// 'it' is now invalid. Accessing *it causes undefined behavior (crash).
```

### Q7: Why is `std::map` avoided in real-time loops?
**Ans**: `std::map` allocates memory on the heap for every single node. This fragments the heap and causes cache misses because nodes are scattered across random memory locations.

### Q8: What does the `mutable` keyword do when applied to a lambda?
**Ans**: By default, lambdas cannot modify variables captured by value. Adding `mutable` removes the `const` restriction on the lambda's call operator, allowing you to modify value-captured variables.

### Q9: Why is capturing `this` by value (`[*this]`) important in asynchronous tasks?
**Ans**: Capturing `[this]` captures a raw pointer. If the parent object is destroyed before the async task runs, it results in a Use-After-Free crash. Capturing `[*this]` copies the entire object, keeping a safe copy alive inside the lambda.

### Q10: What is the overhead of using `std::function`?
**Ans**: It has two main overheads: (1) Heap allocation if the captured payload exceeds its small-object buffer, and (2) Virtual call indirection (pointer referencing) which prevents the compiler from inlining the function.

### Q11: Explain the lifecycle of a `std::thread`. What happens if a `std::thread` is destroyed while it is still joinable?
**Ans**: A thread runs as soon as it is constructed. If the thread object goes out of scope and is destroyed without calling `.join()` or `.detach()` first, the program crashes immediately via `std::terminate()`.

### Q12: What is the difference between `std::lock_guard` and `std::unique_lock`?
**Ans**:
*   `std::lock_guard`: Lightweight, strictly scoped. Lock on construct, unlock on destruct. Non-copyable, non-movable.
*   `std::unique_lock`: More flexible. Can lock and unlock manually, supports deferred locking, timeouts, and can be moved.

### Q13: How does C++17 `std::scoped_lock` prevent deadlocks?
**Ans**: It takes multiple mutexes and locks them all at once. Internally, it uses a deadlock avoidance algorithm that tries to lock all mutexes; if it fails to lock one, it releases the ones it has already locked and tries again.

### Q14: Explain the difference between `std::atomic` and `volatile` in C++.
**Ans**:
*   `std::atomic`: Guarantees thread-safe atomic access and prevents CPU instruction reordering. Used for thread synchronization.
*   `volatile`: Tells the compiler not to optimize away reads/writes (useful for memory-mapped hardware). It does **not** make code thread-safe or prevent CPU reordering.

### Q15: What is a spurious wakeup in a condition variable? How do you prevent it?
**Ans**: A thread waiting on a condition variable wakes up without receiving a signal. Prevent it by passing a validation condition (predicate lambda) to `cv.wait()`:
```cpp
cv.wait(lock, [] { return dataReady; });
```

### Q16: Describe the difference between `std::async` with `std::launch::async` vs `std::launch::deferred`.
**Ans**:
*   `std::launch::async`: Runs the task on a new, separate thread immediately.
*   `std::launch::deferred`: Runs the task lazily on the same thread when `.get()` or `.wait()` is called.

### Q17: What is the difference between `std::promise::set_value` and `std::promise::set_value_at_thread_exit`?
**Ans**:
*   `set_value`: Makes the promise result available immediately, waking up any thread waiting on the future.
*   `set_value_at_thread_exit`: Sets the value but delays notifying the future until the thread actually terminates (prevents issues with thread-local variables).

### Q18: What is Cache Line bouncing and how do atomics affect it?
**Ans**: When multiple CPU cores repeatedly write to atomic variables located close to each other in memory (on the same 64-byte cache line), the CPU must keep copying that cache line back and forth between cores, degrading performance.

### Q19: What is lock-free programming?
**Ans**: Writing multithreaded code that does not block threads using locks (mutexes). Instead, it uses atomic CPU instructions like Compare-And-Swap (CAS) to guarantee progress.

### Q20: Explain the difference between `acquire` and `release` memory orders.
**Ans**:
*   `release`: Guarantees that all preceding writes are completed and visible before this store happens.
*   `acquire`: Guarantees that all subsequent reads cannot see state from before this load.

### Q21: What is the C++17 `inline` variable specifier?
**Ans**: It allows you to define global/static variables in header files without getting "multiple definition" errors at link time when the header is included in multiple source files.

### Q22: How does `std::packaged_task` simplify multithreading?
**Ans**: It wraps any callable target (function, lambda) and automatically handles setting the `std::promise` value/exception once the task runs to completion.

### Q23: Why should we use `noexcept` on move constructors?
**Ans**: If a move constructor is not marked `noexcept`, containers like `std::vector` will fall back to copying elements during reallocation to maintain safety, which is slower.

### Q24: What is Template Metaprogramming (TMP)?
**Ans**: Running computations or checks at compile-time using templates, moving runtime CPU costs to compile-time.

### Q25: What is the difference between `std::mutex::lock` and `std::mutex::try_lock`?
**Ans**:
*   `lock()`: Blocks the calling thread indefinitely until the lock is acquired.
*   `try_lock()`: Tries to acquire the lock. Returns `true` immediately if successful, or `false` if the lock is held by another thread, without blocking.

### Q26: Explain the C++17 `std::string_view`. How does it help optimize code?
**Ans**: It is a lightweight, non-owning view of a string (contains a pointer and a length). It avoids expensive heap allocations and copying when parsing substrings.

### Q27: How does `std::shared_ptr` maintain reference counts?
**Ans**: It uses a heap-allocated "control block" containing the reference count. Modifying the count is thread-safe because it uses atomic operations.

### Q28: What is the danger of circular references with `std::shared_ptr`?
**Ans**: If Object A points to Object B, and Object B points to Object A using `std::shared_ptr`, their reference counts never reach zero. This causes a permanent memory leak. Resolve it by using `std::weak_ptr`.

### Q29: What is SFINAE (Substitution Failure Is Not An Error)?
**Ans**: If a compiler fails to substitute a type parameter in a template overload, it does not stop compilation with an error. It simply discards that overload and tries other matching templates.

### Q30: What is the difference between `std::atomic_flag` and `std::atomic<bool>`?
**Ans**: `std::atomic_flag` is guaranteed to be lock-free on all platforms and only supports set/clear operations. `std::atomic<bool>` supports standard loads/stores but is not guaranteed to be lock-free on all hardware.

---

## 7. Common Bugs, Debugging & Best Practices

### 7.1 Dynamic Memory Allocation in Real-Time Loops
*   **Bug**: Calling `malloc` or `new` (directly or indirectly via `std::vector::push_back`) inside a real-time thread or interrupt service routine (ISR).
*   **Result**: Random latency spikes and frame drops when the memory allocator searches for free blocks or blocks behind other threads.
*   **Fix**: Pre-allocate all memory buffers on startup or use pool allocators.

### 7.2 ThreadSanitizer (TSAN) & AddressSanitizer (ASAN)
Compile your code with sanitizers to find memory safety issues and data races before deploying to production.
```bash
# Enable AddressSanitizer (ASAN - detects use-after-free, buffer overflows)
g++ -fsanitize=address -g main.cpp -o main

# Enable ThreadSanitizer (TSAN - detects data races/concurrency bugs)
g++ -fsanitize=thread -g main.cpp -lpthread -o main
```

### 7.3 Core Guidelines for Low-Latency C++
1.  **Zero Heap Rule**: Never allocate memory on the heap in high-frequency critical paths.
2.  **Use `noexcept`**: Always mark move constructors and destructors `noexcept`.
3.  **Avoid `std::function`**: Pass lambdas using template parameters to enable full compiler optimization and inlining.
4.  **Pre-allocate STL containers**: Always use `.reserve()` before inserting items into a `std::vector`.
