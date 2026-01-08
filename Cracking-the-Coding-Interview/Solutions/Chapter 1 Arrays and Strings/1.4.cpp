/*
 *Q1.4 Write a method to decide if two strings are anagrams or not.
 */

#include <iostream>
#include <cstring>
using namespace std;

bool areAnagrams(const string &str1, const string &str2) {
    if (str1.length() != str2.length()) {
        return false; // Anagrams must be of the same length
    }

    int charCount[128] = {0}; // Assuming ASCII character set

    for (char c : str1) {
        charCount[static_cast<int>(c)]++; // Count each character in str1
    }

    for (char c : str2) {
        charCount[static_cast<int>(c)]--; // Decrease count for each character in str2
        if (charCount[static_cast<int>(c)] < 0) {
            return false; // More occurrences in str2 than in str1
        }
    }

    return true; // All counts are zero, so they are anagrams
}

int main()
{
    string str1 = "listen";
    string str2 = "silent";
    string str3 = "hello";

    cout << areAnagrams(str1, str2) << endl; // Output: 1 (true)
    cout << areAnagrams(str1, str3) << endl; // Output: 0 (false)

    return 0;
}
