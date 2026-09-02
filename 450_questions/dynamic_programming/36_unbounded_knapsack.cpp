/*
    QUESTION    : Knapsack with Duplicate Items (Unbounded Knapsack)
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * W) - Forward traversal 1D DP allows repeated item inclusion
// S.C : O(W)     - 1D DP array
class Solution {
public:
    int knapSack(int N, int W, int val[], int wt[]) {
        vector<int> dp(W + 1, 0);

        for (int i = 0; i < N; i++) {
            for (int w = wt[i]; w <= W; w++) {
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
 * - `for i: for w from wt[i] to W: dp[w] = max(dp[w], val[i] + dp[w - wt[i]])`.
 * - Time: O(N * W), Space: O(W).
 */
