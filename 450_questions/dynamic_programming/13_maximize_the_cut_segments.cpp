/*
    QUESTION    : Maximize The Cut Segments (Rod cutting into lengths x, y, z)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/cutted-segments1641/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - 1D Unbounded Knapsack DP
// S.C : O(N) - DP array
class Solution {
public:
    int maximizeTheCuts(int n, int x, int y, int z) {
        vector<int> dp(n + 1, -1);
        dp[0] = 0; // 0 length requires 0 cuts

        for (int i = 1; i <= n; i++) {
            if (i >= x && dp[i - x] != -1) dp[i] = max(dp[i], dp[i - x] + 1);
            if (i >= y && dp[i - y] != -1) dp[i] = max(dp[i], dp[i - y] + 1);
            if (i >= z && dp[i - z] != -1) dp[i] = max(dp[i], dp[i - z] + 1);
        }

        return (dp[n] == -1) ? 0 : dp[n];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i] = 1 + max(dp[i-x], dp[i-y], dp[i-z])`.
 * - Return `max(0, dp[n])`.
 * - Time: O(N), Space: O(N).
 */
