#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> charIndex(128, -1); // ASCII size
        int maxLength = 0;
        int left = 0; // Left pointer of the sliding window

        for (int right = 0; right < s.length(); ++right) {
            char currentChar = s[right];

            // If the character has been seen and is within the current window
            if (charIndex[currentChar] >= left) {
                left = charIndex[currentChar] + 1; // Move left pointer
            }

            charIndex[currentChar] = right; // Update the last seen index
            maxLength = max(maxLength, right - left + 1); // Update max length
        }

        return maxLength;
    }
};

// Please write Dry Run and Explanation for the code above
/*
Dry Run:
Consider the input string "abcabcbb".
1. Initialize `charIndex` with -1, `maxLength` to 0, and `left` to 0.
2. Iterate through the string with `right` pointer:
    - right = 0 ('a'): Update charIndex['a'] = 0, maxLength = 1
    - right = 1 ('b'): Update charIndex['b'] = 1, maxLength = 2
    - right = 2 ('c'): Update charIndex['c'] = 2, maxLength = 3
    - right = 3 ('a'): 'a' seen at index 0, move left to 1. Update charIndex['a'] = 3, maxLength = 3
    - right = 4 ('b'): 'b' seen at index 1, move left to 2. Update charIndex['b'] = 4, maxLength = 3
    - right = 5 ('c'): 'c' seen at index 2, move left to 3. Update charIndex['c'] = 5, maxLength = 3
    - right = 6 ('b'): 'b' seen at index 4, move left to 5. Update charIndex['b'] = 6, maxLength = 3
    - right = 7 ('b'): 'b' seen at index 6, move left to 7. Update charIndex['b'] = 7, maxLength = 3
3. Final maxLength is 3, corresponding to the substring "abc".
Explanation:
The algorithm uses a sliding window approach to find the longest substring without repeating characters.
1. We maintain a vector `charIndex` to store the last seen index of each character.
2. Two pointers, `left` and `right`, define the current window of characters being considered.
3. As we iterate with the `right` pointer, we check if the current character has been seen 
before within the current window (i.e., its last seen index is greater than or equal to `left`).
4. If it has been seen, we move the `left` pointer to one position right of the last seen index of 
that character to ensure all characters in the window are unique.
5. We update the last seen index of the current character and calculate the length of the current window, 
updating `maxLength` if it's larger than the previous maximum.
6. Finally, we return `maxLength`, which represents the length of the longest substring without repeating 
characters.
*/