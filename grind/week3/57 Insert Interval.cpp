#include<iostream>
#include<vector>
using namespace std;


// https://www.youtube.com/watch?v=XXaVIDIbUn4

// leetcode 57. Insert Interval
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0;
        // Add all intervals that come before newInterval and do not overlap with it
        for (; i < intervals.size(); i++) {
            if (intervals[i][1] < newInterval[0]) { // interval[i][1] value is = 3, newInterval[0] value is = 2, so 3 < 2 is false, so we will not add [1,3] to result
                // than break the loop.
                result.push_back(intervals[i]);
            } else {
                break;
            }
        }

        // Now we are at the point where intervals[i] might overlap with newInterval
        for (; i < intervals.size(); i++) {

            if (intervals[i][0] <= newInterval[1]) { // interval[i][0] value is = 6, newInterval[1] value is = 5, so 6 <= 5 is false, so we will not merge [6,9] with [2,5], so we will break the loop. 

                newInterval[0] = min(intervals[i][0], newInterval[0]);
                newInterval[1] = max(intervals[i][1], newInterval[1]);
            } else {
                break;
            }
        }

        result.push_back(newInterval); // we will add [1,5] to result // how? because we have merged [1,3] and [2,5] to get [1,5]
        //give dry run of the code to understand how we get [1,5]
        // Now we are at the point where intervals[i] starts after newInterval ends, so we can add the remaining intervals to result
        // Add the remaining intervals that come after newInterval
        // i is currently at the index of the first interval that starts after newInterval ends, so we will add all intervals from index i to the end of the intervals vector to result
        // for example, if intervals = [[1,3],[6,9]] and newInterval = [2,5], after the first loop, i will be at index 1 (pointing to [6,9]), so we will add [6,9] to result
        // if intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]] and newInterval = [4,8], after the first loop, i will be at index 2 (pointing to [6,7]), so we will add [6,7], [8,10], and [12,16] to result
        // if intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]] and newInterval = [4,8], after the second loop, i will be at index 4 (pointing to [12,16]), so we will add [12,16] to result

        while (i < intervals.size())
        {

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

please give dry run : 
intervals = [[1,3],[6,9]]
newInterval = [2,5]
Sure! Let's do a dry run of the code with the input:
intervals = [[1,3],[6,9]]
newInterval = [2,5]
1. We initialize an empty result vector and set i = 0.
2. We enter the first loop to add intervals that come before newInterval and do not overlap with it.
   - For i = 0, we check if intervals[0][1] < newInterval[0], which is 3 < 2. This condition is false, so we break out of the loop. The result vector is still empty at this point.     
3. Now we are at the point where intervals[i] might overlap with newInterval. We enter the second loop.
   - For i = 0, we check if intervals[0][0] <= newInterval[1], which is 1 <= 5. This condition is true, so we merge the intervals.
     - We update newInterval[0] to min(intervals[0][0], newInterval[0]), which is min(1, 2) = 1.
     - We update newInterval[1] to max(intervals[0][1], newInterval[1]), which is max(3, 5) = 5.
     - Now newInterval is updated to [1,5]. 
    - We increment i to 1 and check the condition again for i = 1.
    - For i = 1, we check if intervals[1][0] <= newInterval[1], which is 6 <= 5. This condition is false, so we break out of the loop.
4. We add the merged newInterval [1,5] to the result vector. Now result = [[1,5]].
5. We enter the third loop to add the remaining intervals that come after newInterval.
   - For i = 1, we add intervals[1] which is [6,9] to the result vector. Now result = [[1,5],[6,9]].
   - We increment i to 2, which is equal to the size of intervals, so we exit the loop.
6. Finally, we return the result vector, which is [[1,5],[6,9]].


*/