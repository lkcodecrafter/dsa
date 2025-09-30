# Binary Tree Views - README

## Problem References
1. **Left View of Binary Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
2. **Right View of Binary Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
3. **Top View of Binary Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
4. **Bottom View of Binary Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)

---

## Table of Contents
- 00:00 Introduction
- 00:49 Problem 1 - Left View of Binary Tree
- 11:01 Time Complexity Calculation of Problem 1
- 11:26 Code Part - Left View of Binary Tree
- 14:56 Method 2 - Left View of Binary Tree
- 29:07 Code Part - Method 2 - Left View of Binary Tree
- 31:02 Problem 2 - Right View of Binary Tree
- 35:17 Code Part - Right View of Binary Tree
- 38:04 Problem 3 - Top View of Binary Tree
- 45:31 Method 1 - Top View using Level Order Traversal
- 01:10:31 Code Part - Method 1 - Top View
- 01:17:39 Method 2 - Top View using Recursion
- 01:29:35 Code Part - Method 2 - Top View
- 01:35:04 Homework - Bottom View of Binary Tree / Last Note

---

## Notes

### Left View of Binary Tree
- Shows nodes visible from the **left side**.  
- **Method 1**: Level Order Traversal → print first node at each level.  
- **Method 2**: Recursion → track maximum depth and print first visited node.

### Right View of Binary Tree
- Shows nodes visible from the **right side**.  
- Print last node at each level during level order traversal.

### Top View of Binary Tree
- Nodes visible from **above** the tree.  
- Use horizontal distance mapping → first node at each HD is visible.

### Bottom View of Binary Tree (Homework)
- Nodes visible from **below** the tree.  
- Overwrite at each horizontal distance, so last node at HD remains visible.

---

## C++ Implementations

```cpp
#include <iostream>
#include <map>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Left View using Level Order
void leftView(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            Node* curr = q.front(); q.pop();
            if (i == 0) cout << curr->data << " "; // first node at level
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
}

// Right View using Level Order
void rightView(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            Node* curr = q.front(); q.pop();
            if (i == n - 1) cout << curr->data << " "; // last node at level
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
}

// Top View using Level Order
void topView(Node* root) {
    if (!root) return;
    map<int, int> hdMap; // horizontal distance -> node value
    queue<pair<Node*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        auto [node, hd] = q.front(); q.pop();
        if (hdMap.find(hd) == hdMap.end()) {
            hdMap[hd] = node->data; // store first node at hd
        }
        if (node->left) q.push({node->left, hd - 1});
        if (node->right) q.push({node->right, hd + 1});
    }
    for (auto p : hdMap) cout << p.second << " ";
}

// Bottom View using Level Order
void bottomView(Node* root) {
    if (!root) return;
    map<int, int> hdMap;
    queue<pair<Node*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        auto [node, hd] = q.front(); q.pop();
        hdMap[hd] = node->data; // overwrite with last node at hd
        if (node->left) q.push({node->left, hd - 1});
        if (node->right) q.push({node->right, hd + 1});
    }
    for (auto p : hdMap) cout << p.second << " ";
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "Left View: "; leftView(root); cout << endl;
    cout << "Right View: "; rightView(root); cout << endl;
    cout << "Top View: "; topView(root); cout << endl;
    cout << "Bottom View: "; bottomView(root); cout << endl;

    return 0;
}
```

---

## Outro / Last Note
- **Left/Right Views**: Side visibility.  
- **Top/Bottom Views**: Vertical visibility.  
- Practice variations and dry-run them on different tree shapes for mastery.
