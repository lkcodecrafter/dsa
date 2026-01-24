#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

  class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValid(root, LLONG_MIN, LLONG_MAX);
    }

    bool isValid(TreeNode* root, long long min, long long max) {
        if (root == nullptr) {
            return true;
        }
        if (root->val <= min || root->val >= max) {
            return false;
        }
        return isValid(root->left, min, root->val)
            && isValid(root->right, root->val, max);
    }
};

/*
User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily. also why taken min and max variable?

GitHub Copilot: I'll read the code first and then explain it with visualizations and a dry run. 

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week4/98.%20Validate%20Binary%20Search%20Tree.cpp)

Perfect! Let me explain this code with a visual diagram and dry run.

## **Code Explanation: Validate Binary Search Tree**

### **Why do we need `min` and `max` variables?**

In a Binary Search Tree (BST):
- **Left subtree** → all values must be **less than parent**
- **Right subtree** → all values must be **greater than parent**

The `min` and `max` track the **valid range** each node must fall within. For example:
- Root can be any value (LLONG_MIN to LLONG_MAX)
- If we go left from root, max becomes parent's value
- If we go right from root, min becomes parent's value

---

## **Visual Diagram**

```
                    10  [valid range: -∞ to +∞]
                   /  \
            (go left)  (go right)
                /          \
               5            15
         [-∞ to 10]    [10 to +∞]
            /  \          /  \
           3    7        12   20
       [-∞,5] [5,10]  [10,15][15,+∞]
```

**Key Points:**
- Node `5`: Must be < 10 ✓ and > -∞ ✓
- Node `7`: Must be < 10 ✓ and > 5 ✓
- Node `15`: Must be > 10 ✓ and < +∞ ✓

---

## **Dry Run with Example**

Tree: `10 / \ 5 15 / \ 3 7`

```
Step 1: isValid(10, -∞, +∞)
        Check: 10 > -∞ ✓ AND 10 < +∞ ✓
        
        Step 1.1: isValid(5, -∞, 10)    [LEFT subtree]
                  Check: 5 > -∞ ✓ AND 5 < 10 ✓
                  
                  Step 1.1.1: isValid(3, -∞, 5)
                              Check: 3 > -∞ ✓ AND 3 < 5 ✓
                              isValid(nullptr, 5, 5) → TRUE
                              Result: TRUE ✓
                  
                  Step 1.1.2: isValid(7, 5, 10)
                              Check: 7 > 5 ✓ AND 7 < 10 ✓
                              isValid(nullptr) → TRUE
                              Result: TRUE ✓
                  
                  Result: TRUE ✓
        
        Step 1.2: isValid(15, 10, +∞)  [RIGHT subtree]
                  Check: 15 > 10 ✓ AND 15 < +∞ ✓
                  isValid(nullptr) → TRUE
                  Result: TRUE ✓
        
FINAL RESULT: TRUE ✓ (Valid BST)
```

---

## **Algorithm Summary**

| Step | Check | Purpose |
|------|-------|---------|
| 1. | `if (root == nullptr)` | Base case: empty tree is valid |
| 2. | `if (root->val ≤ min OR root->val ≥ max)` | Node violates BST property |
| 3. | Recurse left with `max = root->val` | Left child must be smaller |
| 4. | Recurse right with `min = root->val` | Right child must be larger |

**Time Complexity:** O(n) - visit each node once  
**Space Complexity:** O(h) - recursion depth = height

*/