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