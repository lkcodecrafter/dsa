#include <bits/stdc++.h>
using namespace std;

class A{
    public:

    A(){
        cout<<"A"<<endl;
    }

    ~A(){
        cout<<"~A"<<endl;
    }
};

class B{
    A a;
    public :
    B(){
        cout<<"B"<<endl;
    }
    ~B(){
        cout<<"~B"<<endl;
    }
};

int main(){
    B b; // what this means is that when we create an object of class B, 
    // it will automatically create an object of class A as well, 
    // because class B has a member variable of type A. 
    // So when we create an object of class B, it will first call the constructor of class A to initialize the member variable a, 
    // and then it will call the constructor of class B to initialize the object b. When the object b goes out of scope, 
    // it will first call the destructor of class B to clean up any resources used by b, 
    // and then it will call the destructor of class A to clean up any resources used by a. So the output will be:

    // Output:
    // A
    // B
    // ~B
    // ~A


    // Diff b/w B b and B* b =new B(); 
    /*
    1. B b; (Stack Allocation)
       - Memory is allocated on the stack.
       - The object is automatically destroyed when it goes out of scope.
       - No need to call 'delete'.
       - Faster allocation.

    2. B* b = new B(); (Heap Allocation)
       - Memory is allocated on the heap.
       - The object persists until 'delete b' is explicitly called.
       - If not deleted, it leads to a memory leak.
       - Slower allocation but useful for dynamic lifetimes.
    */



    cout << "--- Heap Allocation Example ---" << endl;
    B* b_ptr = new B(); // Calls A() then B()
    delete b_ptr;       // Calls ~B() then ~A()
    b_ptr = nullptr;
    

    // Same do now with malloc also diff between malloc/calloc etc 
    cout << "--- Malloc Allocation Example ---" << endl;
    // malloc allocates raw memory on the heap but does NOT call constructors
    B* b_malloc = (B*)malloc(sizeof(B)); 
    if (b_malloc != nullptr) {
        cout << "Memory allocated via malloc (No constructor called)" << endl;
        // free deallocates memory but does NOT call destructors
        free(b_malloc);
        cout << "Memory freed via free (No destructor called)" << endl;
        b_malloc = nullptr;
    }

    /*
    Difference between malloc, calloc, realloc, and new:

    1. malloc(size_t size):
       - Allocates a block of uninitialized memory.
       - Returns a void pointer (void*).
       - Does not call constructors.

    2. calloc(size_t num, size_t size):
       - Allocates memory for an array of 'num' elements.
       - Initializes all bits to zero.
       - Does not call constructors.

    3. realloc(void* ptr, size_t new_size):
       - Resizes previously allocated memory.
       - May move the memory block to a new location.

    4. new operator:
       - Allocates memory AND calls the constructor.
       - Returns a typed pointer (no casting needed).
       - Throws an exception if allocation fails (malloc returns NULL).
    */
    
    // so calloc only allow memory for array or vector 
    /*
    Clarification on calloc:
    - calloc is not restricted to arrays or vectors; it can allocate memory for any type.
    - The syntax `calloc(n, size)` is simply a convenience for `malloc(n * size)` with the added benefit of zero-initialization.
    - For a single object, you would use `calloc(1, sizeof(B))`.
    */

    cout << "--- Calloc Allocation Example ---" << endl;
    B* b_calloc = (B*)calloc(1, sizeof(B));
    if (b_calloc != nullptr) {
        cout << "Memory allocated via calloc (Zero-initialized, No constructor called)" << endl;
        free(b_calloc);
        b_calloc = nullptr;
    }
    

    // if i want to use it as B* b = calloc(sizeof(B))? 
    /*
    If you want to use calloc for a single object, you must still provide two arguments:
    the number of elements (1) and the size of the element.
    */
    B* b_calloc_single = (B*)calloc(1, sizeof(B));
    if (b_calloc_single != nullptr) {
        free(b_calloc_single);
        b_calloc_single = nullptr;
    }
    
    // or if we want multipe object using calloc 
    cout << "--- Multiple Objects via Calloc ---" << endl;
    int num_objects = 3;
    B* b_multiple = (B*)calloc(num_objects, sizeof(B));
    if (b_multiple != nullptr) {
        cout << "Allocated memory for " << num_objects << " objects of type B using calloc." << endl;
        // Note: Constructors are NOT called for any of these objects.
        free(b_multiple);
        b_multiple = nullptr;
    }
    // is it requirement to give number of object in calloc 
    /*
    Yes, it is a requirement. The signature of calloc is:
    void* calloc(size_t num, size_t size);
    
    - 'num': Number of elements to be allocated.
    - 'size': Size of each element.
    
    If you only want to provide the total size like malloc, you would use malloc(size). 
    The primary reason to use calloc is to ensure the allocated memory is zero-initialized.
    */
    

    return 0;
}

/*
Important Interview Concept
Constructor Order

Base/member objects created first.
Destructor Order
Reverse order.

*/