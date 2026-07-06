#include <iostream>
using namespace std;

class Camera {

public:
  virtual void name() = 0;
};

class SubCam : public Camera {

public:
  void name() { cout << "The sub camera modules"; }
};

int main() {

  Camera *c =
      new SubCam(); // why we can create pointer of abstract class? Because we
                    // cannot create object of abstract class, but we can create
                    // pointer of abstract class and point it to an object of a
                    // derived class that implements the pure virtual
                    // function(s) of the abstract class.
  // This allows us to achieve polymorphism, where we can call the overridden
  // function through the base class pointer, and the appropriate function in
  // the derived class will be executed at runtime.
  //  but same we can do with object of derived class as well, then why we need
  //  pointer of abstract class? The main reason to use a pointer of the
  //  abstract class is to achieve polymorphism. By using a pointer of the
  //  abstract class, we can write code that is more flexible and can work with
  //  any derived class that implements the pure virtual function(s) of the
  //  abstract class. This allows us to write code that is not tightly coupled
  //  to a specific implementation, and it promotes code reusability and
  //  maintainability.
  // Additionally, using pointers allows us to take advantage of dynamic memory
  // allocation and manage resources more efficiently in certain scenarios.
  c->name();

  SubCam cm; // so we can also create object of derived class and call the
             // function, then why we need pointer of abstract class? The main
             // reason to use a pointer of the abstract class is to achieve
             // polymorphism. By using a pointer of the abstract class, we can
             // write code that is more flexible and can work with any derived
             // class that implements the pure virtual function(s) of the
             // abstract class. This allows us to write code that is not tightly
             // coupled to a specific implementation, and it promotes code
             // reusability and maintainability.
  cm.name();
}

/*

User only knows:

camera->Capture();

Doesn't know internal implementation.

*/