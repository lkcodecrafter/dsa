#include<iostream>
using namespace std;

class complex{

    private:
    int x;
    int y;

    public:
    complex(int a, int b){
        this->x = a;
        this->y = b;
    }
    complex operator+(complex c){
        return complex(x+c.x, y+c.y); // operator keyword is used to overload the + operator for complex numbers. It takes another complex number as an argument and returns a new complex number that is the sum of the two complex numbers. 

    }

    complex(){
        this->x = 1;
        this->y = 1;
    }

    void display(){
        cout << "Complex number: " << x << " + " << y << " i" << endl;
    }
};

int main(){
    complex c(3,4);
   // complex c1(5,6);
    complex c1;
    complex c2 = c + c1; // This line uses the overloaded + operator to add two complex numbers. It calls the operator+ function defined in the complex class, passing c1 as an argument. The result is stored in a new complex number c2.
    c2.display();
    return 0;
}