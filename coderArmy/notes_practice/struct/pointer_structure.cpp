#include <stdlib.h>
#include<iostream>
using namespace std;


//Pointer to stucture
//Accessing structure using pointer

struct Rectangle{
    int length;
    int breath;
};

int main(int argc, char const *argv[])
{
    struct Rectangle r ={3,5};
    struct Rectangle *p = &r;
    r.length = 35;
    (*p).length = 20;

    p->breath = 30;

    cout<<p;
    return 0;
}

