/*
    QUESTION    : Word Break
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/word-break1352/1
    LeetCode    : https://leetcode.com/problems/word-break/
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Dynamic programming checking dictionary substrings
// S.C : O(N + D) - DP array and hash set of dictionary
class Solution {
public:
    int wordBreak(string A, vector<string> &B) {
        unordered_set<string> dict(B.begin(), B.end());
        int n = A.length();

        vector<bool> dp(n + 1, false);
        dp[0] = true; // Base case: empty string

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && dict.find(A.substr(j, i - j)) != dict.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n] ? 1 : 0;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[0] = true`.
 * - `dp[i] = true` if exists `j < i` such that `dp[j] && dict.count(A[j...i-1])`.
 * - Time: O(N^2), Space: O(N + D).
 */
