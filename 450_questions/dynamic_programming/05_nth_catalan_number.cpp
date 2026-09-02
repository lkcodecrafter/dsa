/*
    QUESTION    : Nth Catalan Number (C_n = sum(C_i * C_{n-1-i}))
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/nth-catalan-number0817/1
    LeetCode    : https://leetcode.com/problems/unique-binary-search-trees/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Dynamic programming Catalan convolution
// S.C : O(N)   - DP array
class Solution {
public:
    int findCatalan(int n) {
        long long MOD = 1000000007;
        vector<long long> dp(n + 1, 0);

        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                dp[i] = (dp[i] + (dp[j] * dp[i - 1 - j]) % MOD) % MOD;
            }
        }

        return dp[n];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[0] = dp[1] = 1`.
 * - `dp[i] += (dp[j] * dp[i - 1 - j]) % MOD`.
 * - Time: O(N^2), Space: O(N).
 */
