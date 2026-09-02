/*
    QUESTION    : Minimum cost to fill given weight in a bag (Unbounded Knapsack)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-cost-to-fill-given-weight-in-a-bag1956/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * W) - Unbounded Knapsack DP
// S.C : O(W)     - 1D DP array
class Solution {
public:
    int minimumCost(int cost[], int N, int W) {
        vector<int> dp(W + 1, 1e9);
        dp[0] = 0;

        for (int i = 0; i < N; i++) {
            int packetWeight = i + 1;
            int packetCost = cost[i];

            if (packetCost != -1) {
                for (int w = packetWeight; w <= W; w++) {
                    if (dp[w - packetWeight] != 1e9) {
                        dp[w] = min(dp[w], packetCost + dp[w - packetWeight]);
                    }
                }
            }
        }

        return (dp[W] == 1e9) ? -1 : dp[W];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[w] = min(dp[w], cost[i] + dp[w - (i + 1)])` when `cost[i] != -1`.
 * - Time: O(N * W), Space: O(W).
 */
