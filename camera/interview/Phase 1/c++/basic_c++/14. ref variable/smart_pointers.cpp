#include<iostream>
using namespace std;

int main()
{ 
    int x = 10;
    int &y = x;
    y =11;
    cout << "Value of x: " << x << endl;
    cout << "Value of y: " << y << endl;
    return 0;
}