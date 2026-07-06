# Phase 1 - Chapter 3: Constructors, Copy/Move Semantics & Rule of Five

## Objectives

Understand object lifetime, constructors, copy vs move semantics, and
resource ownership.

# 1. Object Lifetime

``` cpp
class Demo{
public:
    Demo(){ std::cout<<"Ctor\n"; }
    ~Demo(){ std::cout<<"Dtor\n"; }
};

int main(){
    Demo d;
}
```

Output:

    Ctor
    Dtor

The constructor runs when the object is created. The destructor runs
automatically when the object goes out of scope.

------------------------------------------------------------------------

# 2. Types of Constructors

## Default Constructor

``` cpp
class A{
public:
    A(){}
};
```

## Parameterized Constructor

``` cpp
class A{
public:
    A(int x){}
};
```

------------------------------------------------------------------------

# 3. Constructor Initialization List

Prefer this for members, references, const members and performance.

``` cpp
class Student{
    int age;
public:
    Student(int a): age(a){}
};
```

------------------------------------------------------------------------

# 4. Copy Constructor

``` cpp
class Box{
public:
    int value;
    Box(int v):value(v){}
    Box(const Box& other){
        value=other.value;
    }
};
```

Used when: - Passing by value - Returning by value (sometimes elided) -
Initializing one object from another

------------------------------------------------------------------------

# 5. Shallow vs Deep Copy

Bad (shallow copy):

``` cpp
class Buffer{
public:
    int* data;
    Buffer(){ data=new int(10); }
    ~Buffer(){ delete data; }
};
```

Two objects would share the same pointer and both destructors would call
`delete`, causing a double free.

Deep copy allocates new memory and copies the contents.

------------------------------------------------------------------------

# 6. Copy Assignment

``` cpp
obj2 = obj1;
```

A robust implementation should: - Check self-assignment - Release old
resource - Copy new resource

------------------------------------------------------------------------

# 7. Move Constructor

``` cpp
class Buffer{
    int* data;
public:
    Buffer(int* p):data(p){}
    Buffer(Buffer&& other) noexcept{
        data=other.data;
        other.data=nullptr;
    }
};
```

Move transfers ownership instead of copying.

------------------------------------------------------------------------

# 8. Move Assignment

``` cpp
a = std::move(b);
```

Release current resource, steal the resource, null out the source.

------------------------------------------------------------------------

# 9. std::move

`std::move` does not move anything by itself.

It simply casts an object to an rvalue reference so a move
constructor/assignment can be selected.

------------------------------------------------------------------------

# 10. Rule of Three

If you define one of these, you likely need all three:

-   Destructor
-   Copy constructor
-   Copy assignment operator

Example 

```c++

#include <iostream>
using namespace std;

class Example {
public:
  int *data;

  // Constructor
  Example(int size) {
    data = new int[size];
    cout << "Constructor: Allocated memory\n";
  }

  // Destructor
  ~Example() {
    delete[] data;
    cout << "Destructor: Freed memory\n";
  }

  // Copy Constructor (Deep Copy)
  Example(const Example &other) {
    data = new int[5]; // Allocate new memory
    cout << "Copy Constructor: Deep copy performed\n";
  }

  // Copy Assignment Operator
  Example &operator=(const Example &other) {
    if (this != &other) { // Self-assignment check
      delete[] data;      // Free old memory
      data = new int[5];  // Allocate new memory
      cout << "Copy Assignment: Deep copy performed\n";
    }
    return *this;
  }
};

int main() {
  Example obj1(5);

  cout << "\n--- Testing Copy Constructor ---\n";
  Example obj2 = obj1; // Calls copy constructor

  cout << "\n--- Testing Copy Assignment ---\n";
  Example obj3(10);
  obj3 = obj1; // Calls copy assignment operator

  return 0;
}
```


------------------------------------------------------------------------

# 11. Rule of Five

Modern C++ adds:

-   Move constructor
-   Move assignment operator

Example

```c++
#include <iostream>
using namespace std;

class Buffer {
public:
  int *data;

  // Constructor
  Buffer(int size) {
    data = new int[size];
    cout << "Constructor: Allocated memory\n";
  }

  // Destructor
  ~Buffer() {
    delete[] data;
    cout << "Destructor: Freed memory\n";
  }

  // Move Constructor
  Buffer(Buffer &&other) noexcept {
    data = other.data;
    other.data = nullptr; // Set source to nullptr
    cout << "Move Constructor: Ownership transferred\n";
  }

  // Move Assignment Operator
  Buffer &operator=(Buffer &&other) noexcept {
    if (this != &other) {
      delete[] data;      // Free old memory
      data = other.data;  // Steal resource
      other.data = nullptr; // Set source to nullptr
      cout << "Move Assignment: Ownership transferred\n";
    }
    return *this;
  }

  // Disable Copy Operations
  Buffer(const Buffer &) = delete;
  Buffer &operator=(const Buffer &) = delete;
};

int main() {
  Buffer b1(5);

  cout << "\n--- Testing Move Constructor ---\n";
  Buffer b2 = std::move(b1); // Calls move constructor

  cout << "\n--- Testing Move Assignment ---\n";
  Buffer b3(10);
  b3 = std::move(b2); // Calls move assignment

  return 0;
}
```


------------------------------------------------------------------------

# 12. Rule of Zero

Prefer standard library types (`std::vector`, `std::string`, smart
pointers) so you don't need to manually manage resources.


------------------------------------------------------------------------

# 13. Interview Questions

1.  Constructor vs destructor?

Ans : 

Constructor : 
Constructor is a special member function that is automatically called when an object of a class is created.
It is used to initialize the object.

Destructor : 
Destructor is a special member function that is automatically called when an object of a class is destroyed.
It is used to release the resources held by the object.

Example :

```cpp
#include <iostream>
using namespace std;

class Demo {
public:
  // Constructor
  Demo() {
    cout << "Constructor called\n";
  }

  // Destructor
  ~Demo() {
    cout << "Destructor called\n";
  }
};

int main() {
  Demo d;
  return 0;
}
```

2.  Why initialization list?

Ans : 

Initialization list is a way to initialize the members of a class.
It is more efficient than constructor body initialization because it initializes the members directly without creating a temporary object.

Example : 

```cpp
#include <iostream>
using namespace std;

class Demo {
public:
  int value;

  // Constructor using initialization list
  Demo(int val) : value(val) {
    cout << "Initialization list used\n";
  }
};

int main() {
  Demo d(10);
  return 0;
}
```

3.  Copy constructor vs assignment?

Ans : 

Copy constructor : 
Copy constructor is used to initialize an object from another object of the same class.
It is called when an object is created from another object.

Example : 

```cpp
#include <iostream>
using namespace std;

class Demo {
public:
  int value;

  // Constructor
  Demo(int val) : value(val) {
    cout << "Constructor called\n";
  }

  // Copy Constructor
  Demo(const Demo &other) {
    value = other.value;
    cout << "Copy constructor called\n";
  }
};

int main() {
  Demo d1(10);
  Demo d2 = d1; // Calls copy constructor
  return 0;
}
```

Copy assignment : 
Copy assignment is used to assign the value of one object to another object of the same class.
It is called when an object is assigned the value of another object.

Example : 

```cpp
#include <iostream>
using namespace std;

class Demo {
public:
  int value;

  // Constructor
  Demo(int val) : value(val) {
    cout << "Constructor called\n";
  }

  // Copy Assignment
  Demo &operator=(const Demo &other) {
    value = other.value;
    cout << "Copy assignment called\n";
    return *this;
  }
};

int main() {
  Demo d1(10);
  Demo d2(20);
  d2 = d1; // Calls copy assignment
  cout << d2.value << endl;
  return 0;
}

Output :
10
Constructor called
Constructor called
Copy assignment called
Destructor called
Destructor called
```



4.  What is self-assignment?

Ans : 

Self-assignment is when an object is assigned the value of itself.
It is a dangerous operation because it can lead to double deletion.

5.  What is deep copy?

Ans : 

Deep copy is a copy of an object that includes a copy of the data members of the object.
It is a safe operation because it does not lead to double deletion.


6.  What is shallow copy?

Ans : 
Shallow copy is a copy of an object that includes a copy of the data members of the object.
It is not a safe operation because it can lead to double deletion.

7.  Why use `noexcept` on move constructor?

Ans : 

The noexcept specifier in C++ is used to indicate that a function does not throw exceptions.
It is used on move constructors and move assignment operators to indicate that they do not throw exceptions.
If a move constructor or move assignment operator throws an exception, it can lead to undefined behavior.

8.  What is move semantics?

Ans : 

Move semantics is a C++ feature that allows the transfer of ownership of resources from one object to another object.
It is a C++11 feature that was added to the language to improve performance.

9.  What does `std::move` do?

Ans : 

std::move is a C++11 function that is used to transfer ownership of resources from one object to another object.
It is a C++11 feature that was added to the language to improve performance.

10. Rule of Three?

Ans : 

The Rule of Three is a C++ guideline that states that if a class has a user-defined destructor, copy constructor, or copy assignment operator, it should have all three.

11. Rule of Five?

Ans : 

The Rule of Five is a C++ guideline that states that if a class has a user-defined destructor, copy constructor, copy assignment operator, move constructor, or move assignment operator, it should have all five.

12. Rule of Zero?

Ans : 

The Rule of Zero is a C++ guideline that states that if a class does not have any user-defined destructors, copy constructors, copy assignment operators, move constructors, or move assignment operators, it should not have any of them.

13. Why is double delete dangerous?

Ans : 

Double delete is dangerous because it can lead to undefined behavior.
It occurs when an object is deleted more than once.


14. Why set moved-from pointers to `nullptr`?

Ans : 

Moved-from pointers should be set to `nullptr` to prevent double deletion.

15. When is copy elision performed?

Ans : 

Copy elision is a C++ optimization that eliminates the need for a copy constructor or move constructor.
It is performed when an object is created from another object.

Example :

16. Why use move constructor?

Ans : 

Move constructor is used to transfer the ownership of resources from one object to another object.
It is a C++11 feature that was added to the language to improve performance.


------------------------------------------------------------------------

# 14. Camera HAL Example

Large image buffers should not be copied unnecessarily.

Instead of copying megabytes of image data, ownership is transferred
using move semantics or smart pointers.

------------------------------------------------------------------------

# 15. Debugging Exercise

``` cpp
class Buffer{
public:
    int* data;
    Buffer(){ data=new int(5); }
    ~Buffer(){ delete data; }
};

int main(){
    Buffer a;
    Buffer b=a;
}
```

Problem: Two objects own the same pointer.

Fix: Implement a deep copy or disable copying and use move semantics.


------------------------------------------------------------------------

# Revision

-   Prefer initialization lists.
-   Understand copy vs move.
-   Use Rule of Zero whenever possible.
-   Use `std::unique_ptr` for exclusive ownership.
-   Avoid manual memory management when standard library facilities
    suffice.

Next Chapter: **RAII & Smart Pointers**
