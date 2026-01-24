/*
Q1. Longest Substring Without Repeating Characters (Sliding Window)
Given a string s, find the length of the longest substring without repeating characters.
Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> charMap;
        int left = 0, maxLength = 0;

        for (int right = 0; right < s.length(); right++) {
            if (charMap.find(s[right]) != charMap.end()) {
                left = max(left, charMap[s[right]] + 1);
            }
            charMap[s[right]] = right;
            maxLength = max(maxLength, right - left + 1);
        }
        return maxLength;
    }
};

/*
Concept Explanation:
1. We use an unordered_map to keep track of the last seen index of each character.
2. We maintain a sliding window defined by the left and right pointers.
3. If we encounter a repeating character, we move the left pointer to the right of its last seen position.
4. We update the maximum length of the substring found so far.
Example Usage:
int main() {
    Solution solution;
    string s = "abcabcbb";
    cout << "Length of longest substring without repeating characters: " 
         << solution.lengthOfLongestSubstring(s) << endl; // Output: 3
    return 0;
}
Why sliding window?
The sliding window technique is used here to efficiently find the longest substring without repeating 
characters by dynamically adjusting the window size based on the characters encountered.
Time Complexity: O(n), where n is the length of the string. Each character is processed at most twice.
Space Complexity: O(min(m, n)), where m is the size of the character set and n is the length of the string.
what is sliding window?
A sliding window is a subarray or substring that moves over the data structure to find a specific condition,
such as the longest substring without repeating characters in this case.
How to choose left and right pointers?
The right pointer expands the window by moving forward through the string, while the left pointer contracts
the window when a repeating character is found, ensuring all characters in the window are unique.
give an example of sliding window?
For example, in the string "abcabcbb":
- Start with left = 0, right = 0: window = "a"
- Move right to 1: window = "ab"
- Move right to 2: window = "abc"
- Move right to 3: window = "abca" (left moves to 1)
- Move right to 4: window = "bc"
- Move right to 5: window = "bca"
- Move right to 6: window = "cab"
- Move right to 7: window = "abc"
Not able to understand?
how right pointer showing bc?
When the right pointer moves to index 4 (character 'b'), the left pointer moves to index 1 (character 'b')
to ensure all characters in the window are unique. Thus, the current window becomes "bc".
*/