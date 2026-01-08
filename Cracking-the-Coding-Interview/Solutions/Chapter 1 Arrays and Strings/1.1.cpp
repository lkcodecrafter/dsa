/*
 *Q1.1 Implement an algorithm to determine if a string has all unique characters.What if you can not use additional data structures?
 */

#include <iostream>
#include <cstring>
using namespace std;

bool isUniqueChars(const string &str) {
    // Assuming the character set is ASCII
    if (str.length() > 128) {
        return false; // More characters than total unique ASCII characters
    }

    bool charSet[128] = {false}; // Initialize all to false

    for (char c : str) {
        int val = static_cast<int>(c);
        if (charSet[val]) {
            return false; // Character already found in string
        }
        charSet[val] = true; // Mark character as found 
        // value of charSet at index val is set to true
        // what is val here? val is the ASCII value of character c
        // For example, if c is 'A', val will be 65
        // So charSet[65] will be set to true
        // This way, we keep track of which characters have been seen
    }
    return true; // All characters are unique
}

bool isUnique2(const string &str) {
    // Assuming the character set is ASCII
    if (str.length() > 128) {
        return false; // More characters than total unique ASCII characters
    }

    for (size_t i = 0; i < str.length(); ++i) {
        for (size_t j = i + 1; j < str.length(); ++j) {
            if (str[i] == str[j]) {
                return false; // Found a duplicate character
            }
        }
    }
    return true; // All characters are unique
}

int main()
{
	string s1 = "Hello World!";
	string s2 = "asdfghjkl1234567890";
	cout << isUniqueChars(s1) << " " << isUniqueChars(s2) << endl;
	cout << isUnique2(s1) << " " << isUnique2(s2) << endl;
	return 0;
}