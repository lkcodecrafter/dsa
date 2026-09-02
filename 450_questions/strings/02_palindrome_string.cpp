/*
    QUESTION    : Palindrome String
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/palindrome-string0817/1
    LeetCode    : https://leetcode.com/problems/valid-palindrome/
*/

#include <iostream>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Two pointer comparison from opposite ends
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int isPalindrome(string S) {
        int left = 0;
        int right = S.length() - 1;

        while (left < right) {
            if (S[left] != S[right]) {
                return 0; // Mismatch found -> Not palindrome
            }
            left++;
            right--;
        }

        return 1; // All characters matched
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `left = 0, right = S.length() - 1`.
 * - `while (left < right)`: if `S[left] != S[right]` return 0; `left++; right--;`
 * - Return 1.
 * - Time: O(N), Space: O(1).
 */
