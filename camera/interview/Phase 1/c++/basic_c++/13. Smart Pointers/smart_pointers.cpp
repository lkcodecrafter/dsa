#include<iostream>
#include<memory>

/*
Smart Pointers

VERY IMPORTANT

unique_ptr

Single owner.

unique_ptr<Camera> cam =
make_unique<Camera>();

Cannot copy.

*/

class SmartPointer
{
public:
    SmartPointer()
    {
        std::cout << "Constructor called" << std::endl;
    }
    ~SmartPointer()
    {
        std::cout << "Destructor called" << std::endl;
    }

};

int main()
{
    {
        std::cout << "Creating smart pointer" << std::endl;
        std::unique_ptr<SmartPointer> smartPtr = std::make_unique<SmartPointer>();
        std::cout << "Smart pointer created" << std::endl;
    }
    std::cout << "Exiting main function" << std::endl;
    return 0;
}