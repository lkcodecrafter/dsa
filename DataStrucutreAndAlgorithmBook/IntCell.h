#ifndef IntCell_H
#define IntCell_H 

// what is the purpose of this line
// to avoid multiple inclusion problem
// of header files
// IntCell.h
// A simple class that encapsulates an integer
// value, allowing clients to read and write
// it via member functions.
// Note that this is just an example for illustration
// purposes; in real code, one would simply use
// an int directly.
// how call IntCell_H in IntCell.cpp
// #include "IntCell.h"
// declaration of IntCell class
// with its member functions

class IntCell{
    public:

    explicit IntCell(int initialValue = 0);
    int read()const;
    void write(int x);
    
private:
    int storedValue;
};
#endif


