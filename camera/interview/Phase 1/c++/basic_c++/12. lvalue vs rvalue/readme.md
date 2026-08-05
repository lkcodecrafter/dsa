12. lvalue vs rvalue

```c++
int x = 10;

x = lvalue

10

rvalue

int&& ref = 10;

rvalue reference.
 
 Example program

 #include <iostream>
using namespace std;

// Function that takes rvalue (temporary object)
void process(int &&x) {
    cout << "rvalue version called: " << x << endl;
}

// Function that takes lvalue (named variable)
void process(int &x) {
    cout << "lvalue version called: " << x << endl;
}

int main() {
    int a = 5;      // lvalue
    process(a);     // calls lvalue version

    process(10);    // calls rvalue version (10 is temporary)

    process(a + 2); // a + 2 is temporary (rvalue)
                    // but it is first assigned to temporary variable
                    // int temp = a + 2;
                    // process(temp); 
                    // so it calls lvalue version!

    return 0;
}

//Output 
// rvalue version called: 5
// rvalue version called: 10
// lvalue version called: 7
```

Give more info about lvalue and rvalue : 

L-values:
1. A “value” that has an address (storage location).
2. A value that can be assigned to (mutable).
3. A value that can have a name.
4. It “lives” beyond a single expression.
example : 

```c++
// lvalue — has an address, can be assigned to
int x = 10;
int* ptr = &x;   // taking address is allowed
x = 20;         // assignment is allowed

// rvalue — no address, cannot be assigned to
int y = 10 + 20; // 10 + 20 is temporary (rvalue)
// int* ptr = &(10 + 20);  // ERROR! no address
// (10 + 20) = 5;           // ERROR! cannot assign to rvalue
```


R-values: 
1. A “value” that has no address (temporary).
2. A value that cannot be assigned to.
3. A value that cannot have a name.
4. It exists only within a single expression.
example : 

```c++
// rvalue — temporary value that goes out of scope at the end of the
// expression
int x = 10;
int y = x + 5;   // x + 5 is temporary (rvalue)

// temporary objects returned from functions are rvalues
int getValue() { return 42; }
int z = getValue(); // getValue() returns an rvalue
```