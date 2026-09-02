/*
    QUESTION    : Maximum sum increasing subsequence
    Company Tags: Amazon, Microsoft, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximum-sum-increasing-subsequence4749/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Dynamic programming storing max increasing sum ending at each index
// S.C : O(N)   - DP array
class Solution {
public:
    int maxSumIS(int arr[], int n) {
        vector<int> dp(arr, arr + n);
        int maxIS = dp[0];

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) {
                    dp[i] = max(dp[i], dp[j] + arr[i]);
                }
            }
            maxIS = max(maxIS, dp[i]);
        }

        return maxIS;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i] = arr[i]`.
 * - For `j < i`: if `arr[j] < arr[i]`: `dp[i] = max(dp[i], dp[j] + arr[i])`.
 * - Time: O(N^2), Space: O(N).
 */
