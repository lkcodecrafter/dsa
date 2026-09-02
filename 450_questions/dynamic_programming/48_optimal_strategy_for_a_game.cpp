/*
    QUESTION    : Optimal Strategy For A Game (Minimax Game Theory DP)
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/optimal-strategy-for-a-game-1587115620/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Interval Minimax DP
// S.C : O(N^2) - DP table
class Solution {
public:
    long long maximumAmount(int n, int arr[]) {
        vector<vector<long long>> dp(n, vector<long long>(n, 0));

        // Subarray length len from 1 to n
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;

                if (i == j) {
                    dp[i][j] = arr[i];
                } else if (j == i + 1) {
                    dp[i][j] = max(arr[i], arr[j]);
                } else {
                    // Pick arr[i] -> opponent leaves min(dp[i+2][j], dp[i+1][j-1])
                    long long pickLeft = arr[i] + min(dp[i + 2][j], dp[i + 1][j - 1]);

                    // Pick arr[j] -> opponent leaves min(dp[i+1][j-1], dp[i][j-2])
                    long long pickRight = arr[j] + min(dp[i + 1][j - 1], dp[i][j - 2]);

                    dp[i][j] = max(pickLeft, pickRight);
                }
            }
        }

        return dp[0][n - 1];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i][j] = max(arr[i] + min(dp[i+2][j], dp[i+1][j-1]), arr[j] + min(dp[i+1][j-1], dp[i][j-2]))`.
 * - Time: O(N^2), Space: O(N^2).
 */
