 /*
 *Q1.2 Write code to reverse a C-Style String.(S-String means that "abcd" is represented as five charaters,including the null charater.)
 */

#include <iostream>
#include <cstring>
using namespace std;


void reverseCString(char str[]) {
    if (str == nullptr) {
        return; // Handle null pointer
    }

    int length = 0;
    while (str[length] != '\0') {
        length++; // Calculate the length of the string
    }

    int start = 0;
    int end = length - 1;

    while (start < end) {
        // Swap characters at start and end positions
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

int main()
{
    char str1[] = "Hello World!";
    char str2[] = "abcdefg";

    reverseCString(str1);
    reverseCString(str2);

    cout << str1 << endl; // Output: !dlroW olleH
    cout << str2 << endl; // Output: gfedcba

    return 0;
}