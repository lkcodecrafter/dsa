#include<stdlib.h>
#include<iostream>
using namespace std;
//Access heap memory by pionter

int main(int argc, char const *argv[])
{
    int *p;  // tyep care
    p =     (int*)  malloc(5 * sizeof(int)); // it's format void

    //In c++ we can add as below
    p= new int[5];

    p[0]=1;
    p[1]=2;
    cout<<p<<endl;
    
    //print first value
    cout<<*p<<endl;
    
    //print all value
    for(int i=0;i<5;i++){
        cout<<*(p+i)<< " ";
    }

    return 0;
}
