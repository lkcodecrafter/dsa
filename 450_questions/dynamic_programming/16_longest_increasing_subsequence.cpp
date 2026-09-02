/*
    QUESTION    : Longest Increasing Subsequence (Patience Sorting / Binary Search)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence-1587115620/1
    LeetCode    : https://leetcode.com/problems/longest-increasing-subsequence/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Binary search with lower_bound (Patience Sorting)
// S.C : O(N)       - Tails vector
class Solution {
public:
    int longestSubsequence(int n, int a[]) {
        vector<int> tails;

        for (int i = 0; i < n; i++) {
            auto it = lower_bound(tails.begin(), tails.end(), a[i]);

            if (it == tails.end()) {
                tails.push_back(a[i]); // Extend LIS
            } else {
                *it = a[i];            // Replace to maintain smallest possible tail value
            }
        }

        return tails.size();
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `tails` vector.
 * - `it = lower_bound(tails.begin(), tails.end(), a[i])`.
 * - If `it == tails.end()` `tails.push_back(a[i]);` else `*it = a[i];`.
 * - Time: O(N log N), Space: O(N).
 */
