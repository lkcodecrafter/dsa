#include<iostream>
#include<vector>
using namespace std;


// https://www.youtube.com/watch?v=XXaVIDIbUn4


class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0;
        // 
        for (; i < intervals.size(); i++) {
            if (intervals[i][1] < newInterval[0]) {
                result.push_back(intervals[i]);
            } else {
                break;
            }
        }

        // Now we are at the point where intervals[i] might overlap with newInterval
        for (; i < intervals.size(); i++) {

            if (intervals[i][0] <= newInterval[1]) {

                newInterval[0] = min(intervals[i][0], newInterval[0]); // example : if intervals[i][0] = 1 and newInterval[0] = 2 then we update newInterval[0] to 1 because they overlap and we need to merge them
                newInterval[1] = max(intervals[i][1], newInterval[1]); // example : if intervals[i][1] = 3 and newInterval[1] = 5 then we update newInterval[1] to 5 because they overlap and we need to merge them
                // we can do push back? but how newInterval[0] and newInterval[1] are working? because we are updating newInterval[0] and newInterval[1] in place and we are merging intervals as we go through the loop
                // we are not pushing back intervals[i] because they are overlapping with newInterval and we are merging them into newInterval, so we will push back newInterval at the end of this loop after we have merged all overlapping intervals
                // i'm confused with indexing 
                // new interval is [2,5] and intervals[i] is [1,3] then we will update newInterval to [1,5] because they overlap and we need to merge them
                // if intervals[i] is [6,9] then we will not update newInterval because they do not overlap and we will break out of the loop and push back newInterval as it is
            } else {
                break;
            }
        }

        result.push_back(newInterval);

        while (i < intervals.size()) {
            result.push_back(intervals[i]);
            i++;
        }

        return result;
    }
};


/*
Your thinking

You’re saying:

intervals = [[1,3],[6,9]]
newInterval = [2,5]

intervals[0][0] = 1
newInterval[0] = 2

1 < 2  → so we should add [1,3]


This feels correct, but it is actually not always safe.

The key rule (VERY IMPORTANT)

👉 You must compare the END of an interval, not the START

Why?

Because intervals can overlap even if the start is smaller.

Let’s see the mistake clearly
Case 1 (your example)
[1,3] and [2,5]


intervals[0][0] < newInterval[0] → 1 < 2 ✅

But they overlap (because 3 >= 2)

❌ We should NOT add [1,3] yet

✅ We must merge → [1,5]

Correct condition to safely add an interval
intervals[i][1] < newInterval[0]


This means:

“This interval ends before newInterval starts — no overlap possible.”

Example where it is safe:
[1,2] and [3,5]
2 < 3  ✅ → safe to add

Visual explanation
Overlap case
[1----3]
     [2------5]


Ends overlap → must merge

Non-overlap case
[1--2]   [3----5]


Ends before start → safe to add

Summary (remember this rule)
Condition	Meaning	Action
intervals[i][1] < newInterval[0]	Ends before	Add directly
intervals[i][0] <= newInterval[1]	Overlaps	Merge
intervals[i][0] > newInterval[1]	Starts after	Add later
One-line intuition (interview gold ⭐)

Start tells you order, END tells you overlap

If you want, I can:


*/