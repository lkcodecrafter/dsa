# Module 5: Object-Oriented Programming (Lectures 70–77)

## 📋 Syllabus
*   **OOP Principles:** Encapsulation, Inheritance (Types, Access Modifiers), Polymorphism (Runtime/Compile-time), Virtual Functions, Destructors.
*   **Advanced:** Exception Handling, File Handling.

---

## 🟢 Section 1: OOP Principles

### 🎯 Solution 5.1: Encapsulation & Inheritance
*   **Concept:** Encapsulation wraps data and functions into a single unit (class), hiding raw variables behind getter/setter interfaces. Inheritance allows a derived class to reuse properties of a base class.
*   **C++ Code:**
```cpp
#include <string>
#include <iostream>

// 1. Encapsulation
class Employee {
private:
    std::string name;
    double salary;
public:
    void setName(const std::string& n) { name = n; }
    std::string getName() const { return name; }
    
    void setSalary(double s) {
        if (s >= 0) salary = s; // validation logic
    }
    double getSalary() const { return salary; }
};

// 2. Inheritance Types
class Base { public: void display() { std::cout << "Base\n"; } };

// Single Inheritance
class DerivedSingle : public Base {};

// Multilevel Inheritance
class DerivedMultilevel : public DerivedSingle {};

// Multiple Inheritance
class ClassA { public: void printA() {} };
class ClassB { public: void printB() {} };
class MultipleDerived : public ClassA, public ClassB {};
```
*   **🔍 Dry Run:**
    *   Creating an instance of `Employee`: `Employee emp;`
    *   `emp.setSalary(-5000)`: validation fails, salary is unchanged.
    *   `emp.setSalary(75000)`: updates internal `salary` member safely. Access is restricted using `private` modifier.
*   **Complexity:** Time: $O(1)$ for getters/setters, Space: $O(1)$.

### 🎯 Solution 5.2: Polymorphism & Virtual Functions
*   **Concept:** Compile-time polymorphism is achieved using Function Overloading. Runtime polymorphism is achieved via Method Overriding using `virtual` functions and base pointers.
*   **C++ Code:**
```cpp
#include <iostream>

class OverloadDemo {
public:
    // Compile-time Polymorphism (Function Overloading)
    int add(int a, int b) { return a + b; }
    double add(double a, double b) { return a + b; }
};

class Parent {
public:
    // Runtime Polymorphism (Virtual Function)
    virtual void print() {
        std::cout << "Parent Class Print Function\n";
    }
};

class Child : public Parent {
public:
    void print() override {
        std::cout << "Child Class Print Function\n";
    }
};
```
*   **🔍 Dry Run:**
    *   Compile-time overload is resolved at compilation based on signature: `add(5, 10)` maps to `add(int, int)`.
    *   Runtime polymorphism resolves methods dynamically via the VTABLE:
        *   `Parent* ptr = new Child();`
        *   `ptr->print();` resolutely outputs `"Child Class Print Function"` because `print` is marked `virtual` and resolves to the overriding function.
*   **Complexity:** Resolving virtual functions adds a minor pointer indirection overhead $O(1)$ time, Space: $O(1)$.

### 🎯 Solution 5.3: Virtual Destructors (Memory Leakage Prevention)
*   **Problem:** Demonstrate how virtual destructors prevent memory leaks when deleting a derived class object through a base pointer.
*   **C++ Code:**
```cpp
#include <iostream>

class Base {
public:
    Base() { std::cout << "Base Constructor\n"; }
    virtual ~Base() { std::cout << "Base Destructor\n"; } // virtual destructor
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() { 
        std::cout << "Derived Constructor\n"; 
        data = new int[10]; // Heap allocation
    }
    ~Derived() override { 
        std::cout << "Derived Destructor\n"; 
        delete[] data; // Freeing heap memory
    }
};
```
*   **🔍 Dry Run:**
    *   `Base* obj = new Derived();`
        1. Calls `Base()` constructor.
        2. Calls `Derived()` constructor (allocates memory for 10 integers).
    *   `delete obj;`
        *   Since `~Base()` is marked `virtual`, the compiler queries the VTABLE and invokes `~Derived()` destructor first (which deletes dynamic array `data`), and then invokes `~Base()`.
        *   **Without virtual:** Only `~Base()` is called, causing a memory leak for `data`.
*   **Complexity:** Time: $O(1)$, Space: $O(1)$.

---

## 🟢 Section 2: Advanced Topics

### 🎯 Solution 5.4: Exception Handling & File Handling
*   **C++ Code:**
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// 1. Exception Handling
double divide(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero exception!");
    }
    return a / b;
}

// 2. File Handling
void fileHandlingDemo() {
    // Writing to File
    std::ofstream outFile("demo.txt");
    if (outFile.is_open()) {
        outFile << "Writing to a text file in C++.\n";
        outFile.close();
    }
    
    // Reading from File
    std::ifstream inFile("demo.txt");
    std::string line;
    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::cout << "Read: " << line << "\n";
        }
        inFile.close();
    }
}
```
*   **Complexity:** Time: $O(N)$ for reading $N$ characters from file, Space: $O(N)$ buffer string space.
