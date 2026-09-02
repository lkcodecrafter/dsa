/*
    QUESTION    : Count all subsequences having product less than K
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/count-subsequences-product-less-k/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * K) - 2D Dynamic Programming (include/exclude product)
// S.C : O(N * K) - DP table
class Solution {
public:
    int countSubsequences(vector<int>& arr, int n, int k) {
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                // 1. Exclude arr[j - 1]
                dp[i][j] = dp[i][j - 1];

                // 2. Include arr[j - 1]
                if (arr[j - 1] <= i && arr[j - 1] > 0) {
                    dp[i][j] += (dp[i / arr[j - 1]][j - 1] + 1);
                }
            }
        }

        return dp[k][n];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i][j] = dp[i][j - 1] + (arr[j - 1] <= i ? dp[i / arr[j - 1]][j - 1] + 1 : 0)`.
 * - Time: O(N * K), Space: O(N * K).
 */
