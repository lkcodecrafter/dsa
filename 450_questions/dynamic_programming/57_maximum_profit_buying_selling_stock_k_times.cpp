/*
    QUESTION    : Maximum Profit (Buy and sell share at most K times)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximum-profit4657/1
    LeetCode    : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(K * N) - DP tracking maxDiff for each transaction
// S.C : O(K * N) - DP table
class Solution {
public:
    int maxProfit(int K, int N, int A[]) {
        if (N <= 1 || K == 0) return 0;

        // If K >= N / 2, unlimited transactions possible (Greedy valley-peak)
        if (K >= N / 2) {
            int maxProf = 0;
            for (int i = 1; i < N; i++) {
                if (A[i] > A[i - 1]) {
                    maxProf += A[i] - A[i - 1];
                }
            }
            return maxProf;
        }

        // dp[t][d] represents max profit up to day d with at most t transactions
        vector<vector<int>> dp(K + 1, vector<int>(N, 0));

        for (int t = 1; t <= K; t++) {
            int maxDiff = -A[0]; // Represents max(dp[t-1][x] - A[x])

            for (int d = 1; d < N; d++) {
                dp[t][d] = max(dp[t][d - 1], A[d] + maxDiff);
                maxDiff = max(maxDiff, dp[t - 1][d] - A[d]);
            }
        }

        return dp[K][N - 1];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[t][d] = max(dp[t][d-1], A[d] + maxDiff)`.
 * - `maxDiff = max(maxDiff, dp[t-1][d] - A[d])`.
 * - Time: O(K * N), Space: O(K * N).
 */
