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
        for (; i < intervals.size(); i++) {
            if (intervals[i][1] < newInterval[0]) {
                result.push_back(intervals[i]);
            } else {
                break;
            }
        }

        for (; i < intervals.size(); i++) {

            if (intervals[i][0] <= newInterval[1]) {

                newInterval[0] = min(intervals[i][0], newInterval[0]);
                newInterval[1] = max(intervals[i][1], newInterval[1]);

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