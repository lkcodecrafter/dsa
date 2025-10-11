#include <iostream>
using namespace std;

/*
Program can access code section & stack of main Memory.
It cannot access Heap Memory.
:: To access Heap Memory -> Pointers is needed

|-------| 
|       | HEAP
|-------| 
|       | Stack                [CPU]
|-------|
|       | Code section
|-------| 
 Main Memory

Heaps are external to program.

* A pointer might be accessing Monitor, Files, internal & others external things.

Why are Pointer Useful

1. Accessing Heaps
2.   ""      Resources
3. Parameter passing
*/

int main(){

    int a = 10;
    int *p;
    p = &a;
    cout<<a<<endl;
    cout<<*p<<endl;
    cout<<&a<<endl;
    cout<<&p<<endl;
    
    return 0;
}

/*
Output :

10
10
0x5ffecc
0x5ffec0

*/