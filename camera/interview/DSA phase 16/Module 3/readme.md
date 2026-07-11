# Module 3: Pointers & Memory Management (Lectures 45–50)

## 📋 Syllabus
*   **Basics:** Pointers, Pointer Arithmetic, Character Arrays, Double Pointers.
*   **Memory:** Static vs. Dynamic Allocation, 2D/3D Dynamic Arrays.

---

## 🟢 Section 1: Basics

### 🎯 Solution 3.1: Pointers & Double Pointers (Arithmetic & Dereferencing)
*   **Concept:** A pointer is a variable that stores the memory address of another variable. A double pointer is a pointer that stores the address of another pointer. Pointer arithmetic offsets addresses based on the data type's byte size.
*   **C++ Code:**
```cpp
#include <iostream>

void demonstratePointerBasics() {
    int val = 42;
    int* ptr = &val;     // Single Pointer storing address of 'val'
    int** dptr = &ptr;   // Double Pointer storing address of 'ptr'
    
    std::cout << "Value: " << val << "\n";
    std::cout << "Value via ptr: " << *ptr << "\n";
    std::cout << "Value via dptr: " << **dptr << "\n";
    
    // Pointer Arithmetic
    int arr[3] = {100, 200, 300};
    int* p = arr; // points to arr[0]
    
    std::cout << "Value at p: " << *p << "\n";      // 100
    p++; // moves to next int index (adds sizeof(int) = 4 bytes to the address)
    std::cout << "Value at p after p++: " << *p << "\n"; // 200
}
```
*   **🔍 Dry Run:**
    *   Let address of `val` be `0x100` -> `val = 42`.
    *   `ptr` stores address of `val` -> `ptr = 0x100`. Address of `ptr` itself is `0x200`.
    *   `dptr` stores address of `ptr` -> `dptr = 0x200`.
    *   Dereferencing:
        *   `*ptr` reads contents at address `0x100` -> `42`.
        *   `*dptr` reads contents at address `0x200` -> `0x100`.
        *   `**dptr` resolves `*(*dptr) = *(0x100)` -> `42`.
    *   Pointer Arithmetic:
        *   Let array `arr` be located at `0x400`.
        *   `p = 0x400` -> `*p = 100`.
        *   `p++` -> Address becomes `0x400 + 1 * sizeof(int) = 0x404` -> `*p = 200`.
*   **Complexity:** Time: $O(1)$, Space: $O(1)$ auxiliary.

---

## 🟢 Section 2: Memory Management

### 🎯 Solution 3.2: 2D Dynamic Array Allocation & Deallocation
*   **Problem:** Dynamically allocate and free a 2D integer array of size $R \times C$ in heap memory.
*   **C++ Code:**
```cpp
#include <iostream>

int** allocate2D(int rows, int cols) {
    // Allocate rows array of pointers
    int** matrix = new int*[rows];
    
    // Allocate columns for each row
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols](); // () initializes elements to 0
    }
    return matrix;
}

void deallocate2D(int** matrix, int rows) {
    // Free columns of each row
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    // Free rows array of pointers
    delete[] matrix;
}
```
*   **🔍 Dry Run:**
    *   Assume `rows = 2`, `cols = 3`.
    *   `matrix = new int*[2]`: allocates contiguous array of size 2 storing `int*`. Let address of this block be `0x500`.
    *   Loop `i = 0`: `matrix[0] = new int[3]`. Heap allocates 3 integers. Address (e.g., `0x600`) is stored at `0x500`.
    *   Loop `i = 1`: `matrix[1] = new int[3]`. Heap allocates 3 integers. Address (e.g., `0x700`) is stored at `0x504`.
    *   **Deallocation:**
        *   `i = 0`: deletes block at `0x600`.
        *   `i = 1`: deletes block at `0x700`.
        *   `delete[] matrix` deletes block at `0x500`. (All heap memory cleared).
*   **Complexity:** Time: $O(R)$ for allocation & deallocation, Space: $O(R \times C)$ to hold array elements in memory.

### 🎯 Solution 3.3: 3D Dynamic Array Allocation & Deallocation
*   **Problem:** Dynamically allocate and free a 3D integer array of dimensions $X \times Y \times Z$ in memory.
*   **C++ Code:**
```cpp
#include <iostream>

int*** allocate3D(int x, int y, int z) {
    int*** arr = new int**[x];
    for (int i = 0; i < x; i++) {
        arr[i] = new int*[y];
        for (int j = 0; j < y; j++) {
            arr[i][j] = new int[z](); // Init with 0
        }
    }
    return arr;
}

void deallocate3D(int*** arr, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
}
```
*   **🔍 Dry Run:**
    *   For dimensions `2 x 2 x 2`:
    *   Allocates a pointer-to-pointer-to-pointer array `arr` of size 2.
    *   For each element, allocates pointer-to-pointer arrays `arr[i]` of size 2.
    *   For each leaf element, allocates integer arrays `arr[i][j]` of size 2.
    *   Deallocation mirrors this by deleting inward-outward to avoid dangling pointer references or memory leaks.
*   **Complexity:** Time: $O(X \times Y)$, Space: $O(X \times Y \times Z)$.
