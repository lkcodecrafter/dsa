/*
    QUESTION    : Count Palindromic Subsequences
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/count-palindromic-subsequences/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Interval DP with Inclusion-Exclusion principle
// S.C : O(N^2) - DP table
class Solution {
public:
    long long int countPS(string str) {
        int n = str.length();
        long long MOD = 1000000007;

        vector<vector<long long>> dp(n, vector<long long>(n, 0));

        // Base case: single letters are palindromes of length 1
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }

        // Substring length len from 2 to n
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;

                if (str[i] == str[j]) {
                    dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] + 1) % MOD;
                } else {
                    dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + MOD) % MOD;
                }
            }
        }

        return dp[0][n - 1];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `str[i] == str[j]`: `dp[i][j] = (dp[i+1][j] + dp[i][j-1] + 1) % MOD`.
 * - Else: `dp[i][j] = (dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1] + MOD) % MOD`.
 * - Time: O(N^2), Space: O(N^2).
 */
