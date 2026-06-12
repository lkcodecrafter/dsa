#include<iostream>
using namespace std;

class Base{

    public:
    virtual ~Base(){
        cout<<"Base destructor called"<<endl;
    }
};

class Derived : public Base {

    public:
    ~Derived() {
        cout<<"Derived destructor called"<<endl;
    }
};

int main(){

    Base* bs = new Derived();
    delete bs;
}

/*
Without virtual destructor:
Memory leak.

*/