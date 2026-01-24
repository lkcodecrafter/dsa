#include<stdlib.h>
#include<iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    int a = 11;
    int &b = a;
    cout<<a<<endl;
    b++;
    cout<<b<<endl;
    cout<<a;
    return 0;
}
// Use of reference
// Use for parameter passing
// To write small functions
