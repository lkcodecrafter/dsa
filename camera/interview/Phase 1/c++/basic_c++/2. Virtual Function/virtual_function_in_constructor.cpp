#include <iostream>

using namespace std;
class Base
{
public:
    virtual void show()
    {
        cout << "Base class show function called" << endl;
    }
};

class Derived : public Base
{

public:

    Derived(){
        show(); // Calls Base class show function, not Derived class show function, 
        // because the object is still being constructed and the vptr points to the Base class's vtable.
        // But it's calling derived class show function, because the object is already constructed and the vptr points to the derived class's vtable.
        // How to call the base class show function from the constructor of the derived class?
        // You can call the base class show function from the constructor of the derived class using the scope resolution operator (::) to specify that you want to call the base class version of the function. Here's how you can do it:
         Base::show(); // This will call the base class show function, regardless of the state of the object construction.
    }

    void show()
    {
        cout << "Derived class show function called" << endl;
        
    }
};

int main(){
    
Base* bs = new Derived();
bs->show();
}

/*

Question:
How?

Answer:
Uses vtable + vptr.

*/