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

Resource counting mechanism.

Difference:

Mutex:
- One owner
- Binary

Semaphore:
- Multiple resources
- Counting

---

## Condition Variable

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
