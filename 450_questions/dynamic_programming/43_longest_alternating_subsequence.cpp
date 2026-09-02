/*
    QUESTION    : Longest alternating subsequence (Wiggle Subsequence)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-alternating-subsequence5951/1
    LeetCode    : https://leetcode.com/problems/wiggle-subsequence/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear tracking of up and down alternating trends
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int AlternatingaMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return n;

        int up = 1;
        int down = 1;

        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) {
                up = down + 1;
            } else if (nums[i] < nums[i - 1]) {
                down = up + 1;
            }
        }

        return max(up, down);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `if (nums[i] > nums[i-1]) up = down + 1;`
 * - `else if (nums[i] < nums[i-1]) down = up + 1;`
 * - Return `max(up, down)`.
 * - Time: O(N), Space: O(1).
 */
