/*
    QUESTION    : Egg Dropping Puzzle
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/egg-dropping-puzzle-1587115620/1
    LeetCode    : https://leetcode.com/problems/super-egg-drop/
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(K * N^2) or O(K * N log N) using binary search
// S.C : O(K * N) - DP table
class Solution {
public:
    int eggDrop(int n, int k) {
        // dp[e][f] represents min attempts with e eggs and f floors
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        // Base cases
        for (int i = 1; i <= n; i++) {
            dp[i][0] = 0; // 0 floors -> 0 attempts
            dp[i][1] = 1; // 1 floor -> 1 attempt
        }
        for (int j = 1; j <= k; j++) {
            dp[1][j] = j; // 1 egg -> j attempts (linear trial from floor 1 to j)
        }

        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= k; j++) {
                dp[i][j] = INT_MAX;

                for (int x = 1; x <= j; x++) {
                    // Egg breaks (dp[i-1][x-1]) OR egg survives (dp[i][j-x])
                    int res = 1 + max(dp[i - 1][x - 1], dp[i][j - x]);
                    dp[i][j] = min(dp[i][j], res);
                }
            }
        }

        return dp[n][k];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[e][f] = 1 + min_x(max(dp[e-1][x-1], dp[e][f-x]))` for floor $x \in [1, f]$.
 * - Time: O(K * N^2), Space: O(K * N).
 */
