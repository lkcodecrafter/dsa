/*
Q1.9 String Compression: Implement a method to perform basic string compression using the counts 
of repeated characters. For example, the string aabcccccaaa would become a2blc5a3, If the 
"compressed" string would not become smaller than the original string, your method should return 
the original string. You can assume the string has only uppercase and lowercase letters (a - z). 
Hints: #92, if 110 
 */

#include <iostream>
#include <cstring>
using namespace std;

void compressString(const string &input, string &output) {
    int length = input.length();
    if (length == 0) {
        output = input; // Handle empty string
        return;
    }

    output.clear();
    int count = 1;

    for (int i = 1; i <= length; ++i) {
        if (i < length && input[i] == input[i - 1]) {
            count++; // Increment count for repeated characters
        } else {
            output += input[i - 1]; // Append character
            output += to_string(count); // Append count
            count = 1; // Reset count
        }
    }

    // Check if compressed string is smaller than original
    if (output.length() >= length) {
        output = input; // Return original string if not smaller
    }
}

int main() {
    string str1 = "aabcccccaaa";
    string compressed1;
    compressString(str1, compressed1);
    cout << "Original: " << str1 << ", Compressed: " << compressed1 << endl; // Output: a2b1c5a3

    string str2 = "abcdef";
    string compressed2;
    compressString(str2, compressed2);
    cout << "Original: " << str2 << ", Compressed: " << compressed2 << endl; // Output: abcdef

    return 0;
}
