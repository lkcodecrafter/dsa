/*
    QUESTION    : Matrix Chain Multiplication (MCM)
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^3) - Classic MCM Interval DP
// S.C : O(N^2) - DP table
class Solution {
public:
    int matrixMultiplication(int N, int arr[]) {
        vector<vector<int>> dp(N, vector<int>(N, 0));

        // len is chain length (from 2 matrices up to N-1 matrices)
        for (int len = 2; len < N; len++) {
            for (int i = 1; i < N - len + 1; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;

                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }

        return dp[1][N - 1];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i][j] = min(dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j])` for $k \in [i, j-1]$.
 * - Time: O(N^3), Space: O(N^2).
 */
