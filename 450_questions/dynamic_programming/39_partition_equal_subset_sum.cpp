/*
    QUESTION    : Partition Equal Subset Sum
    Company Tags: Amazon, Microsoft, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/subset-sum-problem2014/1
    LeetCode    : https://leetcode.com/problems/partition-equal-subset-sum/
*/

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * (sum / 2)) - 0-1 Knapsack Subset Sum DP
// S.C : O(sum / 2)       - 1D boolean DP array
class Solution {
public:
    int equalPartition(int N, int arr[]) {
        int totalSum = 0;
        for (int i = 0; i < N; i++) totalSum += arr[i];

        // Odd sum cannot be partitioned into two equal integer subsets
        if (totalSum % 2 != 0) return 0;

        int target = totalSum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int i = 0; i < N; i++) {
            for (int j = target; j >= arr[i]; j--) {
                dp[j] = dp[j] || dp[j - arr[i]];
            }
        }

        return dp[target] ? 1 : 0;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `totalSum % 2 != 0` return 0.
 * - Run 0-1 Subset Sum for `target = totalSum / 2`.
 * - Time: O(N * sum), Space: O(sum).
 */
