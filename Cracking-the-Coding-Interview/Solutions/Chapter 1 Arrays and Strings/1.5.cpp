/*
 *Q1.5 Write a method to replace all spaces in a string with '%20'.
 */

#include <iostream>
#include <cstring>
using namespace std;

void replaceSpaces(char str[], int trueLength) {
    int spaceCount = 0;
    for (int i = 0; i < trueLength; ++i) {
        if (str[i] == ' ') {
            spaceCount++; // Count spaces
        }
    }

    int newLength = trueLength + spaceCount * 2; // Each space is replaced by three characters '%20'
    str[newLength] = '\0'; // Null-terminate the modified string

    for (int i = trueLength - 1; i >= 0; --i) {
        if (str[i] == ' ') {
            str[newLength - 1] = '0';
            str[newLength - 2] = '2';
            str[newLength - 3] = '%';
            newLength -= 3;
        } else {
            str[newLength - 1] = str[i];
            newLength--;
        }
    }
}

int main()
{
    char str1[] = "Mr John Smith    ";
    int trueLength1 = 13;
    replaceSpaces(str1, trueLength1);
    cout << str1 << endl; // Output: "Mr%20John%20Smith"

    char str2[] = "Hello World   ";
    int trueLength2 = 11;
    replaceSpaces(str2, trueLength2);
    cout << str2 << endl; // Output: "Hello%20World"

    return 0;
}