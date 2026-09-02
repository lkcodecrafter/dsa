/*
    QUESTION    : Maximum sum of two non-overlapping intervals (Maximum Subarray Sum of Two Non-Overlapping Subarrays)
    Company Tags: Amazon, Google
    LeetCode    : https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Prefix sum + running maximum of fixed-size sliding window
// S.C : O(N) - Prefix sum array
class Solution {
private:
    int maxSum(const vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        vector<int> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        int maxL = 0;
        int maxTotal = 0;

        for (int i = firstLen + secondLen; i <= n; i++) {
            // Maximum sum of subarray of length firstLen before index (i - secondLen)
            maxL = max(maxL, prefix[i - secondLen] - prefix[i - secondLen - firstLen]);

            // Current subarray of length secondLen
            int currentM = prefix[i] - prefix[i - secondLen];

            maxTotal = max(maxTotal, maxL + currentM);
        }

        return maxTotal;
    }

public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        // Consider both orderings: (firstLen before secondLen) AND (secondLen before firstLen)
        return max(maxSum(nums, firstLen, secondLen), maxSum(nums, secondLen, firstLen));
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `maxL = max(maxL, prefix[i-M] - prefix[i-M-L])`.
 * - `maxTotal = max(maxTotal, maxL + (prefix[i] - prefix[i-M]))`.
 * - Check both orderings: `L` before `M` and `M` before `L`.
 * - Time: O(N), Space: O(N).
 */
