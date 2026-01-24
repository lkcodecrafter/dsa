#include<iostream>
#include<queue>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left=0;
        int right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid]==target){
                return mid;
            }
            // left part is sorted
            if(nums[left]<=nums[mid]){ // example [4,5,6,7,0,1,2]
                // target is in left part
                // example target =0
                // nums[left]=4, nums[mid]=7
                // 0>=4 && 0<7 false
                // example target =5
                // 5>=4 && 5<7 true
                // so we move right to mid-1
                // else we move left to mid+1
                // right is now mid-1
                if(target>=nums[left] && target < nums [mid]){
                    right = mid -1;
                }else{
                    left = mid +1;
                }
            }else{ // right part is sorted
                if(target>nums[mid] && target <= nums[right]){
                    left = mid +1;
                }else{
                    right = mid -1;
                }
            }
        }
        return -1;
    }
};


/*

User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily. also why taken min and max variable?

GitHub Copilot: I'll read the code file and help you understand it with a detailed explanation and visualization. 

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week4/33.%20Search%20in%20Rotated%20Sorted%20Array.cpp)

Perfect! Let me explain this code with a detailed visualization and dry run.

## **Code Overview: Search in Rotated Sorted Array**

This code searches for a target value in a **rotated sorted array** using **Binary Search**. A rotated sorted array is when a sorted array is rotated at a pivot point.

### **Why use `min` (left) and `max` (right)?**

The variables `left` and `right` define the **search boundary**:
- `left`: points to the start of the search range
- `right`: points to the end of the search range

This is the standard binary search technique to narrow down the search space.

---

## **Algorithm Explanation**

### **Key Insight:**
Even in a rotated sorted array, **at least one half (left or right of mid) is always sorted**. We use this property to determine which direction to search.

---

## **Visual Representation with Example**

```
Original Sorted Array: [1, 2, 3, 4, 5, 6, 7, 0]
                                        ↑ Rotation Point

Array Index:    0  1  2  3  4  5  6  7
Array Values: [4, 5, 6, 7, 0, 1, 2]
               ↑                       ↑
             left                    right

Target = 0
```

---

## **Dry Run: Finding target = 0 in [4, 5, 6, 7, 0, 1, 2]**

```
┌─────────────────────────────────────────────────────────────┐
│ ITERATION 1                                                 │
├─────────────────────────────────────────────────────────────┤
│ left = 0, right = 6                                         │
│ mid = 0 + (6-0)/2 = 3                                       │
│ nums[mid] = nums[3] = 7                                     │
│ 7 ≠ 0, continue...                                          │
│                                                              │
│ Check if LEFT PART is sorted:                               │
│ nums[left]=4, nums[mid]=7  →  4 ≤ 7? YES ✓                 │
│ → Left part [4,5,6,7] is sorted                             │
│                                                              │
│ Is target in left part?                                     │
│ 0 ≥ 4 && 0 < 7?  →  NO ✗                                    │
│ → Target must be in RIGHT part                              │
│ → left = mid + 1 = 4                                        │
│                                                              │
│ Array: [4, 5, 6, 7, | 0, 1, 2]                             │
│                      ↑ new left                             │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│ ITERATION 2                                                 │
├─────────────────────────────────────────────────────────────┤
│ left = 4, right = 6                                         │
│ mid = 4 + (6-4)/2 = 5                                       │
│ nums[mid] = nums[5] = 1                                     │
│ 1 ≠ 0, continue...                                          │
│                                                              │
│ Check if LEFT PART is sorted:                               │
│ nums[left]=0, nums[mid]=1  →  0 ≤ 1? YES ✓                 │
│ → Left part [0,1] is sorted                                 │
│                                                              │
│ Is target in left part?                                     │
│ 0 ≥ 0 && 0 < 1?  →  YES ✓                                   │
│ → Target is in LEFT part                                    │
│ → right = mid - 1 = 4                                       │
│                                                              │
│ Array: [4, 5, 6, 7, | 0 |, 1, 2]                           │
│                      ↑     ↑                                │
│                     left  right                             │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│ ITERATION 3                                                 │
├─────────────────────────────────────────────────────────────┤
│ left = 4, right = 4                                         │
│ mid = 4 + (4-4)/2 = 4                                       │
│ nums[mid] = nums[4] = 0                                     │
│ 0 == 0? YES ✓  FOUND!                                       │
│ return 4                                                    │
└─────────────────────────────────────────────────────────────┘
```

---

## **Step-by-Step Logic Diagram**

```
                    [4, 5, 6, 7, 0, 1, 2]
                                |
                    ┌───────────┼───────────┐
                    │           │           │
              Check which half  Mid = 7   
              is sorted?        
              
        ┌─────────────┐      ┌─────────────┐
        │ LEFT SORTED │      │ RIGHT SORTED│
        │[4,5,6,7]   │      │[0,1,2]     │
        └─────────────┘      └─────────────┘
              │                    │
      Is target in    Is target in
      left? (4≤0<7)   right? (0<0≤2)
         NO ✗              YES ✓
         Search           Search
         Right            Left
```

---

## **Why min/max (left/right)?**

| Variable | Purpose | Meaning |
|----------|---------|---------|
| **left** | Search boundary (minimum index) | Start of current search range |
| **right** | Search boundary (maximum index) | End of current search range |

**They work together to:**
1. Define the search space
2. Calculate `mid` point
3. Narrow down the range based on where target might be

---

## **Time Complexity**
- **O(log n)** - Binary search, cutting search space in half each iteration
- **Space Complexity: O(1)** - Only using few variables

This is much faster than linear search O(n)!

*/