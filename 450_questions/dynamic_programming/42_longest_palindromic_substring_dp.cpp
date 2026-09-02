/*
    QUESTION    : Longest Palindromic Substring (Expand Around Center)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-palindrome-in-a-string3411/1
    LeetCode    : https://leetcode.com/problems/longest-palindromic-substring/
*/

#include <iostream>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Expand around 2N - 1 centers
// S.C : O(1)   - Constant auxiliary space
class Solution {
private:
    void expand(const string& S, int l, int r, int& startIdx, int& maxLen) {
        while (l >= 0 && r < S.length() && S[l] == S[r]) {
            l--;
            r++;
        }

        int currLen = r - l - 1;
        if (currLen > maxLen) {
            maxLen = currLen;
            startIdx = l + 1;
        }
    }

public:
    string longestPalin (string S) {
        int startIdx = 0;
        int maxLen = 1;

        for (int i = 0; i < S.length(); i++) {
            expand(S, i, i, startIdx, maxLen);     // Odd length palindromes
            expand(S, i, i + 1, startIdx, maxLen); // Even length palindromes
        }

        return S.substr(startIdx, maxLen);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Expand around odd center `(i, i)` and even center `(i, i+1)`.
 * - Track `startIdx` and `maxLen`.
 * - Time: O(N^2), Space: O(1).
 */
