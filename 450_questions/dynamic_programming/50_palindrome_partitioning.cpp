/*
    QUESTION    : Palindromic Partitioning (Minimum Cuts to partition string into palindromes)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/palindromic-patitioning4845/1
    LeetCode    : https://leetcode.com/problems/palindrome-partitioning-ii/
*/

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Precomputed palindrome table + 1D minimum cuts DP
// S.C : O(N^2) - Palindrome table and cuts array
class Solution {
public:
    int palindromicPartition(string str) {
        int n = str.length();

        // Step 1: Precompute palindrome lookup table
        vector<vector<bool>> isPalin(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++) isPalin[i][i] = true;

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (str[i] == str[j]) {
                    isPalin[i][j] = (len == 2) ? true : isPalin[i + 1][j - 1];
                }
            }
        }

        // Step 2: 1D DP for minimum cuts
        vector<int> dp(n, 0);

        for (int i = 0; i < n; i++) {
            if (isPalin[0][i]) {
                dp[i] = 0; // Entire prefix str[0...i] is already a palindrome!
            } else {
                dp[i] = INT_MAX;
                for (int j = 0; j < i; j++) {
                    if (isPalin[j + 1][i]) {
                        dp[i] = min(dp[i], 1 + dp[j]);
                    }
                }
            }
        }

        return dp[n - 1];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Precompute `isPalin[i][j]`.
 * - `dp[i] = min_{j < i}(1 + dp[j])` if `isPalin[j+1][i]`.
 * - Time: O(N^2), Space: O(N^2).
 */
