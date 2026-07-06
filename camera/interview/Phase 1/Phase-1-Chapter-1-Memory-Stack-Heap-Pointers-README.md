# Phase 1 - Chapter 1: Memory, Stack, Heap & Pointers

> Embedded Camera Interview Masterclass (2026 Edition)

## Objectives

After this chapter you should be able to:

-   Explain process memory layout.
-   Differentiate stack vs heap.
-   Use pointers and references correctly.
-   Avoid memory leaks, dangling pointers and wild pointers.
-   Explain these concepts confidently in interviews.

------------------------------------------------------------------------

# 1. Process Memory Layout

    +------------------+
    | Code (.text)     |
    +------------------+
    | Initialized Data |
    +------------------+
    | BSS              |
    +------------------+
    | Heap   ↑ grows   |
    |                  |
    |                  |
    | Stack  ↓ grows   |
    +------------------+

-   **Code**: compiled instructions.
-   **Data**: initialized global/static variables.
-   **BSS**: uninitialized global/static variables.
-   **Heap**: dynamic memory (`new`).
-   **Stack**: local variables and function calls.

------------------------------------------------------------------------

# 2. Stack vs Heap

  Stack          Heap
  -------------- -------------
  Automatic      Manual/RAII
  Fast           Slower
  Small          Large
  Auto cleanup   Must free

Example:

``` cpp
int x = 10;          // stack
int* p = new int(5); // heap
delete p;
```

------------------------------------------------------------------------

# 3. Pointer Basics

``` cpp
int a = 10;
int* p = &a;

std::cout << *p; // 10
```

-   `&` -\> address of
-   `*` -\> dereference

------------------------------------------------------------------------

# 4. Reference

``` cpp
int x = 5;
int& r = x;

r = 20;
// x is now 20
```

Pointers can be reseated and may be null. References cannot.

------------------------------------------------------------------------

# 5. Common Bugs

## Memory Leak

``` cpp
int* p = new int(5);
// forgot delete
```

## Dangling Pointer

``` cpp
int* p = new int(5);
delete p;
// p still points to freed memory

// solution of above is we should set p = nullptr after delete
```

## Wild Pointer

``` cpp
int* p;
*p = 10; // undefined behavior
```

Always initialize pointers.

------------------------------------------------------------------------

# 6. RAII Preview
// full name is resource acquisition is initialization - Used to manage resources in embedded device, mainly in embedded camera HAL.
Bad:

``` cpp
FILE* fp = fopen("a.txt","r");
// exception
fclose(fp); // never reached
```

Good:

``` cpp
std::ifstream file("a.txt");
```

Destructor automatically releases the resource.

------------------------------------------------------------------------

# 7. Smart Pointer Preview

``` cpp
auto p = std::make_unique<int>(10);
```

No manual delete required.

------------------------------------------------------------------------

# 8. Interview Questions

1.  Stack vs Heap?
2.  What is a pointer?
3.  What is a reference?
4.  Difference between pointer and reference?
5.  What is a dangling pointer?
6.  What is a wild pointer?
7.  What is a memory leak?
8.  Why use RAII?
9.  Why avoid raw `new`?
10. Why are smart pointers preferred?

------------------------------------------------------------------------

# 9. Debugging Exercise

``` cpp
int* p = new int(10);
delete p;
std::cout << *p;
```

Question: - What's wrong? - How would AddressSanitizer help? - How would
you fix it?

Answer: - `p` becomes a dangling pointer after `delete`. - Dereferencing
it is undefined behavior. - Set `p = nullptr` after `delete`, or use
`std::unique_ptr`.

------------------------------------------------------------------------

# 10. Embedded Camera HAL Connection

Camera HAL frequently manages: - Image buffers - DMA memory - Metadata
buffers

Poor pointer handling can cause: - Crashes - Buffer leaks - Frame
drops - Camera service restarts

Understanding memory ownership is critical in production Camera HAL
development.

------------------------------------------------------------------------

# Revision Sheet

Remember:

-   Stack = automatic.
-   Heap = dynamic.
-   Pointer stores address.
-   Reference is an alias.
-   Free what you allocate.
-   Prefer RAII.
-   Prefer smart pointers.

Next Chapter: **Classes, Objects & OOP**
