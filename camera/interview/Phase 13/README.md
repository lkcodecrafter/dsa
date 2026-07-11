# Phase 13 - DSA for Embedded Interviews

> Embedded Camera & Real-Time Systems Interview Masterclass (Simplified Edition)

This guide covers **Data Structures and Algorithms (DSA)** optimized for resource-constrained embedded systems. It details circular buffers, bitwise manipulations, static linked lists, memory pools (slab allocators), and Big-O efficiency analysis without dynamic memory allocations (`malloc`/`free`). It is written in simple, clear English with detailed definitions and implementation code.

---

## Table of Contents
1. [Embedded Constraints & DSA Design](#1-embedded-constraints--dsa-design)
2. [The Circular Buffer (Static FIFO Queue)](#2-the-circular-buffer-static-fifo-queue)
3. [Bitwise Operations & Algorithms](#3-bitwise-operations--algorithms)
4. [Memory Pools (Slab Allocators)](#4-memory-pools-slab-allocators)
5. [Static Linked Lists](#5-static-linked-lists)
6. [30 DSA for Embedded Interview Questions & Answers](#6-30-dsa-for-embedded-interview-questions--answers)
7. [Study & Memory Masterclass Strategies](#7-study--memory-masterclass-strategies)

---

## 1. Embedded Constraints & DSA Design

In standard software engineering, algorithms are often designed around dynamic memory allocations, standard library templates, and unlimited heap spaces. In embedded platforms:
*   **Dynamic memory allocations (`malloc`/`new`) are prohibited** in safety-critical systems (e.g., ISO 26262, MISRA-C) because they can fail at runtime and cause heap fragmentation.
*   Data structures must use pre-allocated static arrays or stack space.
*   Algorithms must run in deterministic time ($\mathcal{O}(1)$ or $\mathcal{O}(N)$), avoiding nested recursion that could overflow the stack.

---

## 2. The Circular Buffer (Static FIFO Queue)

A **Circular Buffer** is a fixed-size queue that wraps around when it reaches the end of the array. It is the core data structure for handling asynchronous streams (e.g., UART bytes, camera frames, and network packets).

```
          +---+---+---+---+---+---+---+---+
          | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |  <- Fixed Array of Size 8
          +---+---+---+---+---+---+---+---+
                    ^               ^
                    | Read (Tail)   | Write (Head)
```

### 2.1 C Implementation
To keep operations atomic and avoid lock synchronization, we use index masking (when size is a power of 2):

```c
#define BUFFER_SIZE 8 // Must be a power of 2
#define BUFFER_MASK (BUFFER_SIZE - 1)

typedef struct {
    uint8_t  data[BUFFER_SIZE];
    uint32_t head; // Write index
    uint32_t tail; // Read index
} CircularBuffer_t;

void initBuffer(CircularBuffer_t *cb) {
    cb->head = 0;
    cb->tail = 0;
}

bool isFull(CircularBuffer_t *cb) {
    return ((cb->head - cb->tail) >= BUFFER_SIZE);
}

bool isEmpty(CircularBuffer_t *cb) {
    return (cb->head == cb->tail);
}

bool enqueue(CircularBuffer_t *cb, uint8_t val) {
    if (isFull(cb)) {
        return false; // Buffer overflow
    }
    cb->data[cb->head & BUFFER_MASK] = val;
    cb->head++;
    return true;
}

bool dequeue(CircularBuffer_t *cb, uint8_t *val) {
    if (isEmpty(cb)) {
        return false; // Buffer underflow
    }
    *val = cb->data[cb->tail & BUFFER_MASK];
    cb->tail++;
    return true;
}
```

---

## 3. Bitwise Operations & Algorithms

Bitwise manipulation is essential for reading and writing hardware registers, packing data packets, and optimizing operations.

### 3.1 Common Bitwise Operations

*   **Set Bit $n$**: `reg |= (1 << n);`
*   **Clear Bit $n$**: `reg &= ~(1 << n);`
*   **Toggle Bit $n$**: `reg ^= (1 << n);`
*   **Check Bit $n$**: `bool is_set = (reg & (1 << n)) != 0;`

### 3.2 Power of 2 Check
Check if a number $X$ is a power of 2:
```c
bool isPowerOfTwo(uint32_t x) {
    return (x > 0) && ((x & (x - 1)) == 0);
}
```

---

## 4. Memory Pools (Slab Allocators)

A **Memory Pool** pre-allocates blocks of memory at startup, allowing applications to allocate and free objects in $\mathcal{O}(1)$ time without causing heap fragmentation.

```
       +---------------------------------------------+
       |                 Memory Pool                 |
       +---------------------------------------------+
       | [ Block 0 ] -> [ Block 1 ] -> [ Block 2 ]   |  <- Linked list of free blocks
       +---------------------------------------------+
```

### 4.1 Simple C Implementation
```c
#define BLOCK_SIZE  64
#define BLOCK_COUNT 4

typedef struct Block {
    struct Block* next;
} Block_t;

typedef struct {
    uint8_t  memory[BLOCK_COUNT * BLOCK_SIZE];
    Block_t* freeList;
} MemoryPool_t;

void initPool(MemoryPool_t* pool) {
    pool->freeList = (Block_t*)pool->memory;
    Block_t* curr = pool->freeList;
    
    for (int i = 0; i < BLOCK_COUNT - 1; ++i) {
        curr->next = (Block_t*)((uint8_t*)curr + BLOCK_SIZE);
        curr = curr->next;
    }
    curr->next = NULL; // End of list
}

void* allocateBlock(MemoryPool_t* pool) {
    if (pool->freeList == NULL) return NULL; // Out of memory
    
    void* block = pool->freeList;
    pool->freeList = pool->freeList->next;
    return block;
}

void freeBlock(MemoryPool_t* pool, void* block) {
    Block_t* b = (Block_t*)block;
    b->next = pool->freeList;
    pool->freeList = b;
}
```

---

## 5. Static Linked Lists

Standard linked lists allocate nodes dynamically using `malloc()`. In embedded systems, we can implement linked lists inside a statically allocated array to prevent heap usage.

```cpp
struct Node {
    int data;
    int next; // Array index instead of a pointer; -1 represents NULL
};

Node nodePool[10]; // Static storage pool
int head = -1;
```

---

## 6. 30 DSA for Embedded Interview Questions & Answers

### Q1: Write a function to check if a number is a power of two using bitwise operators.
**Ans**:
```c
bool isPowerOfTwo(uint32_t x) {
    return (x > 0) && ((x & (x - 1)) == 0);
}
```
This works because a power of two has exactly one set bit (e.g., `0b0100`). Subtracting 1 flips all bits after the set bit (e.g., `0b0011`). Performing a bitwise AND between them yields zero.

### Q2: How do you implement a circular buffer queue?
**Ans**: Define a struct containing a fixed-size array, a `head` write index, and a `tail` read index. Increment the indices during operations and wrap them using a bitwise mask (`index & (SIZE - 1)`) where the array size is a power of two.

### Q3: Explain how to reverse the bits of a 32-bit unsigned integer.
**Ans**: You can reverse the bits using mask shifts (divide and conquer):
```c
uint32_t reverseBits(uint32_t n) {
    n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1);
    n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2);
    n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4);
    n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8);
    n = (n >> 16) | (n << 16);
    return n;
}
```

### Q4: Write a C function to count the number of set bits (1s) in a 32-bit integer (Hamming weight).
**Ans**:
```c
int countSetBits(uint32_t n) {
    int count = 0;
    while (n > 0) {
        n &= (n - 1); // Clears the lowest set bit
        count++;
    }
    return count;
}
```

### Q5: How do you check if a linked list has a loop?
**Ans**: Use Floyd's Cycle-Finding Algorithm (slow and fast pointers). Move the slow pointer by 1 node and the fast pointer by 2 nodes. If the pointers meet, the list contains a loop. If the fast pointer reaches NULL, there is no loop.

### Q6: What is a Slab Allocator, and what advantages does it offer?
**Ans**: A slab allocator (memory pool) pre-allocates memory divided into fixed-size chunks. It supports $\mathcal{O}(1)$ allocations and deallocations without heap fragmentation, making it safe for real-time systems.

### Q7: Write a macro to find the offset of a member within a C struct.
**Ans**:
```c
#define offsetof(type, member) ((size_t)&(((type *)0)->member))
```
This casts 0 to a pointer of struct type, references the member, and takes its address, which equals the member's offset in bytes from the start of the struct.

### Q8: What is struct alignment, and how do you prevent padding bytes?
**Ans**: Compilers align struct members to their native size boundaries (e.g., 4-byte boundaries for 32-bit integers) by inserting padding bytes. To prevent padding, use compiler directives like `#pragma pack(push, 1)` or `__attribute__((packed))`.

### Q9: Write a function to swap the bytes of a 16-bit integer (Endianness conversion).
**Ans**:
```c
uint16_t swapBytes(uint16_t val) {
    return (val >> 8) | (val << 8);
}
```

### Q10: How do you swap two variables without using a temporary variable?
**Ans**: Use the bitwise XOR operator:
```c
a ^= b;
b ^= a; // b becomes original a
a ^= b; // a becomes original b
```

### Q11: Explain how you would implement a stack data structure inside a statically allocated array.
**Ans**: Define a struct containing a fixed-size array and a `top` integer index initialized to -1. During `push`, increment `top` and store the element. During `pop`, retrieve the element at `top` and decrement the index.

### Q12: How do you find the middle element of a linked list in a single pass?
**Ans**: Use two pointers: a slow pointer and a fast pointer. Increment the slow pointer by 1 node and the fast pointer by 2 nodes. When the fast pointer reaches the end of the list, the slow pointer will be at the middle node.

### Q13: Write a function to check if the CPU is Little-Endian or Big-Endian.
**Ans**:
```c
bool isLittleEndian(void) {
    uint16_t num = 1;
    return (*(uint8_t*)&num == 1);
}
```
This checks if the lowest memory address of the 16-bit integer stores its least significant byte.

### Q14: How do you clear the lowest set bit of a number?
**Ans**: Use `x & (x - 1)`. This operation flips the lowest set bit of $X$ to 0.

### Q15: What is the Big-O lookup efficiency of a Binary Search Tree (BST) in the worst-case scenario, and how do you prevent it?
**Ans**: In the worst-case scenario (e.g., when elements are inserted in sorted order), a BST degenerates into a linear linked list, resulting in a lookup time of $\mathcal{O}(N)$. Using self-balancing trees like AVL or Red-Black trees guarantees $\mathcal{O}(\log N)$ lookups.

### Q16: How do you implement a priority queue in an RTOS scheduler?
**Ans**: Use an array of linked list headers, where the array indices represent priority levels. Tasks are queued in the linked list matching their priority. The scheduler scans from the highest index to the lowest to find and execute the first task.

### Q17: Write a macro to toggle bit $n$ in a variable.
**Ans**:
```c
#define TOGGLE_BIT(reg, n) ((reg) ^= (1U << (n)))
```

### Q18: What is a Hash Table, and why is it rarely used in microcontrollers with small SRAM?
**Ans**: A Hash Table maps keys to values using a hashing function and bucket arrays. It is rarely used in resource-constrained systems because it requires large arrays to prevent collisions, which consumes significant SRAM.

### Q19: Explain the difference between DFS (Depth-First Search) and BFS (Breadth-First Search).
**Ans**:
*   **DFS**: Explores a branch as deep as possible before backtracking. It uses a Stack (often via recursion) and has a low memory footprint.
*   **BFS**: Explores neighbor nodes level-by-level. It uses a Queue and can consume significant memory on wide graphs.

### Q20: Write a function to check if a specific bit $n$ is set in a register.
**Ans**:
```c
bool isBitSet(uint32_t reg, int n) {
    return (reg & (1U << n)) != 0;
}
```

### Q21: How do you extract the upper and lower nibbles (4 bits) from a byte?
**Ans**:
```c
uint8_t lower = byte & 0x0F;
uint8_t upper = (byte >> 4) & 0x0F;
```

### Q22: Explain the time complexity of bubble sort vs. quicksort.
**Ans**:
*   **Bubble Sort**: Time complexity is $\mathcal{O}(N^2)$ in the average and worst cases, but it runs in-place with no stack overhead.
*   **Quicksort**: Average time complexity is $\mathcal{O}(N \log N)$ but worst-case is $\mathcal{O}(N^2)$. It requires $\mathcal{O}(\log N)$ stack space for recursion.

### Q23: Write a function to find the absolute value of an integer without using branches.
**Ans**:
```c
int abs_no_branch(int n) {
    int mask = n >> (sizeof(int) * 8 - 1);
    return (n + mask) ^ mask;
}
```

### Q24: What is the "offsetof" macro used for in the Linux kernel linked list implementation?
**Ans**: The Linux kernel linked list struct (`struct list_head`) is embedded inside user data structures. The kernel uses the `offsetof` macro within the `container_of` macro to calculate the starting address of the parent structure using the list node's address.

### Q25: Write a function to count leading zeros (CLZ) in an integer using bitwise operations.
**Ans**: Most embedded CPUs provide a hardware `CLZ` instruction. In C, it can be implemented using binary search:
```c
int countLeadingZeros(uint32_t x) {
    if (x == 0) return 32;
    int count = 0;
    if (x <= 0x0000FFFF) { count += 16; x <<= 16; }
    if (x <= 0x00FFFFFF) { count += 8;  x <<= 8;  }
    if (x <= 0x0FFFFFFF) { count += 4;  x <<= 4;  }
    if (x <= 0x3FFFFFFF) { count += 2;  x <<= 2;  }
    if (x <= 0x7FFFFFFF) { count += 1;            }
    return count;
}
```

### Q26: What is a binary search algorithm, and what is its precondition?
**Ans**: A binary search divides a search interval in half on every step. Its precondition is that the input array must be sorted. Time complexity is $\mathcal{O}(\log N)$.

### Q27: How do you implement a circular linked list?
**Ans**: A circular linked list is a standard list where the last node's `next` pointer references the `head` node instead of NULL, forming a continuous loop.

### Q28: Write a macro to swap the nibbles of a byte.
**Ans**:
```c
#define SWAP_NIBBLES(byte) (((byte) >> 4) | (((byte) & 0x0F) << 4))
```

### Q29: What is the stack depth of a recursive binary search algorithm, and why does it matter?
**Ans**: The stack depth is $\mathcal{O}(\log N)$. In resource-constrained microcontrollers, each nested call pushes registers and parameters to the stack. If the stack is too small, this can cause a stack overflow crash.

### Q30: How do you represent a Graph in memory when RAM is limited to 2KB?
**Ans**: Avoid using an adjacency matrix, which scales quadratically ($\mathcal{O}(V^2)$). Instead, use an adjacency list implemented with static linked list nodes, where storage scales linearly with the number of edges ($\mathcal{O}(V + E)$).

---

## 7. Study & Memory Masterclass Strategies

### 7.1 The "Index Masking" Wrap-Around Model

For array index wrap-arounds:
*   **Standard Method (Modulo)**: `index = (index + 1) % size;`. This uses the CPU division engine, which can take 10-40 cycles.
*   **Optimal Method (Masking)**: `index = (index + 1) & (size - 1);` (where size is a power of 2). This executes in a single clock cycle.

### 7.2 Bitwise Operations Reference

| Operation | C Code Expression | Description |
| :--- | :--- | :--- |
| **Set Bit** | `reg \|= (1 << n)` | Changes bit $n$ to 1; leaves other bits unchanged. |
| **Clear Bit** | `reg &= ~(1 << n)` | Changes bit $n$ to 0; leaves other bits unchanged. |
| **Toggle Bit** | `reg ^= (1 << n)` | Flips bit $n$ (1 to 0 or 0 to 1). |
| **Check Bit** | `(reg >> n) & 1` | Returns 1 if bit $n$ is set, otherwise 0. |
