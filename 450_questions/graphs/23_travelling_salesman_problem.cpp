/*
    QUESTION    : Travelling Salesman Problem (TSP using DP + Bitmasking / Held-Karp Algorithm)
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/travelling-salesman-problem2743/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(2^N * N^2) - Held-Karp Bitmask DP
// S.C : O(2^N * N)   - Memoization table
class Solution {
private:
    int tsp(int mask, int u, int n, const vector<vector<int>>& cost, vector<vector<int>>& dp) {
        // Base case: All cities visited (mask = (1 << n) - 1) -> return cost to return to starting city 0
        if (mask == (1 << n) - 1) {
            return cost[u][0];
        }

        if (dp[mask][u] != -1) {
            return dp[mask][u];
        }

        int ans = INT_MAX;

        // Try visiting every unvisited city v
        for (int v = 0; v < n; v++) {
            if (!(mask & (1 << v))) {
                int nextCost = cost[u][v] + tsp(mask | (1 << v), v, n, cost, dp);
                ans = min(ans, nextCost);
            }
        }

        return dp[mask][u] = ans;
    }

public:
    int total_cost(vector<vector<int>> cost) {
        int n = cost.size();
        vector<vector<int>> dp(1 << n, vector<int>(n, -1));

        // Start at city 0 with mask = 1 (city 0 visited)
        return tsp(1, 0, n, cost, dp);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - State: `dp[mask][u]` = min cost from city `u` having visited set `mask`.
 * - Transition: `min(cost[u][v] + tsp(mask | (1 << v), v))`.
 * - Base: `mask == (1<<n) - 1 ? cost[u][0] : ...`
 * - Time: O(2^N * N^2), Space: O(2^N * N).
 */
