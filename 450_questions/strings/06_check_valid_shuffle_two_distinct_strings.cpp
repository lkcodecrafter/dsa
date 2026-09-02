/*
    QUESTION    : Check if a string is a valid shuffle of two other distinct strings (Interleaving Strings)
    Company Tags: Amazon, Microsoft
    Link        : https://www.programiz.com/java-programming/examples/check-valid-shuffle-of-strings
    LeetCode    : https://leetcode.com/problems/interleaving-string/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - 2D Dynamic Programming validates interleaved ordering
// S.C : O(M)     - 1D space optimized DP row
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.length();
        int m = s2.length();

        if (n + m != s3.length()) return false;

        vector<bool> dp(m + 1, false);

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0) {
                    dp[j] = true;
                } else if (i == 0) {
                    dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);
                } else if (j == 0) {
                    dp[j] = dp[j] && (s1[i - 1] == s3[i - 1]);
                } else {
                    dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]) ||
                            (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
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
 * - `dp[i][j]` represents if `s3[0...i+j-1]` is valid interleave of `s1[0...i-1]` and `s2[0...j-1]`.
 * - `dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) || (dp[i][j-1] && s2[j-1] == s3[i+j-1])`.
 * - Time: O(N * M), Space: O(M).
 */
