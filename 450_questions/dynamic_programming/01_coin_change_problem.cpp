/*
    QUESTION    : Coin Change (Count number of ways to make sum)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/coin-change2448/1
    LeetCode    : https://leetcode.com/problems/coin-change-ii/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * sum) - Unbounded Knapsack DP
// S.C : O(sum)     - 1D DP array
class Solution {
public:
    long long int count(int coins[], int N, int sum) {
        vector<long long int> dp(sum + 1, 0);
        dp[0] = 1; // 1 way to make sum 0 (empty selection)

        for (int i = 0; i < N; i++) {
            for (int j = coins[i]; j <= sum; j++) {
                dp[j] += dp[j - coins[i]];
            }
        }

        return dp[sum];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[0] = 1`.
 * - Outer loop over coins, inner loop `j` from `coin` to `sum`: `dp[j] += dp[j - coin]`.
 * - Time: O(N * sum), Space: O(sum).
 */
