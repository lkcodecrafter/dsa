/*
    QUESTION    : Largest square sub-matrix with all 1s (Maximal Square)
    Company Tags: Amazon, Microsoft, Google, Adobe, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/largest-square-sub-matrix-with-all-1s1453/1
    LeetCode    : https://leetcode.com/problems/maximal-square/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - 2D Dynamic Programming
// S.C : O(N * M) - DP matrix
class Solution {
public:
    int maxSquare(int n, int m, vector<vector<int>> mat) {
        vector<vector<int>> dp(n, vector<int>(m, 0));
        int maxSide = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || j == 0) {
                    dp[i][j] = mat[i][j];
                } else if (mat[i][j] == 1) {
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
                maxSide = max(maxSide, dp[i][j]);
            }
        }

        return maxSide;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]})` when `mat[i][j] == 1`.
 * - Time: O(N * M), Space: O(N * M).
 */
