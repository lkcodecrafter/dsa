# Phase 1 - Chapter 2: Classes, Objects & OOP

## Goals

Learn the four pillars of OOP and interview-focused C++ class design.

## 1. What is a Class?

A class is a blueprint.

``` cpp
class Car{
public:
    void start(){}
};
```

## 2. What is an Object?

``` cpp
Car c1;
Car c2;
```

Each object has its own data but shares member function code.

## 3. Access Specifiers

  Specifier   Accessible
  ----------- -----------------
  public      Everywhere
  protected   Class + Derived
  private     Only Class

## 4. Four Pillars

### Encapsulation

``` cpp
class BankAccount{
    int balance;
public:
    BankAccount():balance(0){}
    void deposit(int x){ balance+=x; }
    int getBalance() const { return balance; }
};
```

### Inheritance

``` cpp
class Animal{
public:
    virtual void speak(){ }
};

class Dog: public Animal{
public:
    void speak() override {}
};
```

### Polymorphism

``` cpp
Animal* a=new Dog();
a->speak();
delete a;
```

Runtime dispatch uses a virtual table.

### Abstraction

Expose only necessary APIs and hide implementation details.

## 5. Constructors

``` cpp
class Student{
public:
    Student(){}
    Student(int){}
};
```

## 6. Destructor

``` cpp
class Demo{
public:
    ~Demo(){}
};
```

Use a virtual destructor in polymorphic base classes.

## 7. this Pointer

`this` points to the current object.

## 8. Static Members

Shared among all objects.

## 9. Friend Function

Can access private members; use sparingly.

## 10. Common Interview Questions with Answers

1.  Difference between class and object?

-   Class is a blueprint; object is an instance.

2.  Why encapsulation?

-   Protects state and controls access.

3.  Why virtual functions?

-   Enable runtime polymorphism.

4.  Why virtual destructor?

-   Ensures derived destructors execute when deleting through a base
    pointer.

5.  Difference between compile-time and runtime polymorphism?

-   Overloading vs overriding.

6.  Can constructors be virtual?

-   No.

7.  Can static functions be virtual?

-   No.

8.  Why use `override`?

-   Compile-time verification of overriding.

9.  What is object slicing?

-   Copying a derived object into a base object loses derived parts.

10. What is an abstract class?

-   A class with at least one pure virtual function.

## 11. Camera HAL Example

``` cpp
class CameraDevice{
public:
    virtual void open()=0;
    virtual ~CameraDevice()=default;
};

class QualcommCamera: public CameraDevice{
public:
    void open() override{}
};
```

## 12. Debugging Exercise

``` cpp
Animal* a=new Dog();
delete a;
```

Question: What happens if `Animal` has a non-virtual destructor?

Answer: Undefined behavior; derived cleanup may not run, causing leaks.

## Revision

-   Prefer composition over inheritance.
-   Use `override`.
-   Keep data private.
-   Make polymorphic base destructors virtual.
-   Program to interfaces.

Next: Constructors, Copy Constructor, Move Constructor & Rule of Five.
