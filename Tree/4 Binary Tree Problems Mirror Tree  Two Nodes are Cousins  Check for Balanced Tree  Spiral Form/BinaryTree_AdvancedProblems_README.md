# Binary Tree Advanced Problems - README

## Problem References
1. **Determine if Two Trees are Identical**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
2. **Mirror Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
3. **Check for Balanced Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
4. **Level Order Traversal in Spiral Form**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
5. **Check if Two Nodes are Cousins**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)

---

## Table of Contents
- 00:00 Introduction
- 00:30 Problem 1 - Two Trees are Identical
- 16:21 Calculating Time Complexity
- 16:59 Code Part - Two Trees are Identical
- 19:06 Problem 2 - Mirror Tree
- 25:57 Code Part - Mirror Tree
- 27:13 Problem 3 - Check for Balance Tree
- 48:20 Code Part - Check for Balance Tree
- 51:40 Problem 4 - Level order Traversal in Spiral Form
- 01:14:07 Calculating Time and Space Complexity
- 01:14:57 Code Part - Level Order Traversal in Spiral Form
- 01:18:48 Problem 5 - Check If 2 Nodes are Cousins
- 01:37:33 Code Part - Check if 2 Nodes are cousin
- 01:44:36 Last Note

---

## C++ Implementations

```cpp
#include <iostream>
#include <queue>
#include <algorithm>
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

// Problem 1: Determine if Two Trees are Identical
bool isIdentical(Node* a, Node* b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    return (a->data == b->data) && 
           isIdentical(a->left, b->left) &&
           isIdentical(a->right, b->right);
}

// Problem 2: Mirror Tree
Node* mirror(Node* root) {
    if (root == NULL) return root;
    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
    return root;
}

// Problem 3: Check for Balanced Tree
int checkHeight(Node* root) {
    if (root == NULL) return 0;
    int lh = checkHeight(root->left);
    if (lh == -1) return -1;
    int rh = checkHeight(root->right);
    if (rh == -1) return -1;
    if (abs(lh - rh) > 1) return -1;
    return max(lh, rh) + 1;
}
bool isBalanced(Node* root) {
    return checkHeight(root) != -1;
}

// Problem 4: Level Order Traversal in Spiral Form
void spiralOrder(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    bool leftToRight = false;
    while (!q.empty()) {
        int n = q.size();
        vector<int> level(n);
        for (int i = 0; i < n; i++) {
            Node* curr = q.front();
            q.pop();
            int index = leftToRight ? i : (n - i - 1);
            level[index] = curr->data;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        for (int val : level) cout << val << " ";
        leftToRight = !leftToRight;
    }
}

// Problem 5: Check if Two Nodes are Cousins
bool isCousins(Node* root, int x, int y) {
    if (root == NULL) return false;
    queue<pair<Node*, Node*>> q; // (node, parent)
    q.push({root, NULL});
    while (!q.empty()) {
        int n = q.size();
        Node* parentX = NULL;
        Node* parentY = NULL;
        for (int i = 0; i < n; i++) {
            auto [node, parent] = q.front();
            q.pop();
            if (node->data == x) parentX = parent;
            if (node->data == y) parentY = parent;
            if (node->left) q.push({node->left, node});
            if (node->right) q.push({node->right, node});
        }
        if (parentX && parentY) return parentX != parentY;
        if ((parentX && !parentY) || (!parentX && parentY)) return false;
    }
    return false;
}

int main() {
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);

    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);

    cout << "Identical Trees: " << (isIdentical(root1, root2) ? "Yes" : "No") << endl;

    cout << "Is Balanced: " << (isBalanced(root1) ? "Yes" : "No") << endl;

    cout << "Spiral Order: "; spiralOrder(root1); cout << endl;

    cout << "Are 4 and 5 Cousins? " << (isCousins(root1, 4, 5) ? "Yes" : "No") << endl;

    return 0;
}
```

---

## Outro / Homework
- Implement mirror function and verify by printing level order before & after mirroring.
- Practice balanced tree check on skewed and full binary trees.
- Test cousin check with multiple examples.
