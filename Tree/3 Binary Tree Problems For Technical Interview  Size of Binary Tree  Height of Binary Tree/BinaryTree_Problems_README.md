# Binary Tree Problems - README

## Problem References
1. **Level Order Traversal**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
2. **Size of Binary Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
3. **Sum of Binary Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
4. **Count Leaves in Binary Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
5. **Count Non-Leaf Nodes in Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
6. **Height of Binary Tree**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
7. **Largest Value in Each Level**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)

---

## Table of Contents
- 00:00 Introduction
- 00:45 Problem 1 - Level Order Traversal
- 13:32 Calculating Time and Space Complexity 
- 18:34 Code Part - Implementing Level Order Traversal
- 20:21 How to Calculate Pre-Order, Post-Order and In-Order by seeing a Binary Tree Diagram
- 29:51 Problem 2 - Method 1 - Size of Binary Tree
- 38:54 Method 2 - Size of Binary Tree
- 46:46 Code Part - Method 1 - Size of Binary Tree
- 48:48 Code Part - Method 2 - Size of Binary Tree
- 50:22 Problem 3 - Method 1 - Sum of Binary Tree
- 55:27 Method 2 - Sum of Binary Tree
- 01:00:30 Code Part - Method 1 - Sum of Binary Tree
- 01:02:49 Code Part - Method 2 - Sum of Binary Tree
- 01:04:48 Problem 4 - Count Leaves of Binary Tree
- 01:15:44 Code Part - Count Leaves of Binary Tree
- 01:20:03 Problem 5 - Count Non Leaf Nodes
- 01:27:01 Code Part - Count Non Leaf Nodes
- 01:28:44 Problem 6 - Height of Binary Tree
- 01:41:39 Code Part - Height of Binary Tree
- 01:43:00 Problem 7 - Largest Value in each Level - Homework/Last Note

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

// Problem 1: Level Order Traversal
void levelOrder(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// Problem 2: Size of Binary Tree
int size(Node* root) {
    if (root == NULL) return 0;
    return 1 + size(root->left) + size(root->right);
}

// Problem 3: Sum of Binary Tree
int sum(Node* root) {
    if (root == NULL) return 0;
    return root->data + sum(root->left) + sum(root->right);
}

// Problem 4: Count Leaves in Binary Tree
int countLeaves(Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// Problem 5: Count Non-Leaf Nodes
int countNonLeaves(Node* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return 0;
    return 1 + countNonLeaves(root->left) + countNonLeaves(root->right);
}

// Problem 6: Height of Binary Tree
int height(Node* root) {
    if (root == NULL) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// Problem 7: Largest Value in Each Level
void largestValueEachLevel(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        int maxVal = INT_MIN;
        for (int i = 0; i < n; i++) {
            Node* curr = q.front();
            q.pop();
            maxVal = max(maxVal, curr->data);
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << maxVal << " ";
    }
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "Level Order: "; levelOrder(root); cout << endl;
    cout << "Size: " << size(root) << endl;
    cout << "Sum: " << sum(root) << endl;
    cout << "Leaves: " << countLeaves(root) << endl;
    cout << "Non-Leaves: " << countNonLeaves(root) << endl;
    cout << "Height: " << height(root) << endl;
    cout << "Largest Values per Level: "; largestValueEachLevel(root); cout << endl;

    return 0;
}
```

---

## Outro / Homework
- Implement all problems and test on different binary trees.
- Try writing iterative solutions where possible.
- Practice Level Order variants (like reverse level order, zigzag traversal).
