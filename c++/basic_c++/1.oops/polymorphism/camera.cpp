#include<iostream>
using namespace std;

class Camera{

    public:
    virtual void name()=0;

};

class SubCam : public Camera{

  public:
  void name(){
    cout<<"name is called here";
  }

};

int main(){
    
    Camera * c = new SubCam(); // Runtime decides function.
    c->name();
    
    
}

 