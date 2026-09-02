/*
    QUESTION    : 0 - 1 Knapsack Problem
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem0929/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * W) - 0-1 Knapsack DP
// S.C : O(W)     - Space optimized 1D DP (reversed traversal)
class Solution {
public:
    int knapSack(int W, int wt[], int val[], int n) {
        vector<int> dp(W + 1, 0);

        for (int i = 0; i < n; i++) {
            // Traverse capacity backwards to ensure each item is used at most once
            for (int w = W; w >= wt[i]; w--) {
                dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
            }
        }

        return dp[W];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `for i: for w from W down to wt[i]:`
 * - `dp[w] = max(dp[w], val[i] + dp[w - wt[i]])`.
 * - Time: O(N * W), Space: O(W).
 */
