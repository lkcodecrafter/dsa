#include<iostream>
using namespace std;
class Camera {
    private:
    int data;

    public:
    void setData(int d) {
       data = d;
    }
    int getData(){
        return data;
    }
};

int main(){
    Camera cm;
    cm.setData(3);
    cout<<cm.getData();
}

/*

Question:
Why private?

Answer:
To hide internal implementation and protect data.

*/
