#include<iostream>
using namespace std;

// What is StrStr?
// StrStr is a function that finds the first occurrence of a substring (needle) in a
// larger string (haystack). It returns the index of the first occurrence of the
// needle in the haystack, or -1 if the needle is not found. If the needle is an
// empty string, the function returns 0.
// Example:
// Input: haystack = "hello", needle = "ll"
// Output: 2
// Input: haystack = "aaaaa", needle = "bba"
// Output: -1
// Implementation of StrStr function in C++17
// What is \0?
// In C and C++, strings are represented as arrays of characters terminated by a
// special null character '\0'. This character indicates the end of the string.
// How B[j] != '\0' works?
// The condition B[j] != '\0' checks whether the current character in the needle
// string is not the null terminator. If it is not, it means there are more characters
// to compare in the needle string.
// But [J]== '\0'?
// When B[j] == '\0', it indicates that we have reached the end of the needle string.
// This means that all characters in the needle have been successfully matched with
// What is benefit of j++?
// The j++ increments the index j to move to the next character in the needle string
// during the comparison process. This allows us to check each character of the needle
// against the corresponding characters in the haystack string.

int strStr(const char* A, const char* B) {
    if (*B == '\0') {
        return 0; // An empty needle is found at index 0
    }

    for (int i = 0; A[i] != '\0'; i++) {
        int j = 0;
        while (B[j] != '\0' && A[i + j] != '\0' && A[i + j] == B[j]) {
            j++;
        }
        if (B[j] == '\0') {
            return i; // Found the needle at index i
        }
    }
    return -1; // Needle not found
} 


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

// Explanation of the code:
// 1. The function strStr takes two constant character pointers A (haystack) and
//    B (needle) as input.
// 2. It first checks if the needle B is an empty string. If it is, the function
//    returns 0, indicating that an empty needle is found at index 0.
// 3. The outer for loop iterates through each character in the haystack A.
// 4. Inside the loop, a variable j is initialized to 0 to keep track of the current
//    index in the needle B.
// 5. The inner while loop compares characters from the haystack A and needle B
//    as long as the characters match and neither string has reached its end.
// 6. If the entire needle B is found in the haystack A (i.e., B[j] == '\0'),
//    the function returns the starting index i where the needle is found.
// 7. If the needle is not found after checking all possible positions in the
//    haystack, the function returns -1.
// Dry run example:
// Let's say we have haystack A = "hello" and needle B = "ll".
// - The function starts by checking if B is empty. It's not, so we proceed.
// - The outer loop starts with i = 0 (pointing to 'h' in "hello").
// - The inner loop compares 'h' with 'l'. They don't match, so we move to the next i.
// - Now i = 1 (pointing to 'e'). 'e' doesn't match 'l', so we move to the next i.
// - Now i = 2 (pointing to 'l'). The inner loop starts comparing:
//   - j = 0: 'l' (A[2]) matches 'l' (B[0]), increment j to 1.
//   - j = 1: 'l' (A[3]) matches 'l' (B[1]), increment j to 2.
//   - Now B[2] is '\0', indicating the end of the needle.  
// - The function returns i = 2, which is the starting index of the first occurrence
//   of "ll" in "hello".
