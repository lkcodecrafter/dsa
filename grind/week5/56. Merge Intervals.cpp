#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        if(intervals.size()==0){
            return result;
        }
        sort(intervals.begin(), intervals.end());
        vector<int> temp = intervals[0];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <=temp[1]) {
                temp[1] = max(temp[1], intervals[i][1]);
            } else {
                result.push_back(temp);
                temp = intervals[i];
            }
        }
        result.push_back(temp);
        return result;
    }
};

/*

User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily. also why taken min and max variable?

GitHub Copilot: I'll read the file and analyze it for you. 

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week5/56.%20Merge%20Intervals.cpp)

Perfect! Let me explain this **Merge Intervals** code with a detailed visualization and dry run.

## Code Explanation

This code merges overlapping intervals. Here's how it works:

### Algorithm Steps:
1. **Sort** intervals by their starting point
2. **Iterate** through sorted intervals
3. **Check overlap**: If current interval's start ≤ previous interval's end, they overlap
4. **Merge**: Extend the end of the current interval to include both
5. **No overlap**: Add the previous interval to result and start a new one

---

## Why `min` and `max` Variables?

Actually, the code **only uses `max()`**, not both. Here's why:

- **`max(intervals[i][1], temp[1])`** → When intervals overlap, we take the **maximum end value** 
to ensure we capture the entire merged range
- We don't need `min` because after sorting, the **starting point is already the minimum**
(the smaller start is in `temp[0]`)

---

## Dry Run with Visualization

### Example: `intervals = [[1,3],[2,6],[8,10],[15,18]]`

```
Step 0: Sort intervals (already sorted)
[[1,3],[2,6],[8,10],[15,18]]

Step 1: temp = [1,3]
────────────────────────────────────

Step 2: i=1, intervals[1] = [2,6]
Check: 2 <= 3? YES (overlap!)
┌─────────────────────┐
│  [1,3]              │
│    [2,6]            │
├─────────────────────┤
│    [1,6]  (merged)  │
└─────────────────────┘
temp = [1, max(6,3)] = [1,6]

Step 3: i=2, intervals[2] = [8,10]
Check: 8 <= 6? NO (no overlap)
┌─────┐
│[1,6]│        ┌───────┐
│     │        │[8,10] │
└─────┘        └───────┘
Push [1,6] to result
temp = [8,10]

Step 4: i=3, intervals[3] = [15,18]
Check: 15 <= 10? NO (no overlap)
┌───────┐
│[8,10] │              ┌────────┐
│       │              │[15,18] │
└───────┘              └────────┘
Push [8,10] to result
temp = [15,18]

Step 5: End of loop
Push [15,18] to result

Final Result: [[1,6],[8,10],[15,18]]
```

---

## Why `max()` is Essential

| Scenario | Example | Without max | With max |
|----------|---------|------------|----------|
| Normal overlap | [1,3] + [2,6] | Would get [1,3] ❌ | Gets [1,6] ✓ |
| Contained | [1,5] + [2,3] | Would get [1,3] ❌ | Gets [1,5] ✓ |
| Extended | [1,3] + [2,8] | Would get [1,2] ❌ | Gets [1,8] ✓ |

The `max()` ensures we capture the furthest end point when intervals overlap!

*/