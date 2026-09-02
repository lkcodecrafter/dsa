/*
    QUESTION    : Interleaved Strings (Check if C is an interleaving of A and B)
    Company Tags: Amazon, Microsoft, Google, Yahoo
    GfG Link    : https://practice.geeksforgeeks.org/problems/interleaved-strings/1
    LeetCode    : https://leetcode.com/problems/interleaving-string/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - 2D Dynamic Programming (or 1D space optimized)
// S.C : O(M)     - 1D boolean row
class Solution {
public:
    bool isInterleave(string A, string B, string C) {
        int n = A.length();
        int m = B.length();

        if (n + m != C.length()) return false;

        vector<bool> dp(m + 1, false);

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0) {
                    dp[j] = true;
                } else if (i == 0) {
                    dp[j] = dp[j - 1] && (B[j - 1] == C[j - 1]);
                } else if (j == 0) {
                    dp[j] = dp[j] && (A[i - 1] == C[i - 1]);
                } else {
                    dp[j] = (dp[j] && A[i - 1] == C[i + j - 1]) ||
                            (dp[j - 1] && B[j - 1] == C[i + j - 1]);
                }
            }
        }

        return dp[m];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[j] = (dp[j] && A[i-1] == C[i+j-1]) || (dp[j-1] && B[j-1] == C[i+j-1])`.
 * - Time: O(N * M), Space: O(M).
 */
