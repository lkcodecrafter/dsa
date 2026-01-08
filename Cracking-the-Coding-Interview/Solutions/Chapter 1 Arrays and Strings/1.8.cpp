/*
 *Q1.8 Assume you have a method isSubstring which checks if one word is a substring of another.
 *Given two things,s1 and s2,write code to check if s2 is a rotation of s1 using only one call
 *to isSubstring(i.e.,"waterbottlde"is a rotation of"erbottlewat").
 */

#include <iostream>
#include <cstring>
using namespace std;


bool isSubstring(const string &s1, const string &s2) {
    return s1.find(s2) != string::npos; // npos indicates not found // when s2 is found in s1
    // we return true, otherwise false
}

bool isRotation(const string &s1, const string &s2) {
    if (s1.length() != s2.length() || s1.empty()) {
        return false;
    }
    string s1s1 = s1 + s1; // Concatenate s1 with itself
    // why concatenate? because if s2 is a rotation of s1, it must be a substring of s1s1
    // example: s1 = "waterbottle", s2 = "erbottlewat"
    // s1s1 = "waterbottlewaterbottle"
    // s2 is indeed a substring of s1s1
    return isSubstring(s1s1, s2); // Check if s2 is a substring of s1s1
}

int main() {
    string s1 = "waterbottle";
    string s2 = "erbottlewat";

    if (isRotation(s1, s2)) {
        cout << s2 << " is a rotation of " << s1 << endl;
    } else {
        cout << s2 << " is not a rotation of " << s1 << endl;
    }

    return 0;
}
