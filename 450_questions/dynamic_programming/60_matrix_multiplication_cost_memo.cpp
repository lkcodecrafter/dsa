/*
    QUESTION    : Matrix Chain Multiplication (Memoized Top-Down DP)
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^3) - Top-down memoized Matrix Chain Multiplication
// S.C : O(N^2) - Memoization table + recursion call stack
class Solution {
private:
    int solve(int i, int j, int arr[], vector<vector<int>>& dp) {
        // Base case: single matrix has 0 multiplication cost
        if (i == j) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        int minCost = INT_MAX;

        for (int k = i; k < j; k++) {
            int cost = solve(i, k, arr, dp) +
                       solve(k + 1, j, arr, dp) +
                       arr[i - 1] * arr[k] * arr[j];

            minCost = min(minCost, cost);
        }

        return dp[i][j] = minCost;
    }

public:
    int matrixMultiplication(int N, int arr[]) {
        vector<vector<int>> dp(N, vector<int>(N, -1));
        return solve(1, N - 1, arr, dp);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `solve(i, j) = min_{k}(solve(i, k) + solve(k+1, j) + arr[i-1]*arr[k]*arr[j])`.
 * - Base: `i == j` return 0.
 * - Time: O(N^3), Space: O(N^2).
 */
