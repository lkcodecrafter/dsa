# Phase 1 - Chapter 4: RAII & Smart Pointers

## RAII
RAII (Resource Acquisition Is Initialization) acquires resources in constructors and releases them in destructors.

### RAII Flow
Create Object -> Acquire Resource -> Use Resource -> Destructor -> Release Resource

Example if RAII flow:
```cpp
#include <iostream>
#include <vector>

using namespace std;

class DataProcessor {
public:
  DataProcessor() {
    cout << "Resource acquired!" << endl;
    // Simulate acquiring a resource (like opening a file, network connection, etc.)
  }

  ~DataProcessor() {
    cout << "Resource released!" << endl;
    // Simulate releasing the resource
  }

  void process() {
    cout << "Processing data..." << endl;
    // Simulate doing work with the resource
  }
};

int main() {
  cout << "Entering main function..." << endl;
  // Object 'processor' is created - constructor acquires the resource
  DataProcessor processor;
  // Resource is in use
  processor.process();
  // Object 'processor' goes out of scope - destructor releases the resource
  cout << "Exiting main function..." << endl;
  return 0;
}
```

## unique_ptr
- Exclusive ownership
- Cannot be copied
- Can be moved with std::move

```cpp
auto p=std::make_unique<int>(10);
auto q=std::move(p);
```
Example of unique_ptr simple example 

```cpp
#include <iostream>
#include <memory>

using namespace std;

class CameraSensor {
public:
  CameraSensor(int id) : id_(id) {
    cout << "CameraSensor " << id_ << " acquired!" << endl;
  }

  ~CameraSensor() {
    cout << "CameraSensor " << id_ << " released!" << endl;
  }

  void capture() {
    cout << "Capturing image from CameraSensor " << id_ << "..." << endl;
  }

private:
  int id_;
};

void testUniquePtr() {
  cout << "\n--- Testing unique_ptr ---" << endl;
  // Create a unique_ptr with exclusive ownership
  auto sensor = make_unique<CameraSensor>(1);
  
  // Access the object through the unique_ptr
  sensor->capture();
  
  // Move ownership to another unique_ptr
  auto sensor2 = move(sensor);
  
  // 'sensor' is now null
  if (!sensor) {
    cout << "'sensor' is now null (ownership moved)." << endl;
  }
  
  // 'sensor2' now owns the object
  sensor2->capture();
  
  // When 'sensor2' goes out of scope, the CameraSensor object will be deleted
}

int main() {
  testUniquePtr();
  return 0;
}
```

What is the use of unique_ptr : like exclusive ownership means only one unique_ptr will have ownership of the object. if copy is attempted it will throw compile time error. if move is attempted it will transfer ownership to the new unique_ptr.


## shared_ptr
- Shared ownership
- Reference counting

```cpp
auto a=std::make_shared<int>(5);
auto b=a;
```

Example of shared_ptr

```cpp
#include <iostream>
#include <memory>

using namespace std;

class CameraSensor {
public:
  CameraSensor(int id) : id_(id) {
    cout << "CameraSensor " << id_ << " acquired!" << endl;
  }

  ~CameraSensor() {
    cout << "CameraSensor " << id_ << " released!" << endl;
  }

  void capture() {
    cout << "Capturing image from CameraSensor " << id_ << "..." << endl;
  }

private:
  int id_;
};

void testSharedPtr() {
  cout << "\n--- Testing shared_ptr ---" << endl;
  // Create a shared_ptr with shared ownership
  auto sensor = make_shared<CameraSensor>(1);
  
  // Access the object through the shared_ptr
  sensor->capture();
  
  // Share ownership with another shared_ptr
  auto sensor2 = sensor;
  
  // Both shared_ptrs point to the same object
  cout << "Both sensors point to the same object." << endl;
  
  sensor2->capture();
  
  // When sensor2 goes out of scope, reference count decreases
  {
    auto sensor3 = sensor;
    cout << "Reference count: " << sensor.use_count() << endl;
  }
  // When sensor3 goes out of scope, reference count decreases again
  
  cout << "Reference count after sensor3 goes out of scope: " << sensor.use_count() << endl;
  
  // When sensor goes out of scope, the CameraSensor object will be deleted
}

int main() {
  testSharedPtr();
  return 0;
}

```

What is the use of shared_ptr -  like shared ownership means multiple shared_ptr can have ownership of the object. if copy is attempted it will copy the shared_ptr and increment the reference count. if move is attempted it will transfer ownership to the new shared_ptr.

## weak_ptr
- Non-owning observer
- Breaks circular references

```cpp
std::weak_ptr<int> w=a;
```

Example of weak_ptr 

```cpp

#include <iostream>
#include <memory>

using namespace std;

class CameraSensor {
public:
  CameraSensor(int id) : id_(id) {
    cout << "CameraSensor " << id_ << " acquired!" << endl;
  }

  ~CameraSensor() {
    cout << "CameraSensor " << id_ << " released!" << endl;
  }

  void capture() {
    cout << "Capturing image from CameraSensor " << id_ << "..." << endl;
  }

private:
  int id_;
};

void testWeakPtr() {
  cout << "\n--- Testing weak_ptr ---" << endl;
  // Create a shared_ptr with shared ownership
  auto sensor = make_shared<CameraSensor>(1);
  
  // Create a weak_ptr observing the shared_ptr
  weak_ptr<CameraSensor> weak_sensor = sensor;
  
  // Access the object through the weak_ptr (requires locking)
  if (auto locked_sensor = weak_sensor.lock()) {
    locked_sensor->capture();
  }
  
  // When sensor goes out of scope, the CameraSensor object will be deleted
  sensor.reset();
  
  // weak_ptr will now point to a deleted object
  if (!weak_sensor.expired()) {
    cout << "weak_sensor is still valid." << endl;
  } else {
    cout << "weak_sensor is expired (object was deleted)." << endl;
  }
}

int main() {
  testWeakPtr();
  return 0;
}


```

What is the use of weak_ptr - like weak_ptr is used to observe the object managed by shared_ptr. it does not have ownership of the object. if copy is attempted it will copy the weak_ptr and increment the reference count. if move is attempted it will transfer ownership to the new weak_ptr. it will not increment the reference count. 

## Circular Reference
Use weak_ptr instead of shared_ptr on one side.

## Custom Deleter
```cpp
auto fp=std::unique_ptr<FILE,decltype(&fclose)>(fopen("a.txt","r"),fclose);
```

Custom deleter means : a custom deleter is a function that is called when the object is deleted. it is used to release the resources held by the object. 
Example of custom deleter

```cpp
#include <iostream>
#include <memory>

using namespace std;

class CameraSensor {
public:
  CameraSensor(int id) : id_(id) {
    cout << "CameraSensor " << id_ << " acquired!" << endl;
  }

  ~CameraSensor() {
    cout << "CameraSensor " << id_ << " released!" << endl;
  }

  void capture() {
    cout << "Capturing image from CameraSensor " << id_ << "..." << endl;
  }

private:
  int id_;
};

// Custom deleter for CameraSensor
void deleteCameraSensor(CameraSensor* sensor) {
  cout << "Custom deleting CameraSensor " << sensor->id_ << "..." << endl;
  delete sensor;
}

void testCustomDeleter() {
  cout << "\n--- Testing Custom Deleter ---" << endl;
  
  // Create a unique_ptr with a custom deleter
  auto sensor = make_unique<CameraSensor>(1);
  
  // Access the object through the unique_ptr
  sensor->capture();
  
  // When sensor goes out of scope, the custom deleter will be called
}

int main() {
  testCustomDeleter();
  return 0;
}

```

## Camera HAL
Use smart pointers to manage image buffers and metadata safely.

## Interview Questions
1. What is RAII?

Ans : RAII (Resource Acquisition Is Initialization) is a C++ programming technique that ties the lifetime of a resource to the lifetime of an object. In simple terms, it means that when an object is created, it acquires a resource, and when the object is destroyed, it releases the resource. This ensures that resources are always properly managed and released, preventing memory leaks and other resource management issues.

2. Why use unique_ptr?

Ans : unique_ptr is used to manage the lifetime of an object. It is a smart pointer that keeps track of the object it points to, and when the unique_ptr goes out of scope, it automatically deletes the object it points to. This prevents memory leaks and other resource management issues.

3. Difference between unique_ptr and shared_ptr?

Ans : unique_ptr - unique_ptr is a smart pointer that provides exclusive ownership of an object. It is a lightweight smart pointer that is used to manage the lifetime of an object. It is a non-copyable smart pointer that can be moved from one unique_ptr to another. It is a move-only smart pointer that can be used to transfer ownership of an object from one unique_ptr to another. It is a compile-time checked smart pointer that can be used to detect memory leaks at compile time.

shared_ptr - shared_ptr is a smart pointer that provides shared ownership of an object. It is a reference-counted smart pointer that keeps track of the number of shared_ptrs that point to an object. When the number of shared_ptrs that point to an object becomes zero, the object is automatically deleted. It is a copyable smart pointer that can be copied from one shared_ptr to another. It is a move-only smart pointer that can be used to transfer ownership of an object from one shared_ptr to another. It is a compile-time checked smart pointer that can be used to detect memory leaks at compile time.

4. What is weak_ptr?

Ans : weak_ptr is a smart pointer that keeps track of the object it points to, but it does not own the object. It is used to observe the object without owning it. When the weak_ptr goes out of scope, it does not delete the object. This is useful for breaking circular references.

5. What is a circular reference?

Ans : Circular reference is a situation where two or more objects hold shared_ptr to each other, resulting in a cycle. This can lead to memory leaks because the reference count will never reach zero, and the objects will never be deleted.

Example of circular reference:

```cpp
#include <iostream>
#include <memory>

using namespace std;

class A;
class B;

class A {
public:
  A() { cout << "A constructor" << endl; }
  ~A() { cout << "A destructor" << endl; }
  shared_ptr<B> b_ptr;
};

class B {
public:
  B() { cout << "B constructor" << endl; }
  ~B() { cout << "B destructor" << endl; }
  shared_ptr<A> a_ptr;
};

void testCircularReference() {
  cout << "\n--- Testing Circular Reference ---" << endl;
  
  // Create a circular reference
  shared_ptr<A> a = make_shared<A>();
  shared_ptr<B> b = make_shared<B>();
  
  a->b_ptr = b;
  b->a_ptr = a;
  
  // When a and b go out of scope, their reference counts will not reach zero
  // because they hold shared_ptrs to each other.
  // This will result in a memory leak.
}

int main() {
  testCircularReference();
  return 0;
}

```

6. Why std::move?

Ans : std::move is a function that is used to convert an lvalue to an rvalue. It is a function that is used to transfer ownership of an object from one unique_ptr to another. It is a function that is used to move an object from one unique_ptr to another. It is a function that is used to move an object from one unique_ptr to another.

7. What is ownership?

Ans : Ownership is a concept that is used to manage the lifetime of an object. It is a concept that is used to manage the lifetime of an object. It is a concept that is used to manage the lifetime of an object.

8. What is a custom deleter?

Ans : A custom deleter is a function that is called when the object is deleted. It is used to release the resources held by the object. It is a function that is used to release the resources held by the object.

9. Why make_unique?

Ans : make_unique is a function that is used to create a unique_ptr. It is a function that is used to create a unique_ptr. It is a function that is used to create a unique_ptr.

10. Why make_shared?

Ans : make_shared is a function that is used to create a shared_ptr. It is a function that is used to create a shared_ptr. It is a function that is used to create a shared_ptr.

11. What is exception safety?

Ans : Exception safety is a property of a C++ program that ensures that the program remains in a valid state even when exceptions are thrown. It is a property that is used to ensure that the program remains in a valid state even when exceptions are thrown. It is a property that is used to ensure that the program remains in a valid state even when exceptions are thrown.

12. What is reference counting?

Ans : Reference counting is a memory management technique that is used to keep track of the number of references to an object. It is a technique that is used to keep track of the number of references to an object. It is a technique that is used to keep track of the number of references to an object.

13. When is shared_ptr memory freed?

Ans : shared_ptr memory is freed when the number of shared_ptrs that point to an object becomes zero. It is freed when the number of shared_ptrs that point to an object becomes zero. It is freed when the number of shared_ptrs that point to an object becomes zero.

14. Can unique_ptr be copied?

Ans : No, unique_ptr cannot be copied. It is a move-only smart pointer that can be moved from one unique_ptr to another. It is a move-only smart pointer that can be used to transfer ownership of an object from one unique_ptr to another. It is a move-only smart pointer that can be used to transfer ownership of an object from one unique_ptr to another.

15. Can weak_ptr own memory?

Ans : No, weak_ptr cannot own memory. It is a non-owning observer that keeps track of the object it points to, but it does not own the object. It is used to observe the object without owning it. When the weak_ptr goes out of scope, it does not delete the object. This is useful for breaking circular references.

16. What is use_after_free?

Ans : Use-after-free is a memory management error that occurs when a program tries to access memory after it has been freed. It is a common source of security vulnerabilities and can lead to crashes and other undefined behavior. It is a memory management error that occurs when a program tries to access memory after it has been freed. It is a common source of security vulnerabilities and can lead to crashes and other undefined behavior.

17. What is memory leak?

Ans : Memory leak is a memory management error that occurs when a program fails to release memory that it no longer needs. It can lead to crashes and other undefined behavior. It is a memory management error that occurs when a program fails to release memory that it no longer needs. It can lead to crashes and other undefined behavior.

18. What is double delete?

Ans : Double delete is a memory management error that occurs when a program tries to delete the same memory twice. It can lead to crashes and other undefined behavior. It is a memory management error that occurs when a program tries to delete the same memory twice. It can lead to crashes and other undefined behavior.

19. RAII in embedded?

Ans : RAII in embedded is a technique that is used to manage the lifetime of resources in an embedded system. It is a technique that is used to manage the lifetime of resources in an embedded system. It is a technique that is used to manage the lifetime of resources in an embedded system.

20. RAII in Camera HAL?

Ans : RAII in Camera HAL is a technique that is used to manage the lifetime of resources in a camera hardware abstraction layer. It is a technique that is used to manage the lifetime of resources in a camera hardware abstraction layer. It is a technique that is used to manage the lifetime of resources in a camera hardware abstraction layer.

21. Smart pointer overhead?

Ans : Smart pointer overhead is the extra memory and time that is required to use a smart pointer compared to a raw pointer. It is a small overhead that is required to use a smart pointer compared to a raw pointer. It is a small overhead that is required to use a smart pointer compared to a raw pointer.

22. Lock on weak_ptr?

Ans : lock() on weak_ptr is used to acquire a shared_ptr to the object that the weak_ptr points to. If the object has already been deleted, lock() will return an empty shared_ptr.

23. Rule of Zero?

Ans : Rule of Zero is a programming principle that states that if a class does not have any custom destructor, copy constructor, or copy assignment operator, then it does not need any custom move constructor or move assignment operator.

24. Raw pointer vs unique_ptr?

Ans : Raw pointer is a pointer that points to a memory location. It is a pointer that is not managed by any smart pointer. It is a pointer that is not managed by any smart pointer.

25. Raw pointer vs shared_ptr?

Ans : Raw pointer is a pointer that points to a memory location. It is a pointer that is not managed by any smart pointer. It is a pointer that is not managed by any smart pointer.

26. Can custom deleter close sockets?

Ans : Yes, a custom deleter can be used to close sockets. It is a function that is called when the object is deleted. It is used to release the resources held by the object.

27. Can unique_ptr manage arrays?

Ans : Yes, unique_ptr can manage arrays. It is a smart pointer that can be used to manage the lifetime of arrays. It is a smart pointer that can be used to manage the lifetime of arrays.

28. Ownership transfer?

Ans : Ownership transfer is the process of transferring the ownership of an object from one unique_ptr to another. It is a move-only operation that can be done using std::move. It is a move-only operation that can be done using std::move. It is a move-only operation that can be done using std::move.

29. Best practices?

Ans : Best practices for using smart pointers include using make_unique and make_shared instead of new, using unique_ptr for exclusive ownership, using shared_ptr for shared ownership, and using weak_ptr for non-owning observations.

30. Common interview mistakes?

Ans : Common interview mistakes for using smart pointers include not using make_unique and make_shared instead of new, not using unique_ptr for exclusive ownership, not using shared_ptr for shared ownership, and not using weak_ptr for non-owning observations.

