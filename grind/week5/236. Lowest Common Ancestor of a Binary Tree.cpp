#include<iostream>
#include<vector>
using namespace std;
 // Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 
 
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q){
            return root;
        }
        
        TreeNode* left  =  lowestCommonAncestor(root->left, p, q); // 
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        if(left && right){ // found p and q in left and right subtree
            return root; // this is lca
        }

        return left ? left : right;
    }
};

/*

User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily.

GitHub Copilot: I'll read the file first to understand the code, then provide a detailed explanation with visualization. 

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week5/236.%20Lowest%20Common%20Ancestor%20of%20a%20Binary%20Tree.cpp)

Perfect! I can see this code solves the **Lowest Common Ancestor (LCA) of a Binary Tree** problem. Let me explain it with a detailed dry run and visualization.

## Code Overview

The algorithm finds the **Lowest Common Ancestor** - the deepest node that has both `p` and `q` as descendants.

### Algorithm Logic:

1. **Base Case**: If we reach `null` or find either `p` or `q`, return that node
2. **Recursive Case**: Search for `p` and `q` in left and right subtrees
3. **Decision**: 
   - If both found in left AND right → current node is LCA
   - If found in only one subtree → return that subtree's result

---

## Dry Run with Example

Let's trace through a sample tree:

```
        3
       / \
      5   1
     / \ / \
    6  2 0  8
      / \
     7   4
```

**Goal**: Find LCA of nodes **5** and **1**

### Step-by-Step Execution:

```
lowestCommonAncestor(3, 5, 1)
│
├─ root = 3 (not p, not q, continue)
│
├─ left = lowestCommonAncestor(3→right(1), 5, 1)
│  │
│  └─ root = 1 (equals q, return 1) ✓
│
├─ right = lowestCommonAncestor(3→left(5), 5, 1)
│  │
│  └─ root = 5 (equals p, return 5) ✓
│
├─ left=1 && right=5 (both found!)
│
└─ return 3 (LCA found!)
```

### Visualization of the Recursive Tree:

```
                    lowestCommonAncestor(3, 5, 1)
                         /              \
                    left=1              right=5
                      /                    \
           (found q)↓                      ↓(found p)
          lowestCommonAncestor(1, 5, 1)   lowestCommonAncestor(5, 5, 1)
          returns 1                       returns 5
          
          Both left & right exist
          ✓ Result: 3 is the LCA
```

---

## Another Example: LCA of **6** and **2**

```
        3
       / \
      5   1
     / \ / \
    6  2 0  8
      / \
     7   4
```

```
lowestCommonAncestor(3, 6, 2)
│
├─ At node 3: neither is 6 or 2
├─ Search left(5): left = lowestCommonAncestor(5, 6, 2)
│  │
│  └─ At node 5: neither is 6 or 2
│     ├─ Search left(6): returns 6 ✓ (found p)
│     ├─ Search right(2): returns 2 ✓ (found q)
│     ├─ Both found in subtree of 5
│     └─ return 5
│
├─ Search right(1): left = lowestCommonAncestor(1, 6, 2)
│  └─ returns null (6, 2 not in right subtree)
│
├─ left=5 (found), right=null
└─ return 5 (LCA of 6 and 2)
```

---

## Key Points:

✅ **Time Complexity**: O(n) - visits each node once  
✅ **Space Complexity**: O(h) - recursion stack depth = height of tree  
⚠️ **Note in Code**: Lines 20-21 have `left` and `right` swapped (should be `left→root->left`, `right→root->right`), but the logic still works because we check both sides

This algorithm is elegant because it uses **post-order traversal** - we get results from children before deciding at current node!

*/