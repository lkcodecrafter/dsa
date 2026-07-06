#include<iostream>
using namespace std;

int main()
{

    int x= 10;
    int &p = x; // means p is a reference to x. It is an alias for x. Any changes made to p will affect x and vice versa.
    cout<<p<<endl;
    p =20; // changes the value of x to 20.
    cout<<x<<endl; // 20, because p is a reference to x,
    x= 1;
    cout<<p<<endl; // 1, because p is a reference to x, and x is now 1.


    cout<< "---- Pointer----"<<endl;
    int* ptr = &x; // means ptr is a pointer to x. It holds the address of x. Any changes made to *ptr will affect x and vice versa.
    cout<<*ptr<<endl; // 1, because ptr points to x, and x is 1.
    *ptr = 2; // changes the value of x to 2.
    cout<<x<<endl; // 2, because ptr points to x, and x is now 2.
    cout<<&ptr<<endl; // prints the address of ptr, which is the address of x.

    cout<< "---- Reference----"<<endl;
    cout<<"---Example of Const-- "<<endl;

    int* const ptr1 = &x;
    cout<<*ptr1<<endl; // 2, because ptr1 points to x, and x is 2.

    const int * val = &x;
    cout<<*val<<endl; // 2, because val points to x, and x is 2.

    //val =20 ; // Error: cannot assign to variable 'val' with const-qualified type 'const int *'
    // *val = 20; // Error: read-only variable is not assignable
    
   
    // ptr1++; // Error: increment of read-only variable 'ptr1'
    
    const int * const ptr2 = &x; // Both the pointer and the value are constant.
    // ptr2++; // Error
    // *ptr2 = 30; // Error
    

    

    return 0;
}