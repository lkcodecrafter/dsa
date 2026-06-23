#include <iostream>
#include <cstdlib> // Required for malloc and free

int main() {
    int n = 5;
    
    // Allocate memory for 'n' integers using malloc
    int* ptr = (int*)malloc(n * sizeof(int));
    
    // Always check if the allocation was successful
    if (ptr == nullptr) {
        std::cerr << "Memory allocation failed!\n";
        return 1;
    }

    // Initialize the allocated memory
    for (int i = 0; i < n; ++i) {
        ptr[i] = (i + 1) * 10;
    }

    // Print the values
    std::cout << "Allocated values: ";
    for (int i = 0; i < n; ++i) {
        std::cout << ptr[i] << " ";
    }
    std::cout << "\n";

    // Free the allocated memory to prevent leaks
    free(ptr);
    ptr = nullptr; // Good practice to avoid dangling pointers


    return 0;
}


/*
Key Rules for malloc in C++:
1. Include Header: Always include <cstdlib>.
2. Type Casting: You must explicitly cast the void* returned by malloc (e.g., (int*)malloc(...))
3. Null Check: Always verify that malloc didn't return nullptr before using the memory.
4. Deallocation: You must use free(ptr) when you are done to avoid memory leaks.


*/