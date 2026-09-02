/*
    QUESTION    : Subset Sum Problem
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * sum) - 0-1 Knapsack Boolean DP
// S.C : O(sum)     - 1D boolean array (reverse traversal)
class Solution {
public:
    bool isSubsetSum(vector<int> arr, int sum) {
        int n = arr.size();
        vector<bool> dp(sum + 1, false);
        dp[0] = true; // Sum 0 is always achievable

        for (int i = 0; i < n; i++) {
            for (int j = sum; j >= arr[i]; j--) {
                dp[j] = dp[j] || dp[j - arr[i]];
            }
        }

        return dp[sum];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[0] = true`.
 * - `for i: for j from sum down to arr[i]: dp[j] = dp[j] || dp[j - arr[i]]`.
 * - Time: O(N * sum), Space: O(sum).
 */
