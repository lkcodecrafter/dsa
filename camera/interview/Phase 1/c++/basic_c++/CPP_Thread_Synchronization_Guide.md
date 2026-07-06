# C++ Thread Synchronization & System Programming Notes

## Topics Covered

1. Process vs Thread
2. Race Condition
3. Mutex
4. Deadlock
5. Semaphore
6. Condition Variable
7. Producer Consumer
8. Thread Lifecycle
9. Stack vs Heap
10. Pointer Sharing
11. Smart Pointers
12. Virtual Functions
13. Important Interview Questions

---

## Process vs Thread

Process:
- Independent execution unit
- Own memory

Thread:
- Shares process memory
- Lightweight

```c++
Example:

std::thread t1(func);

void func() {
    std::cout << "Hello" << std::endl;


void threadExample() {
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();
}


#include <iostream>
#include <thread>

// Define a simple function
void greet() {
    std::cout << "Thread: Hello from the function!\n";
}

int main() {
    // Call the function using a thread
    std::thread myThread(greet);

    // Wait for the thread to finish
    myThread.join();

    std::cout << "Main: Thread finished execution.\n";
    return 0;
}

```

---

## Race Condition

Multiple threads modify shared data simultaneously.

Example:

int counter = 0;
counter++;

Solution:
Use mutex.

---

## Mutex

Only one thread enters critical section.

std::mutex mtx;

mtx.lock();
counter++;
mtx.unlock();

Recommended:

std::lock_guard<std::mutex> lock(mtx); 

because it automatically releases the mutex when it goes out of scope, preventing deadlocks if an exception occurs or if you forget to call unlock().



---

## Deadlock

Thread A waits for Thread B.
Thread B waits for Thread A.

System stuck forever.

Prevention:
- Lock ordering
- std::lock()
- Avoid nested locks

---

## Semaphore

Resource counting mechanism. - Allows multiple threads to access a limited number of resources. Means to control access to a common resource in a concurrent system.
What is a semaphore? A semaphore is a synchronization primitive that is used to control access to a common resource in a concurrent system. It is a variable or abstract data type that provides a simple but useful abstraction for controlling access by multiple threads to a common resource in a parallel programming environment. In simple terms, a semaphore is a counter that is used to manage access to a shared resource by multiple threads. It can be used to signal between threads, allowing one thread to notify another thread that a certain condition has been met or that a resource is available.

```c++
#include <semaphore.h>

sem_t sem;

Semaphore initialization:
```c++
std::counting_semaphore<5> sem;

// Simple program in semaphore
#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

std::counting_semaphore<3> sem(3); // Allow 3 threads at a time

void worker(int id) {
    sem.acquire(); // Decrement counter
    std::cout << "Thread " << id << " acquired semaphore\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " releasing semaphore\n";
    sem.release(); // Increment counter
}

int main() {
    std::thread t1(worker, 1), t2(worker, 2), t3(worker, 3), t4(worker, 4);
    t1.join(); t2.join(); t3.join(); t4.join();
    return 0;
}


// Output 
Thread 1 acquired semaphore
Thread 2 acquired semaphore
Thread 3 acquired semaphore
Thread 1 releasing semaphore
Thread 4 acquired semaphore
Thread 2 releasing semaphore
Thread 3 releasing semaphore
Thread 4 releasing semaphore


```

Difference:

Mutex:
- One owner
- Binary

Semaphore:
- Multiple resources
- Counting

---

## Condition Variable - Synchronization Primitive

Initialization:
```c++
std::condition_variable cv;
std::mutex mtx;
```

What is condtion variable A condition variable is a synchronization primitive that allows multiple threads to wait until a specific condition is met. It is always used in conjunction with a `std::mutex` to avoid race conditions where one thread starts waiting just as another thread signals.

Key functions:
- `wait()`: Atomically releases the mutex and suspends execution of the thread.
- `notify_one()`: Wakes up one waiting thread.
- `notify_all()`: Wakes up all waiting threads.

so is it same as semarphore No, they are different.

**Condition Variable vs Semaphore:**

1.  **Memory/State:** A Semaphore maintains an internal counter (state). Even if a signal is sent before a thread starts waiting, the semaphore "remembers" it. A Condition Variable has no internal counter; if `notify_one()` is called and no thread is currently waiting, the signal is lost.
2.  **Mutex Requirement:** A Condition Variable **must** be used with a `std::unique_lock` and a mutex to protect the shared condition. A Semaphore is self-contained and does not require an external mutex for its internal counter.
3.  **Purpose:** Semaphores are generally used for resource counting (e.g., "I have 3 printers available"). Condition Variables are used for event signaling (e.g., "The data is now ready for processing").

---

### Condition Variable Example

Wait:
```c++
cv.wait(mtx);

```
```c++

// Write a sample programm #include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready) cv.wait(lck); // Wait until ready is true
    std::cout << "Thread " << id << " executing\n";
}

void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all(); // Wake up all waiting threads
}

int main() {
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) threads[i] = std::thread(print_id, i);

    std::cout << "5 threads ready to race...\n";
    go(); // Signal all threads to proceed

    for (auto& th : threads) th.join();
    return 0;
}

```

Used for wait/notify.

cv.wait(lock);
cv.notify_one();

---

## Producer Consumer

Producer:
Creates data

Consumer:
Consumes data

Camera Example:

Sensor
-> Buffer Queue
-> HAL
-> Framework

---

## Stack vs Heap

Stack:
Automatic cleanup

Heap:
Dynamic allocation

int x = 10;

int* p = new int(10);

---

## Pointer Sharing

Frame* frame = new Frame();

queue.push(frame);

No copy occurs.
Same memory shared.

---

## Smart Pointers

unique_ptr
shared_ptr
weak_ptr

---

## Virtual Functions

Runtime polymorphism.

class Base {
public:
    virtual void show();
};

---

## Important Interview Questions

- Race Condition
- Mutex
- Semaphore
- Deadlock
- Condition Variable
- Producer Consumer
- Stack vs Heap
- Virtual Function
- Smart Pointer
- Dangling Pointer
- Thread Synchronization

---

## Camera HAL Mapping

Frame Buffer -> Struct
Memory Sharing -> Pointer
Buffer Queue -> Producer Consumer
Thread Safety -> Mutex
Wakeup -> Condition Variable
