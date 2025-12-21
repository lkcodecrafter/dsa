#include<iostream>
#include "IntCell.h"
using namespace std;

int main(){
    IntCell m;
    m.write(10);
    cout<<m.read()<<endl;

    //Using pointer
    IntCell *p;
    p = new IntCell{2};
    p->write(20);
    cout<<p->read();

    //delete
    delete p;
    return 0;
}


//g++ testIntCell.cpp IntCell.cpp -o testIntCell