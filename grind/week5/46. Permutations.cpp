#include<iostream>
#include<unordered_set>
#include<vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> result;
    int n;
    unordered_set<int> mp;
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> temp;
        n = nums.size();
        solve(temp, nums);
        return result;
    }

    void solve(vector<int>& temp, vector<int>& nums) {
        if (temp.size() == n) {
            result.push_back(temp);
            return;
        }

        for (int i = 0; i < n; i++) {
            if (mp.find(nums[i]) == mp.end()) { // not found
                temp.push_back(nums[i]);
                mp.insert(nums[i]);
                solve(temp, nums);
                mp.erase(nums[i]);
                temp.pop_back();
            }
        }
    }
};

/*

## **Code Explanation: Generate All Permutations of an Array**

User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily. also why taken min and max variable?

GitHub Copilot: I'll read the code and provide a detailed explanation with visualization. 

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week5/46.%20Permutations.cpp)

Great! This code generates **all permutations** of a given array using **Backtracking**. Let me explain it thoroughly.

## **Code Overview: Generate All Permutations**

This code finds **all possible orderings** of the input numbers using backtracking with a set to track used elements.

**Note:** This code doesn't use `min` and `max` variables - it uses **`st` (unordered_set)** to track which elements are already used.

---

## **Key Variables Explained**

| Variable      | Purpose |
|----------     |---------|
| **`st`**      | Tracks which numbers are already used in current permutation |
| **`temp`**    | Builds current permutation one element at a time |
| **`result`**  | Stores all completed permutations |
| **`n`**       | Size of input array |

---

## **How It Works**

**Basic Idea:**
- Try placing each unused number at the current position
- Recursively build the permutation
- **Backtrack**: Remove the choice and try next number

---

## **Dry Run: Finding Permutations of [1, 2, 3]**

```
Input: [1, 2, 3]
n = 3

┌─────────────────────────────────────────────────────────┐
│ CALL 1: solve([], [1,2,3])                              │
│ temp.size() = 0, n = 3 (not equal, continue)            │
│ Try each number:                                        │
├─────────────────────────────────────────────────────────┤
│                                                         │
│ ✓ First iteration: i=0, nums[0]=1                       │
│   1 not in set? YES → Add 1                             │
│   temp = [1], st = {1}                                  │
│   ⬇ RECURSE                                             │
│                                                         │
│   ┌─────────────────────────────────────────────────┐   │
│   │ CALL 2: solve([1], [1,2,3])                     │   │
│   │ temp.size() = 1, n = 3 (continue)               │   │
│   │                                                 │   │
│   │ ✓ i=0, nums[0]=1 → 1 in set, SKIP               │   │
│   │ ✓ i=1, nums[1]=2 → 2 not in set, Add            │   │
│   │   temp = [1,2], st = {1,2}                      │   │
│   │   ⬇ RECURSE                                     │   │
│   │                                                 │   │
│   │   ┌──────────────────────────────────────────┐ │   │
│   │   │ CALL 3: solve([1,2], [1,2,3])            │ │   │
│   │   │ temp.size() = 2, n = 3 (continue)        │ │   │
│   │   │                                          │ │   │
│   │   │ ✓ i=0, 1 in set, SKIP                    │ │   │
│   │   │ ✓ i=1, 2 in set, SKIP                    │ │   │
│   │   │ ✓ i=2, 3 not in set, Add                 │ │   │
│   │   │   temp = [1,2,3], st = {1,2,3}           │ │   │
│   │   │   ⬇ RECURSE                              │ │   │
│   │   │                                          │ │   │
│   │   │   ┌──────────────────────────────────┐  │ │   │
│   │   │   │ CALL 4: solve([1,2,3], ...)     │  │ │   │
│   │   │   │ temp.size() = 3, n = 3 ✓        │  │ │   │
│   │   │   │ BASE CASE! Add to result        │  │ │   │
│   │   │   │ result = [[1,2,3]]              │  │ │   │
│   │   │   │ RETURN                          │  │ │   │
│   │   │   └──────────────────────────────────┘  │ │   │
│   │   │                                          │ │   │
│   │   │   BACKTRACK: Remove 3                    │ │   │
│   │   │   temp = [1,2], st = {1,2}              │ │   │
│   │   │   (Loop ends, no more i values)         │ │   │
│   │   │   RETURN                                │ │   │
│   │   └──────────────────────────────────────────┘ │   │
│   │                                                 │   │
│   │ BACKTRACK: Remove 2                            │   │
│   │ temp = [1], st = {1}                           │   │
│   │ Continue with i=2...                           │   │
│   │                                                 │   │
│   │ ✓ i=2, nums[2]=3 → 3 not in set, Add           │   │
│   │   temp = [1,3], st = {1,3}                     │   │
│   │   ⬇ RECURSE → temp = [1,3,2]                   │   │
│   │   result = [[1,2,3], [1,3,2]]                  │   │
│   │                                                 │   │
│   │ RETURN                                         │   │
│   └─────────────────────────────────────────────────┘   │
│                                                         │
│ BACKTRACK: Remove 1                                    │
│ temp = [], st = {}                                     │
│ Continue with i=1...                                   │
│                                                         │
│ ✓ i=1, nums[1]=2 → Add 2                              │
│   (Similar process generates [2,1,3], [2,3,1])        │
│                                                         │
│ ✓ i=2, nums[2]=3 → Add 3                              │
│   (Similar process generates [3,1,2], [3,2,1])        │
│                                                         │
└─────────────────────────────────────────────────────────┘

FINAL RESULT:
[[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]]
```

---

## **Visual Tree Representation**

```
                              START (empty)
                              |
                ┌─────────────┼─────────────┐
                │             │             │
              [1]           [2]           [3]
              / \           / \           / \
            [1,2] [1,3]   [2,1] [2,3]   [3,1] [3,2]
            |     |       |     |       |     |
         [1,2,3][1,3,2] [2,1,3][2,3,1][3,1,2][3,2,1] ✓ RESULTS
```

---

## **Algorithm Steps**

```
1. Choose an unused number from array
   └─ Add to temp
   └─ Mark as used in set (st)
   
2. If temp has n elements → Found a permutation! Store it
   
3. If not → Recursively try next position with remaining numbers
   
4. BACKTRACK: Remove the number from temp and set
   (This allows trying other numbers at same position)
   
5. Repeat until all permutations found
```

---

## **Key Insight: Why Use Set (st)?**

The **unordered_set** tracks **which numbers are already used** in the current permutation path.

```
Example: Building [1,2,...]
├─ Add 1 to set: st = {1}
├─ Can't use 1 again (find returns != end())
└─ Can use 2 or 3 (find returns == end())
```

---

## **Code Flow**

```cpp
// Check if number is UNUSED
if(st.find(nums[i]) == st.end()) {  // Not found = not used ✓
    temp.push_back(nums[i]);         // Add to current path
    st.insert(nums[i]);              // Mark as used
    
    solve(temp, nums);               // Recurse deeper
    
    st.erase(nums[i]);               // BACKTRACK: Mark unused
    temp.pop_back();                 // BACKTRACK: Remove from path
}
```

---

## **Complexity Analysis**

| Aspect | Value |
|--------|-------|
| **Time Complexity** | **O(n! × n)** - n! permutations, each takes O(n) to build |
| **Space Complexity** | **O(n)** - Recursion depth + temp array + set |
| **Example:** n=3 | 3! = 6 permutations |
| **Example:** n=4 | 4! = 24 permutations |

---

## **Why This Approach?**

✅ **Backtracking** efficiently explores all combinations  
✅ **Set** prevents using same element twice  
✅ **Optimal** for small arrays (n ≤ 10)  
❌ Exponential growth for large n

*/