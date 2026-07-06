# Phase 3 - Linux & Embedded Systems Internals

> Embedded Camera & Real-Time Systems Interview Masterclass (Simplified Edition)

This guide covers core operating system internals, virtual memory, scheduling, inter-process communication (IPC), compilation formats (ELF), and essential debugging/profiling tools in Linux and Android. It is written in simple, plain English with straightforward examples to help you ace your embedded and camera systems interviews.

---

## Table of Contents
1. [Process & Thread Internals](#1-process--thread-internals)
2. [Virtual Memory](#2-virtual-memory)
3. [CPU Scheduling & Real-Time Policies](#3-cpu-scheduling--real-time-policies)
4. [Inter-Process Communication (IPC)](#4-inter-process-communication-ipc)
5. [ELF Binary Format](#5-elf-binary-format)
6. [Debugging & Profiling Tools (gdb, strace, dmesg, logcat)](#6-debugging--profiling-tools)
7. [Step-by-Step Dry Runs & ASCII Diagrams](#7-step-by-step-dry-runs--ascii-diagrams)
8. [30 Core Linux & Embedded Interview Questions](#8-30-core-linux--embedded-interview-questions)

---

## 1. Process & Thread Internals

An operating system runs programs as either **processes** or **threads**. Understanding how they differ in memory allocation and management is a core interview requirement.

### 1.1 Process vs. Thread
*   **Process**: A running instance of a program. It is completely isolated from other processes. If one process crashes, it does not affect others.
*   **Thread**: A lightweight unit of execution *within* a process. A process can have multiple threads, and they all share the parent process's memory space. If a thread crashes (e.g. due to a null pointer), it crashes the entire process.

#### Shared vs. Private Resources
When threads run inside a process, they share some resources but keep others completely private:

| Resource | Shared by Threads? | Notes |
| :--- | :--- | :--- |
| **Code (Text)** | Yes | All threads execute instructions from the same compiled binary. |
| **Global/Static Variables**| Yes | Declared outside functions; any thread can read/write them (requires locking!). |
| **Heap Memory** | Yes | Dynamically allocated memory (`malloc`/`new`) is shared. |
| **File Descriptors (FD)** | Yes | If Thread A opens a file or camera sensor device, Thread B can read from it. |
| **CPU Registers** | **No (Private)** | Each thread has its own CPU registers, including the Program Counter (PC). |
| **Stack Space** | **No (Private)** | Each thread gets its own small stack for local variables and function calls. |

### 1.2 Process Control Block (PCB) vs. Thread Control Block (TCB)
The OS kernel manages processes and threads using struct data structures:
*   **Process Control Block (PCB)**: Stores process information (Process ID / PID, memory mapping tables, list of open files, parent PID).
*   **Thread Control Block (TCB)**: Stores thread-specific details (Thread ID / TID, saved CPU registers, stack pointer, scheduling priority).

### 1.3 How the Kernel Creates Them: `fork()` vs. `vfork()` vs. `clone()`
In Linux, the creation of processes and threads is handled by system calls:
*   **`fork()`**: Creates a child process by copying the parent. Linux uses **Copy-on-Write (COW)**: it doesn't copy memory immediately; instead, parent and child share the same physical memory until one of them tries to write to it, at which point the OS copies that specific page.
*   **`vfork()`**: A legacy optimization where the parent process is completely frozen until the child calls `exec()` or `exit()`. The child uses the parent's memory directly. (Rarely used now as `fork()` + COW is highly optimized).
*   **`clone()`**: The modern, unified Linux system call that creates both processes and threads. It allows you to specify exactly what resources to share with the child via flags:
    *   **Create a Thread**: `clone(..., CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND, ...)` (shares memory, files, and signals).
    *   **Create a Process**: `clone(..., SIGCHLD, ...)` (shares nothing, acts like `fork()`).

```cpp
#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork(); // Splits program into two processes

    if (pid == 0) {
        // Child process
        std::cout << "Child process. PID: " << getpid() << ", Parent PID: " << getppid() << '\n';
    } else if (pid > 0) {
        // Parent process
        std::cout << "Parent process. PID: " << getpid() << ", Child PID: " << pid << '\n';
    } else {
        std::cerr << "Fork failed!\n";
    }
    return 0;
}
```

---

## 2. Virtual Memory

Every process acts as if it has exclusive access to a massive, contiguous range of memory (e.g. 4GB on 32-bit systems). This address range is called **Virtual Memory**. In reality, physical RAM is shared among all processes and is heavily fragmented.

### 2.1 Virtual-to-Physical Translation
The translation from a virtual memory address to a physical RAM address is performed by hardware and software working together:
*   **MMU (Memory Management Unit)**: A hardware component inside the CPU that intercept every memory access and translates virtual addresses into physical ones on-the-fly.
*   **Page Tables**: Data tables stored in physical RAM that act as a directory mapping virtual memory units (Pages) to physical memory units (Frames). A standard page size is **4KB**.
*   **TLB (Translation Lookaside Buffer)**: A small, ultra-fast hardware cache located directly in the CPU. It remembers the most recent page translations.
    *   **TLB Hit**: The translation is cached in the TLB. Translation takes almost 0 cycles.
    *   **TLB Miss**: The translation is not cached. The CPU must perform a "Page Table Walk" (searching RAM tables), which is slow.

```
Virtual Memory Mapping:
+-------------------+                    +-----------------------+
|  Virtual Address  |                    | Physical RAM Address  |
|  [Page Number]    |---( TLB HIT? )---->|  [Frame Number]       |
+-------------------+      | (Yes)       +-----------------------+
                           | (No: Page Walk)
                           v
                     +------------+
                     | Page Table | (in RAM)
                     +------------+
```

### 2.2 Page Faults
A **Page Fault** occurs when a program tries to access a virtual page that does not currently have a valid mapping in physical RAM. The CPU triggers an interrupt, letting the OS kernel handle it:
*   **Minor Page Fault**: The requested memory page is already loaded in physical RAM (e.g. shared library memory or a Copy-on-Write page), but it is not mapped in this process's page table. The kernel simply adds a mapping entry. This is resolved very quickly.
*   **Major Page Fault**: The page is not in physical memory at all. The OS must halt the program, read the data from disk (like swap space or the binary executable file), allocate a frame in RAM, map it, and then resume the program. This is extremely slow.
*   **Demand Paging**: An efficiency technique where the OS allocates physical memory for a program only when the program actually reads or writes to those pages.

---

## 3. CPU Scheduling & Real-Time Policies

A scheduler determines which thread gets to run on a CPU core at any given millisecond.

### 3.1 Preemptive vs. Cooperative Scheduling
*   **Cooperative Scheduling**: A running thread keeps control of the CPU until it voluntarily releases it (e.g., calls `sleep()`, blocks on IO, or calls `yield()`). If a thread hangs in an infinite loop, the entire OS freezes.
*   **Preemptive Scheduling**: The OS kernel controls the CPU. It uses periodic timer interrupts (e.g., every 1ms) to pause a running thread, save its state, and run another thread. This ensures system stability.

### 3.2 Real-Time Scheduling Policies (Linux POSIX)
For standard programs, Linux uses a fair-share scheduler (CFS). However, for time-critical components like camera sensor frame acquisition, Linux offers Real-Time (RT) scheduling policies:
*   **`SCHED_FIFO` (First-In, First-Out)**: A thread running under this policy will run until it is blocked by IO, voluntarily yields, or is preempted by a *higher* priority RT thread. There is no time-slicing.
*   **`SCHED_RR` (Round Robin)**: Similar to `SCHED_FIFO`, but each thread is given a maximum time slice (e.g., 10ms). If multiple threads have the exact same RT priority, they alternate execution when their time slice expires.

### 3.3 Priority Inversion & Priority Inheritance
Real-time systems can suffer from a critical scheduling bug called **Priority Inversion**:

1.  **Low Priority Thread (L)** locks a shared resource (e.g. Mutex).
2.  **High Priority Thread (H)** starts up and wants the lock. It blocks and goes to sleep waiting for **L** to release it.
3.  **Medium Priority Thread (M)** starts up. Since **M** does not need the lock, and its priority is higher than **L**, the scheduler runs **M** instead of **L**.
4.  **Result**: **L** is preempted by **M** and cannot run to finish its work and release the lock. Consequently, **H** is blocked indefinitely!

#### The Fix: Priority Inheritance
When **H** blocks waiting for the lock held by **L**, the OS temporarily boosts **L**'s scheduling priority to match **H**'s priority. This allows **L** to run immediately, bypass **M**, release the lock, and immediately drop back to its original low priority, allowing **H** to execute.

```
Priority Inversion (No Inheritance):
Time --->
L-thread: [Locks Mutex]--------------------------------------[Blocked by M]----> (Stuck!)
M-thread:              [Starts & Preempts L]==================================> (Runs)
H-thread:                           [Needs Mutex - BLOCKED by L]---------------> (Stuck!)

Priority Inheritance (The Fix):
Time --->
L-thread: [Locks Mutex]------------[Inherits H Priority]======[Releases Mutex]--> (Normal L)
M-thread:              [Preempted]----------------------------[Runs now]======>
H-thread:                           [Needs Mutex - BLOCKED]===[Acquires Lock]===>
```

---

## 4. Inter-Process Communication (IPC)

Because processes are isolated by virtual memory, they cannot read or write each other's memory directly. They must use IPC mechanisms managed by the kernel.

### 4.1 Common IPC Mechanisms
1.  **Pipes (Unidirectional)**:
    *   A simple buffer in kernel memory. Data goes in one end (write) and comes out the other (read).
    *   **Anonymous Pipes**: Used only between related processes (parent-child). Created with `pipe()`.
    *   **Named Pipes (FIFOs)**: Appear as files in the file system, allowing completely unrelated processes to communicate.
2.  **Shared Memory (Fastest)**:
    *   The kernel maps the same physical RAM frame into the virtual address spaces of two different processes.
    *   **Pros**: Zero-copy. Data written by Process A is instantly visible to Process B because no data copying between user space and kernel space occurs.
    *   **Cons**: No built-in synchronization. If both write at the same time, memory corruption occurs. Developers must use mutexes or semaphores to coordinate access.
3.  **Message Queues**:
    *   A message list managed by the kernel. Processes send structured data pack arrays ("messages") to the queue.
    *   Unlike pipes, message queues are packet-oriented, meaning boundaries between messages are preserved.
4.  **Unix Domain Sockets (Bidirectional)**:
    *   Similar to TCP/IP network sockets, but bypass the network stack entirely.
    *   Optimized for fast, bidirectional communication between processes on the local machine.

### 4.2 Synchronization Primitives
*   **Mutex**: Binary lock (Locked/Unlocked) with a strict concept of ownership. Only the exact thread that locked the mutex can unlock it. Best for protecting code blocks (critical sections).
*   **Semaphore**: A counter-based signaling mechanism. 
    *   **Binary Semaphore**: Can only be 0 or 1. Unlike a mutex, *any* thread or process can unlock (signal) a semaphore, making it ideal for event notification between threads/processes.
    *   **Counting Semaphore**: Initialized to a value $N$, representing $N$ available units of a resource.

### 4.3 Embedded & Android Specific IPC
*   **Android Binder**: Android's core IPC mechanism. Instead of copying data to the kernel and then to the target process (which takes 2 copy operations), Binder uses shared memory mapping (`mmap`) to copy data directly from the sender's user space to the receiver's user space in a **single copy operation**.
*   **dmabuf (DMA Buffer) & ION**: Crucial for zero-copy camera frame processing. Camera sensors generate massive image frames (e.g. 12MB). Copying this data between the Camera driver, ISP, and GPU would freeze the system. `dmabuf` allocates physical memory buffers once and passes *file descriptors* pointing to that buffer. This allows hardware components and user processes to read/write the frames with zero CPU copy overhead.

---

## 5. ELF Binary Format

The compiled binary file format on Linux is called **ELF (Executable and Linkable Format)**. 

### 5.1 ELF Core Sections
An ELF file is divided into distinct sections that dictate where code and data reside in memory once loaded:

```
ELF File Layout:
+--------------------------------------+
|             ELF Header               | -> Architecture, entry point address
+--------------------------------------+
|      .text Section (Read-Only)       | -> Compiled CPU instructions
+--------------------------------------+
|    .rodata Section (Read-Only)       | -> Constant variables, string literals
+--------------------------------------+
|     .data Section (Read-Write)       | -> Initialized global & static variables
+--------------------------------------+
|      .bss Section (Read-Write)       | -> Uninitialized variables (0 initialized)
+--------------------------------------+
```

*   **`.text`**: Read-only machine code. The CPU executes instructions directly from here.
*   **`.rodata`**: Read-only data, such as hardcoded string literals (e.g. `printf("Hello World\n")`).
*   **`.data`**: Initialized global and static variables. Takes up space in the binary file because the initial values must be saved. (e.g. `int global_var = 100;`).
*   **`.bss`**: Uninitialized global and static variables (e.g. `int buffer[1024];`). The OS automatically fills this segment with zeros upon loading. To save disk space, this section takes up almost 0 bytes inside the compiled binary file on disk.

### 5.2 Linking: Static vs. Dynamic
*   **Static Linking**: 
    *   The linker merges all dependent libraries directly into the final executable at compile time.
    *   **Pros**: Self-contained executable; no runtime library dependency errors.
    *   **Cons**: Large file size; memory is wasted if multiple running programs use the same library code.
*   **Dynamic Linking**:
    *   The executable contains only references to shared libraries (e.g. `.so` files on Linux/Android).
    *   When the program starts, the OS dynamic loader (`ld.so`) maps the shared libraries into the process's virtual memory space.
    *   **Pros**: Small file size; multiple programs share the same physical memory space containing the library code.

---

## 6. Debugging & Profiling Tools

Debugging low-level embedded software requires a strong grasp of command-line tools.

### 6.1 GDB (GNU Debugger)
GDB is the standard debugger for C/C++ applications.
*   **Running**: `gdb ./my_program`
*   **Essential Commands**:
    *   `break file.cpp:42` (or `b`): Sets a breakpoint at line 42.
    *   `run` (or `r`): Starts the program execution.
    *   `step` (or `s`): Steps into a function call.
    *   `next` (or `n`): Steps over a function call.
    *   `print x` (or `p`): Displays the current value of variable `x`.
    *   `backtrace` (or `bt`): Prints the function call stack leading to the current line (crucial for finding where a crash occurred).
*   **Core Dumps**: When a program crashes, the OS can save a snapshot of its memory to a "core" file. You can load this file into GDB to investigate the exact crash state:
    ```bash
    gdb ./my_program core
    (gdb) bt # Show stack trace of the crash
    ```

### 6.2 strace (System Call Tracer)
`strace` intercepts and records the system calls made by a process. It is invaluable for diagnosing file access errors, device driver issues, and locking hangs without source code.
*   **Trace a program from startup**: `strace ./my_program`
*   **Filter specific system calls**: `strace -e open,read,write ./my_program`
*   **Attach to an already running process**: `strace -p <PID>`
*   **Get summaries (time spent in each syscall)**: `strace -c ./my_program`

### 6.3 dmesg (Kernel Log Buffer)
`dmesg` prints the kernel's message ring buffer. In embedded systems, this is where device drivers (like camera sensors or ISP drivers) print initialization errors, hardware failures, or memory out-of-memory (OOM) kills.
*   **Print all logs**: `dmesg`
*   **Follow logs in real-time**: `dmesg -w`
*   **Search for camera-specific errors**: `dmesg | grep -i camera`

### 6.4 logcat (Android Logging System)
On Android systems, `logcat` is the command used to view system and application logs.
*   **View real-time logs**: `adb logcat`
*   **Show only error logs**: `adb logcat *:E`
*   **Filter logs for Camera HAL**: `adb logcat | grep -i Camera`

---

## 7. Step-by-Step Dry Runs & ASCII Diagrams

### 7.1 Dry Run: Accessing a Virtual Memory Address
What happens when a CPU instruction executes `int x = *ptr;`?

```
CPU Core              MMU (Hardware)            TLB Cache (Fast)         RAM (Slow)
--------              --------------            ----------------         ----------
1. Requests Virtual 
   Address (VAddr).
                      2. Checks TLB for VAddr.
                                                3. TLB HIT?
                                                   - (Yes) -> Return Physical Address (PAddr) immediately to MMU.
                                                   - (No)  -> Trigger Page Table Walk in RAM.
                                                                                4. Walk Page Table in RAM.
                                                                                5. Find PAddr mapping.
                                                                                6. Store translation in TLB.
                                                                                7. Return PAddr to MMU.
                      8. Access Physical RAM
                         at PAddr to load x.
```

---

### 7.2 Dry Run: Resolving a System Call (`read()` from camera sensor)
How does user code retrieve data from the hardware kernel driver?

```
User Space                                      Kernel Space
----------                                      ------------
1. Calls read(sensor_fd, buffer, size).
2. CPU transitions to privileged kernel mode 
   via software interrupt / syscall instruction.
                                                3. Kernel matches file descriptor to 
                                                   the Camera Driver file structure.
                                                4. Calls driver's read() function.
                                                5. Driver reads physical hardware register.
                                                6. Copies data to user 'buffer' memory.
                                                7. Returns number of bytes read.
8. CPU transitions back to User Mode.
9. read() returns in C++ program.
```

---

## 8. 30 Core Linux & Embedded Interview Questions

### Q1: What is the main difference between a process and a thread?
**Ans**: A process is a fully isolated execution unit with its own private virtual memory space and resources. A thread is an execution unit inside a process that shares memory, file descriptors, and heap space with sister threads, keeping only its stack and registers private.

### Q2: What is the role of the MMU?
**Ans**: The MMU (Memory Management Unit) is a hardware component in the CPU that translates virtual memory addresses requested by programs into physical memory addresses in RAM at runtime.

### Q3: Explain TLB Miss and its performance impact.
**Ans**: A TLB Miss occurs when the translation for a virtual address is not cached in the TLB. The CPU must walk the multi-level page tables in physical RAM, adding significant latency to memory access.

### Q4: What is the difference between a Minor and a Major Page Fault?
**Ans**: 
*   **Minor Page Fault**: The target page is in RAM but not mapped in the process's page table. Resolved quickly by adding the map entry.
*   **Major Page Fault**: The page is not in RAM at all. The OS must load it from disk (swap/storage), which is extremely slow.

### Q5: What is Copy-on-Write (COW)?
**Ans**: COW is an optimization used during `fork()`. Instead of copying the parent's memory pages to the child, the OS shares the physical memory pages as read-only. When either process attempts to write to a page, a page fault occurs, and the OS creates a physical copy of that page for the writing process.

### Q6: Why is `vfork()` deprecated or rarely used?
**Ans**: `vfork()` freezes the parent process while the child runs in the parent's address space. It was created to avoid copying memory before `exec()`. With modern `fork()` using Copy-on-Write, the copying overhead is minimized, making `vfork()` obsolete and dangerous.

### Q7: Explain priority inversion and how to solve it.
**Ans**: Priority inversion is when a low-priority thread holding a lock is preempted by a medium-priority thread, leaving a waiting high-priority thread blocked indefinitely. It is solved using **Priority Inheritance**, where the low-priority thread temporarily inherits the high-priority thread's priority level.

### Q8: What scheduling policy is best for low-latency audio or camera capture?
**Ans**: `SCHED_FIFO` or `SCHED_RR` (Real-Time policies) with high priority. They bypass standard fair-share scheduling, ensuring the time-critical thread preempts normal threads instantly.

### Q9: Why is shared memory the fastest IPC mechanism?
**Ans**: Shared memory maps physical memory frames directly into both processes' virtual address spaces. Communication requires zero data copying between user and kernel space, unlike pipes or queues which require copy operations.

### Q10: Why do we need synchronization when using shared memory?
**Ans**: Shared memory has no built-in protection. If multiple processes read and write simultaneously, it causes data races and memory corruption. Mutexes, semaphores, or atomic flags must be used to coordinate access.

### Q11: What is the difference between a mutex and a semaphore?
**Ans**: A mutex has ownership: only the thread that locked it can unlock it. A semaphore is a general counter/signaling mechanism without ownership; any thread can signal (increment) it, making semaphores ideal for inter-thread synchronization.

### Q12: How does Android Binder IPC optimize communication?
**Ans**: Binder maps a portion of the receiver's memory into kernel space. When a process sends data, the kernel copies it directly from the sender's user space into the receiver's mapped space, completing the IPC in a single memory copy operation.

### Q13: What is `dmabuf` and why is it used in camera pipelines?
**Ans**: `dmabuf` provides a framework for zero-copy buffer sharing between hardware drivers (like camera sensor, ISP, GPU) and user processes. It passes file descriptors representing physical memory buffers instead of copying the massive pixel frames.

### Q14: Explain the difference between `.data` and `.bss` sections in an ELF file.
**Ans**: 
*   `.data`: Stores initialized global/static variables. Takes up physical disk space in the compiled binary.
*   `.bss`: Stores uninitialized global/static variables. Takes up almost 0 space on disk; the OS zero-initializes this memory during loading.

### Q15: How does a dynamic loader (`ld.so`) work at program startup?
**Ans**: The OS loader reads the ELF program headers, maps the sections, and identifies shared libraries (`.so`). It calls the dynamic linker/loader (`ld.so`), which loads the libraries into memory and resolves symbol references (functions/variables) at runtime.

### Q16: What happens during static linking?
**Ans**: The linker copies the machine code of all library dependencies directly into the final executable binary. The output is self-contained but has a much larger file size.

### Q17: How do you check which system calls a program is hanging on?
**Ans**: Run `strace -p <PID>` to attach to the running hanging process and trace its active system calls in real-time.

### Q18: What is a core dump, and how do you analyze it?
**Ans**: A core dump is a file containing the memory image of a crashed process. It is analyzed using GDB: `gdb ./my_program core`, followed by the `backtrace` (or `bt`) command to inspect the call stack at the time of the crash.

### Q19: What tool would you use to verify if a camera sensor hardware driver probe failed?
**Ans**: Run the `dmesg` command (e.g. `dmesg | grep -i camera`) to inspect kernel driver initialization logs.

### Q20: How do you capture only error logs on an Android device?
**Ans**: Run `adb logcat *:E` to filter out everything except Error priority logs.

### Q21: What is the role of the CPU Program Counter (PC)?
**Ans**: The Program Counter is a CPU register that holds the virtual memory address of the next instruction to be executed by the current thread.

### Q22: What is thrashing in virtual memory?
**Ans**: Thrashing occurs when physical RAM is full, causing the OS to constantly swap memory pages in and out of disk storage. The system spends more time waiting for disk IO than executing instructions, causing extreme lag.

### Q23: Why is time-slicing absent in `SCHED_FIFO`?
**Ans**: `SCHED_FIFO` is a first-in-first-out real-time policy designed to let a critical thread run uninterrupted until it finishes its task, blocks, or yields. Time-slicing is omitted to avoid predictable execution disruption.

### Q24: What is a Named Pipe (FIFO)?
**Ans**: A Named Pipe is an IPC channel represented as a file node in the file system. It allows unrelated processes to communicate bidirectional-like by opening it as a standard file.

### Q25: Explain the `.text` segment in ELF.
**Ans**: The `.text` segment contains the compiled machine code instructions of the program. It is mapped as read-only and executable to prevent programs from accidentally modifying their own code.

### Q26: What GDB command is used to inspect variables?
**Ans**: The `print <variable>` command (or `p <variable>`).

### Q27: How does `mmap` work?
**Ans**: `mmap` maps files or device buffers directly into a process's virtual memory space. Reading/writing to this memory range translates directly to reading/writing the file, bypassing standard system calls.

### Q28: What is cooperative multitasking?
**Ans**: A multitasking style where the CPU scheduler relies on running threads to voluntarily yield execution time slices. If a thread behaves badly, it hangs the system.

### Q29: What is the purpose of the ELF entry point?
**Ans**: The entry point is a header field in the ELF file containing the virtual memory address where CPU execution should start when the program loads.

### Q30: How do you trace specific system calls using `strace`?
**Ans**: Use the `-e` flag, for example: `strace -e open,close ./my_program`.

---

## 9. Common Bugs, Debugging & Best Practices

### 9.1 Data Races in Shared Memory IPC
*   **Problem**: Process A writes an image frame to shared memory while Process B reads it, causing torn frames or crashes.
*   **Fix**: Always coordinate access using a binary semaphore or named mutex. Ensure Process B only reads after Process A signals that the write is complete.

### 9.2 Zombie Processes
*   **Problem**: A child process exits, but the parent does not call `wait()` or `waitpid()` to read its exit status. The child remains in the process table as a "zombie" ($Z$ state), wasting kernel resources.
*   **Fix**: Call `waitpid()` in the parent or handle the `SIGCHLD` signal.

### 9.3 OOM (Out of Memory) Kills
*   **Problem**: The Linux kernel runs out of physical memory and swap space. To save the system, the kernel's Out-Of-Memory (OOM) Killer picks a high-memory process and forces a crash.
*   **Fix**: Pre-allocate fixed memory sizes, monitor allocations via `/proc/meminfo`, and avoid memory leaks.
