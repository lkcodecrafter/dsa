/*
    QUESTION    : Longest Palindrome in a String (Longest Palindromic Substring)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-palindrome-in-a-string3411/1
    LeetCode    : https://leetcode.com/problems/longest-palindromic-substring/
*/

#include <iostream>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Expand Around Center technique
// S.C : O(1)   - Constant auxiliary space
class Solution {
private:
    void expand(const string& s, int left, int right, int& start, int& maxLen) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        int len = right - left - 1;
        if (len > maxLen) {
            maxLen = len;
            start = left + 1;
        }
    }

public:
    string longestPalin(string S) {
        int n = S.length();
        if (n <= 1) return S;

        int start = 0;
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            expand(S, i, i, start, maxLen);     // Odd-length palindromes (center at i)
            expand(S, i, i + 1, start, maxLen); // Even-length palindromes (center between i and i+1)
        }

        return S.substr(start, maxLen);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Expand Around Center for both odd (`i, i`) and even (`i, i+1`) centers.
 * - Track `start` and `maxLen`. Return `S.substr(start, maxLen)`.
 * - Time: O(N^2), Space: O(1).
 */
