# Pattern: Level Order Traversal (BFS) - Full Study Guide

This guide contains the logic, C++ solutions, and dry runs for all 8 lessons in the Level Order Traversal pattern.

---

## 🏗️ The BFS Template
All problems below utilize this core structure:
```cpp
queue<TreeNode*> q;
q.push(root);
while(!q.empty()){
    int levelSize = q.size(); // Defines the boundary of the current level
    for(int i = 0; i < levelSize; i++){
        TreeNode* curr = q.front(); q.pop();
        // Process node here
        if(curr->left) q.push(curr->left);
        if(curr->right) q.push(curr->right);
    }
}
```

---

## 1. Reverse Level Order Traversal (Easy)
**Goal:** Return levels from bottom to top.
```cpp
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    reverse(res.begin(), res.end());
    return res;
}
```

Dry Run: [3,9,20,null,null,15,7]

Initial: Queue = [3]

Level 1 (size 1): Pop 3, push 9, 20. Res = [[3]]. Queue = [9, 20]

Level 2 (size 2): Pop 9 (no children), pop 20 (push 15, 7). Res = [[3], [9, 20]]. Queue = [15, 7]

Level 3 (size 2): Pop 15, pop 7. Res = [[3], [9, 20], [15, 7]].

Final Step: reverse(res) -> [[15, 7], [9, 20], [3]].

---

## 2. Find Largest Value in Each Tree Row (Medium)
```cpp
vector<int> largestValues(TreeNode* root) {
    if (!root) return {};
    vector<int> res;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size(), maxVal = INT_MIN;
        for (int i = 0; i < size; i++) {
            TreeNode* n = q.front(); q.pop();
            maxVal = max(maxVal, n->val);
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        res.push_back(maxVal);
    }
    return res;
}
```

Dry Run: [1,3,2,5,3,null,9]

Level 0: Queue [1]. Max = 1. Res = [1].

Level 1: Queue [3, 2]. Max = 3. Res = [1, 3].

Level 2: Queue [5, 3, 9]. Max = 9. Res = [1, 3, 9].

---

## 3. Maximum Width of Binary Tree (Medium)
**Note:** Uses unsigned long long or index normalization to handle overflow.
```cpp
int widthOfBinaryTree(TreeNode* root) {
    if (!root) return 0;
    long maxW = 0;
    queue<pair<TreeNode*, long>> q;
    q.push({root, 0});
    while (!q.empty()) {
        int size = q.size();
        long minIdx = q.front().second; 
        long first, last;
        for (int i = 0; i < size; i++) {
            long curIdx = q.front().second - minIdx;
            TreeNode* node = q.front().first; q.pop();
            if (i == 0) first = curIdx;
            if (i == size - 1) last = curIdx;
            if (node->left) q.push({node->left, 2 * curIdx + 1});
            if (node->right) q.push({node->right, 2 * curIdx + 2});
        }
        maxW = max(maxW, last - first + 1);
    }
    return maxW;
}
```
Dry Run: [1, 3, 2, 5, 3, null, 9]

Level 0: Index 0. Width = 0-0+1 = 1.

Level 1: 3 at idx 1, 2 at idx 2. Width = 2-1+1 = 2.

Level 2: 5 at idx 3, 3 at idx 4, 9 at idx 6. Width = 6-3+1 = 4.

---

## 4. Maximum Level Sum of a Binary Tree (Medium)
```cpp
int maxLevelSum(TreeNode* root) {
    int maxSum = INT_MIN, ans = 0, level = 1;
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        int size = q.size();
        long long currentSum = 0;
        for (int i = 0; i < size; i++) {
            TreeNode* n = q.front(); q.pop();
            currentSum += n->val;
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        if (currentSum > maxSum) { 
            maxSum = currentSum;
            ans = level; 
        }
        
        level++;
    }
    return ans;
}
```

---

## 5. Zigzag Traversal (Medium)
```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> res;
    queue<TreeNode*> q; q.push(root);
    bool LtoR = true;
    while (!q.empty()) {
        int size = q.size();
        vector<int> row(size);
        for (int i = 0; i < size; i++) {
            TreeNode* n = q.front(); q.pop();
            int idx = LtoR ? i : (size - 1 - i);
            row[idx] = n->val;
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        res.push_back(row);
        LtoR = !LtoR;
    }
    return res;
}
```
Dry Run: [3, 9, 20, 15, 7]

LtoR true: Pop 3. Row = [3].

LtoR false: Pop 9, 20. Row[1]=9, Row[0]=20. Row = [20, 9].

LtoR true: Pop 15, 7. Row[0]=15, Row[1]=7. Row = [15, 7].

---

## 6. Even Odd Tree (Medium)
```cpp
bool isEvenOddTree(TreeNode* root) {
    queue<TreeNode*> q; q.push(root);
    int level = 0;
    while (!q.empty()) {
        int size = q.size(), prev = -1;
        for (int i = 0; i < size; i++) {
            TreeNode* n = q.front(); q.pop();
            if (level % 2 == 0) {
                if (n->val % 2 == 0 || (prev != -1 && n->val <= prev)) return false;
            } else {
                if (n->val % 2 != 0 || (prev != -1 && n->val >= prev)) return false;
            }
            prev = n->val;
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        level++;
    }
    return true;
}
```

---

## 7. N-ary Tree Level Order Traversal (Hard)
```cpp
vector<vector<int>> levelOrder(Node* root) {
    if (!root) return {};
    vector<vector<int>> res;
    queue<Node*> q; q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> currLevel;
        for (int i = 0; i < size; i++) {
            Node* n = q.front(); q.pop();
            currLevel.push_back(n->val);
            for (Node* child : n->children) q.push(child);
        }
        res.push_back(currLevel);
    }
    return res;
}
```

Dry Run:

Queue: [Root]

Step: Pop Root, push its vector<Node*> children to the queue.

Loop: Repeat until queue is empty.
"""

---

## 🔍 Example Dry Run: Zigzag Traversal
**Tree:** `[3, 9, 20, null, null, 15, 7]`

1. **Level 0 (L to R):** Queue `[3]`. Pop `3`. Level: `[3]`. Flag flips.
2. **Level 1 (R to L):** Queue `[9, 20]`. 
   - Pop `9`, place at `index 1`.
   - Pop `20`, place at `index 0`.
   - Level: `[20, 9]`. Flag flips.
3. **Level 2 (L to R):** Queue `[15, 7]`. Level: `[15, 7]`.
**Result:** `[[3], [20, 9], [15, 7]]`
