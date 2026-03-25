#include<stdlib.h>
#include<iostream>

using namespace std;

void basicPointer(){
    
    int a = 10;
    int *p = &a;

    cout<<"The a value is " <<a<<endl;
    cout<<"The address of a" <<&a<<endl;
    cout<<"The pointer is " <<p<<endl;
    cout<<"The pointer value is "<<*p<<endl;
}

void modifyUsingPointer(){
    int a =10;
    int *p = &a;

    cout<<"Before A value change"<<endl;
    
    cout<<"The a value is " <<a<<endl;
    cout<<"The address of a" <<&a<<endl;
    cout<<"The pointer is " <<p<<endl;
    cout<<"The pointer value is "<<*p<<endl;


    *p = 20;

    cout<<"After A value changed using pointer"<<endl;
    cout<<"The a value is " <<a<<endl;
    cout<<"The address of a" <<&a<<endl;
    cout<<"The pointer is " <<p<<endl;
    cout<<"The pointer value is "<<*p<<endl;
    //In this example pointer can change the Original value.
    
}
void AddNull(){
    int *p = NULL;
    printf("%d", *p);
}
int main()
{
    AddNull();
    return 0;
}