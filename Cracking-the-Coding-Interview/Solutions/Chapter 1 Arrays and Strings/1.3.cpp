/*
 *Q1.3 Design an algorithm and write code to remove the duplicate charaters in a string without using any additional buffer.
 *NOTE:One or twp addtional variables are fine.An extra copy of the array is not.
 *FOLLOW UP
 *Write the test cases for this method.
 */

#include <iostream>
#include <cstring>
using namespace std;


void removeDuplicates(char str[]) {
    if (str == nullptr) {
        return; // Handle null pointer
    }

    int length = 0;
    while (str[length] != '\0') {
        length++; // Calculate the length of the string
    }

    if (length < 2) {
        return; // No duplicates possible in strings of length 0 or 1/ how? because a single character or empty string cannot have duplicates
    }

    int tail = 1; // Index to place the next unique character

    for (int i = 1; i < length; ++i) {
        int j;
        for (j = 0; j < tail; ++j) {
            if (str[i] == str[j]) {
                break; // Duplicate found
            }
        }
        if (j == tail) { // No duplicate found
            str[tail] = str[i];
            tail++;
        }
    }
    str[tail] = '\0'; // Null-terminate the modified string
}

int main()
{
    char str1[] = "banana";
    char str2[] = "abracadabra";
    char str3[] = "hello world";

    removeDuplicates(str1);
    removeDuplicates(str2);
    removeDuplicates(str3);

    cout << str1 << endl; // Output: ban
    cout << str2 << endl; // Output: abrcd
    cout << str3 << endl; // Output: helo wrd

    return 0;
}

// dry run for "banana":
// Initial string: "banana"
// i=1 ('a'): j=0 to tail(1): no duplicate, str[1]='a', tail=2 -> "ba...."
// i=2 ('n'): j=0 to tail(2): no duplicate, str[2]='n', tail=3 -> "ban..."
// i=3 ('a'): j=0 to tail(3): duplicate found at j
// i=4 ('n'): j=0 to tail(3): duplicate found at j
// i=5 ('a'): j=0 to tail(3): duplicate found at j
// Final string: "ban"
