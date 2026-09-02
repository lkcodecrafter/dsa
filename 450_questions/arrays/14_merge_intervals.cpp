/*
 * QUESTION: Merge Intervals
 * Link: https://leetcode.com/problems/merge-intervals/
 * 
 * Input: intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}}
 * Output: {{1, 6}, {8, 10}, {15, 18}}
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Merges all overlapping intervals.
std::vector<std::vector<int>> mergeIntervals(std::vector<std::vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    // Step 1: Sort intervals based on start value
    std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[0] < b[0];
    });
    
    std::vector<std::vector<int>> merged;
    merged.push_back(intervals[0]);
    
    // Step 2: Iterate and merge
    for (size_t i = 1; i < intervals.size(); i++) {
        std::vector<int>& last = merged.back();
        const std::vector<int>& current = intervals[i];
        
        // If current interval overlaps with the last merged interval
        if (current[0] <= last[1]) {
            last[1] = std::max(last[1], current[1]); // Merge them
        } else {
            merged.push_back(current); // No overlap, add as new interval
        }
    }
    
    return merged;
}

/*
 * VISUALIZATION:
 * Timeline:  1   2   3   4   5   6   7   8   9   10  11  ...  15  16  17  18
 * Interval 1:[=======] (1,3)
 * Interval 2:    [===============] (2,6)
 * Merged 1&2:[==================] (1,6)
 * 
 * Interval 3:                        [=======] (8,10)
 * Interval 4:                                                 [=======] (15,18)
 * 
 * DRY RUN (intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}}):
 * Sorted: {{1, 3}, {2, 6}, {8, 10}, {15, 18}}
 * merged = {{1, 3}}
 * 
 * | Step | i | Current Interval | Last Merged in Result | Overlap Condition | Action                        | Result State                  |
 * | :--- | :-| :--------------- | :-------------------- | :---------------- | :---------------------------- | :---------------------------- |
 * | 1    | 1 | {2, 6}           | {1, 3}                | 2 <= 3 (Yes)      | Merge: update last[1]=max(3,6)| {{1, 6}}                       |
 * | 2    | 2 | {8, 10}          | {1, 6}                | 8 <= 6 (No)       | Push {8, 10}                  | {{1, 6}, {8, 10}}             |
 * | 3    | 3 | {15, 18}         | {8, 10}               | 15 <= 10 (No)     | Push {15, 18}                 | {{1, 6}, {8, 10}, {15, 18}}   |
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Think of booking a meeting room. 
 * First, sort the bookings by start time. 
 * If a booking starts before the previous one ends, they overlap, so you must extend the meeting duration (merge). 
 * Otherwise, it's a separate meeting.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Sort intervals by their start value: `std::sort(..., [](a, b){ return a[0] < b[0]; })`.
 * - Push the first interval to the `merged` result vector.
 * - Iterate from the second interval. Let `last` be the last interval in `merged`.
 * - If `current[0] <= last[1]`, set `last[1] = max(last[1], current[1])`.
 * - Else, push `current` to `merged`.
 * - Time Complexity: O(N log N) (due to sorting)
 * - Space Complexity: O(N) to return the result, O(1) auxiliary space (excluding result).
 */
