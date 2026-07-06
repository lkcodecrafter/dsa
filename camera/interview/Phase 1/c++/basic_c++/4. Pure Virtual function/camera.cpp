#include <iostream>
using namespace std;

class Camera{
    public:
        virtual void takePhoto() = 0; // pure virtual function
        // Makes class abstract.
};

int main() {
    // Camera cam; // Error: cannot instantiate abstract class
    // Cannot create object.
    return 0;
}
