#include<iostream>
using namespace std;

class Camera{

    public:
    virtual void name()=0;

};

class SubCam : public Camera{

    public:
    void name(){
        cout<<"The sub camera modules";
    }

};

int main(){
    /*
    Camera * c = new SubCam();
    c->name();
    */
    SubCam cm;
    cm.name();
}


/*

User only knows:

camera->Capture();

Doesn't know internal implementation.

*/