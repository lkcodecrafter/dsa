/*
    QUESTION    : Optimal Binary Search Tree (OBST / Minimum Search Cost BST)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/optimal-binary-search-tree2214/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^3) - Interval DP
// S.C : O(N^2) - DP table
class Solution {
private:
    int sumFreq(int freq[], int i, int j) {
        int s = 0;
        for (int k = i; k <= j; k++) s += freq[k];
        return s;
    }

public:
    int optimalSearchTree(int keys[], int freq[], int n) {
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            dp[i][i] = freq[i];
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                int fSum = sumFreq(freq, i, j);

                for (int r = i; r <= j; r++) {
                    int c = ((r > i) ? dp[i][r - 1] : 0) +
                            ((r < j) ? dp[r + 1][j] : 0) +
                            fSum;
                    dp[i][j] = min(dp[i][j], c);
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
 * - `dp[i][j] = sum(freq[i..j]) + min_r(dp[i][r-1] + dp[r+1][j])`.
 * - Time: O(N^3), Space: O(N^2).
 */
