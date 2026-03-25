#include<stdlib.h>
#include<iostream>

using namespace std;

void basicPointer(){
    int* p = (int*)malloc(sizeof(int));
    *p = 10;
    cout << "Value: " << *p << endl;
    free(p);
    p = nullptr; // Avoid dangling pointer
}

void movePointer(){
    // Pointer moves like array index, but it is not an array, it is a pointer.
    int arr[5] ={1,2,3,4,5};
    int *p = arr;
    cout<<"The value of Pointer "<<*p<<endl;
    *p++;
    cout<<"The value of Pointer "<<*p<<endl;
    *p++;
    cout<<"The value of Pointer "<<*p<<endl;
    *p++;
    cout<<"The value of Pointer "<<*p<<endl;
    *p++;
    cout<<"The value of Pointer "<<*p<<endl;
    
    *p++;
    cout<<"The value of Pointer "<<*p<<endl;
    *p++;
    cout<<"The value of Pointer "<<*p<<endl;
    
    p += 5; // what is diff between *p++ and p += 5 ? // it's give segmentation fault because we are trying to access memory that is out of bounds of the array. The pointer p is now pointing to a memory location that is not part of the array, and when we try to dereference it with *p, it results in undefined behavior, which in this case is a segmentation fault.
    // *p++ moves the pointer to the next element in the array, while p += 5 moves the pointer 5 elements ahead in the array.
    cout<<"The value of Pointer "<<*p<<endl;
    *p++;
    cout<<"The value of Pointer "<<*p<<endl;

    // Important below : 
    //arr[i] == *(arr+i)
    // arr is the base address of the array, and i is the index. When we add i to arr, we are moving the pointer to the ith element of the array. The expression *(arr+i) dereferences the pointer to get the value at that position in the array.
}

void pointerToPointer(){
    int x = 10;
    int* p = &x; // pointer to x
    int** pp = &p; // pointer to pointer p
    // pointer to pointer is used when we want to modify the value of a pointer in a function. 
    //It allows us to pass the address of a pointer to a function, and the function can then modify the pointer itself, 
    //not just the value it points to.

    cout << "Value of x: " << x << endl; // 10
    cout << "Value through pointer p: " << *p << endl; // 10
    cout << "Value through pointer to pointer pp: " << **pp << endl; // 10

    // diagram of pointer to pointer
    // x (10) <-- p (pointer to x) <-- pp (pointer to pointer p)
    // If we want to change the value of x through pp, we can do it like this:
    **pp = 20; // This will change the value of x to 20
    cout << "Value of x after modification through pp: " << x << endl; // 20
    // but we cant change the value of x using *p = 30; // This will change the value of x to 30
    // than why we need pointer to pointer ? because if we want to change the value of pointer p itself,
    // we can do it through pp. For example:
    int y = 30;
    *pp = &y; // This will change the pointer p to point to y instead of x
    cout << "Value through pointer p after modification through pp: " << *p << endl; // 30

    // not able to understand pointer to pointer ? think of it like this :
    // You have a box (x) that contains a value (10). You have a label (p) that points to the box (x). Now, you have another label (pp) that points to the first label (p).
    // If you want to change the value in the box (x), you can do it through the first label (p) by dereferencing it (*p = 20).
    // However, if you want to change which box the first label (p) is pointing to, you can do it through the second label (pp) by dereferencing it twice (**pp = 30). This way, you can modify both the value in the box and which box the label is pointing to.  
}

void pointerMovement(){
    int arr[5];
    int *p = arr;
    for(int i=0;i<5;i++){
        cout<<"The address of pointer " << p <<endl;
        *p++;
    }

    int arr2[5] = {1,2,3,4,5};
    int *p2 = arr2;
    int size  = sizeof(arr2)/sizeof(arr2[0]);
    for(int i=0;i<size;i++){
        cout<<"The value of pointer " << *p2 <<endl;
        *p2++;
    }
}

void addressDiff(){
    int arr[4];
    int *p1 = &arr[0];;
    int *p2 = &arr[3];
    cout<<"The address of pointer p1 " << p1 <<endl;
    cout<<"The address of pointer p2 " << p2 <<endl;
    cout<<"The difference between p1 and p2 " << p2 - p1 <<endl; // 3
     // The difference between two pointers is calculated by subtracting the addresses they point to and dividing by the size of the data type they point to. 
     // In this case, since both pointers are of type int*, the size of the data type is 4 bytes (assuming a 32-bit system).
     // Therefore, the difference in terms of number of elements is (p2 - p1) / sizeof(int), which gives us 3.
     // 16 - 4 = 12 bytes, and 12 bytes / 4 bytes per int = 3 elements. Hence, the output is 3.
}

void pointerOffset(){
    int arr[5] = {1,2,3,4,5};
    int *p = arr;
    cout<<"The value of pointer " << *p <<endl; // 1
    cout<<"The value of pointer " << *(p+1) <<endl; // 2
    cout<<"The value of pointer " << *(p+2) <<endl; // 3
    cout<<"The value of pointer " << *(p+3) <<endl; // 4
    cout<<"The value of pointer " << *(p+4) <<endl; // 5

    // *(p+1) == *p++? No, they are not the same. *(p+1) is accessing the next element in the array without modifying the pointer p,
    // while *p++ is accessing the current element pointed to by p and then incrementing the pointer to point to the next element.
}
int main()
{
    pointerMovement();
    return 0;
}