/*
    QUESTION    : Gold Mine Problem (Maximum gold collected moving right, right-up, right-down)
    Company Tags: Amazon, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/gold-mine-problem2608/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - Column-by-column DP from right to left
// S.C : O(N)     - 1D column storage
class Solution {
public:
    int maxGold(int n, int m, vector<vector<int>> M) {
        vector<vector<int>> dp = M;

        // Process columns from second-to-last to first
        for (int col = m - 2; col >= 0; col--) {
            for (int row = 0; row < n; row++) {
                // Right
                int right = dp[row][col + 1];

                // Right up
                int rightUp = (row > 0) ? dp[row - 1][col + 1] : 0;

                // Right down
                int rightDown = (row < n - 1) ? dp[row + 1][col + 1] : 0;

                dp[row][col] += max({right, rightUp, rightDown});
            }
        }

        // Maximum gold collected starting from any row in the first column
        int maxGoldCollected = 0;
        for (int row = 0; row < n; row++) {
            maxGoldCollected = max(maxGoldCollected, dp[row][0]);
        }

        return maxGoldCollected;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[row][col] += max({right, rightUp, rightDown})`.
 * - Return `max_element` in column 0.
 * - Time: O(N * M), Space: O(N * M).
 */
