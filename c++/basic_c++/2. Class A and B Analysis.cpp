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

    return 0;
}

/*
Important Interview Concept
Constructor Order

Base/member objects created first.
Destructor Order
Reverse order.

*/