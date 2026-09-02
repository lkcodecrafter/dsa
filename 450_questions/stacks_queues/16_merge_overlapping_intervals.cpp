/*
    QUESTION    : Merge Overlapping Intervals
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/overlapping-intervals/0
    LeetCode    : https://leetcode.com/problems/merge-intervals/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting intervals by start time + linear merge
// S.C : O(1)       - In-place merged vector
class Solution {
public:
    vector<vector<int>> overlappedInterval(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        // Step 1: Sort intervals primarily by start time
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged;
        merged.push_back(intervals[0]);

        // Step 2: Merge overlapping intervals
        for (int i = 1; i < intervals.size(); i++) {
            // Check if current interval overlaps with last merged interval
            if (intervals[i][0] <= merged.back()[1]) {
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                merged.push_back(intervals[i]);
            }
        }

        return merged;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(intervals.begin(), intervals.end())`.
 * - If `intervals[i][0] <= merged.back()[1]`: `merged.back()[1] = max(merged.back()[1], intervals[i][1])`.
 * - Else `merged.push_back(intervals[i])`.
 * - Time: O(N log N), Space: O(1).
 */
