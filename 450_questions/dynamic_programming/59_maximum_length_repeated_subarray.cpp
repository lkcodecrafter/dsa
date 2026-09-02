/*
    QUESTION    : Maximum Length of Repeated Subarray (Longest Common Substring in Arrays)
    Company Tags: Amazon, Google
    LeetCode    : https://leetcode.com/problems/maximum-length-of-repeated-subarray/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - 1D Space Optimized DP (reversed inner traversal)
// S.C : O(M)     - 1D DP row
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        vector<int> dp(m + 1, 0);
        int maxLen = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[j] = 1 + dp[j - 1];
                    maxLen = max(maxLen, dp[j]);
                } else {
                    dp[j] = 0;
                }
            }
        }

        return maxLen;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Reversed inner loop `j` from `m` down to 1:
 * - `dp[j] = (nums1[i-1] == nums2[j-1]) ? 1 + dp[j-1] : 0`.
 * - Time: O(N * M), Space: O(M).
 */
