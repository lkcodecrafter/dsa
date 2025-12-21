#include "IntCell.h"
using namespace std;

IntCell::IntCell(int x)
    : storedValue {x}
{
}
void IntCell::write(int x){
    storedValue =x;
}
int IntCell::read() const{
    return storedValue;
}

 


