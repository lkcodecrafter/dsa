#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.size() == 0)
            return {};
        int m = matrix.size();
        int n = matrix[0].size();
        int dir=0;
        //dir
        //0   -> left  to right
        //1   -> top   to down
        //2   -> right to left
        //3   -> down  to top
        vector<int> result;
        int top = 0;
        int down = m-1;
        int left = 0;
        int right = n-1;
        while(top <=down && left <= right){
            if(dir==0){
                for(int i = left; i<=right;i++){
                result.push_back(matrix[top][i]);
                }
                top++;
            }
            if(dir==1)
            {
                for(int i = top;i<=down; i++){
                result.push_back(matrix[i][right]);
                }
                right--;
            }
            if(dir==2)
            {
                for(int i= right;i>=left; i--){
                result.push_back(matrix[down][i]); 
                }
                down--;
            }
            if(dir==3)
            {
                for(int i= down;i>=top;i--){
                result.push_back(matrix[i][left]); // 
                }
                left++;
            }
          
          dir++;
          if(dir==4){
            dir=0;
          }
        }
        return result;
    }
};

/*

User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily?

GitHub Copilot: Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week6/54.%20Spiral%20Matrix.cpp)

Perfect! This is the **Spiral Matrix** problem. Let me explain this code with a detailed dry run and visualization.

## Code Overview

This code traverses a 2D matrix in a **spiral pattern** (clockwise from outside to inside) and returns all elements in that order.

## How It Works

The algorithm uses **4 boundaries** to track which rows/columns have been visited:
- `top`: top row boundary
- `down`: bottom row boundary  
- `left`: left column boundary
- `right`: right column boundary

The `dir` variable controls direction:
- **0** = Left to Right (→)
- **1** = Top to Bottom (↓)
- **2** = Right to Left (←)
- **3** = Bottom to Top (↑)

## Visual Dry Run

Let's trace through a 3×4 matrix:
```
[1,  2,  3,  4]
[5,  6,  7,  8]
[9, 10, 11, 12]
```

### Step-by-Step Traversal:

```
Initial state:
top=0, down=2, left=0, right=3, dir=0

┌────────────────────────────┐
│ 1→ 2→ 3→ 4  (dir=0)       │
│              ↓              │
│              8  (dir=1)    │
│              ↓              │
│ 9←10←11←12  (dir=2)       │
│ ↑              │            │
│ 5  (dir=3)     │            │
└────────────────────────────┘
```

### Iteration Breakdown:

**Iteration 1 (dir=0):** Left→Right on row 0
```
Result: [1, 2, 3, 4]
top++  → top=1
dir=1
```

**Iteration 2 (dir=1):** Top→Bottom on column 3
```
Result: [1, 2, 3, 4, 8, 12]
right--  → right=2
dir=2
```

**Iteration 3 (dir=2):** Right→Left on row 2
```
Result: [1, 2, 3, 4, 8, 12, 11, 10, 9]
down--  → down=1
dir=3
```

**Iteration 4 (dir=3):** Bottom→Top on column 0
```
Result: [1, 2, 3, 4, 8, 12, 11, 10, 9, 5]
left++  → left=1
dir=0
```

**Iteration 5 (dir=0):** Left→Right on row 1
```
Result: [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]
top++  → top=2
Now top > down, loop ends ✓
```

## Key Points

| Step | Direction | What Happens | Update |
|------|-----------|--------------|--------|
| 0 | → Left-Right | Traverse top row | top++ |
| 1 | ↓ Top-Bottom | Traverse right column | right-- |
| 2 | ← Right-Left | Traverse bottom row | down-- |
| 3 | ↑ Bottom-Top | Traverse left column | left++ |

**Time Complexity:** O(m × n) - visit each element once  
**Space Complexity:** O(1) - only boundaries, not counting output

Would you like me to explain any specific part in more detail or help with edge cases?
*/