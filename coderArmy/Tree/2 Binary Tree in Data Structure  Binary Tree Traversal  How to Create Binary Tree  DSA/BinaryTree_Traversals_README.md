# Binary Tree Traversals

## Problem References
1. **PreOrder Traversal (NLR)**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
2. **InOrder Traversal (LNR)**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
3. **PostOrder Traversal (LRN)**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
4. **Level Order Traversal**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)

---

## Table of Contents
- 00:00 Introduction
- 00:49 Recap of Method 1 - Create Binary Tree
- 02:51 Method 2 - Create Binary Tree
- 25:09 Code Part - Create Binary Tree
- 33:11 Calculating Time and Space Complexity of Binary Tree
- 45:35 Understanding Traversal in Binary Tree, and Types of Traversal
- 46:50 Understanding PreOrder Traversal - NLR
- 51:28 Understanding InOrder Traversal - LNR
- 54:38 Understanding PostOrder Traversal - LRN
- 58:09 How to Print - PreOrder Traversal
- 01:06:37 How to Print - InOrder Traversal
- 01:08:17 How to Print - PostOrder Traversal
- 01:09:29 Practicing Traversal with an Example of Binary Tree
- 01:12:50 Code Part - Implementing Traversal Methods of Binary Tree
- 01:23:05 Understanding Level Order Traversal - Homework

---

## Traversal Types Explanation

### PreOrder Traversal (NLR)
Visit the **Node**, then traverse the **Left** subtree, and finally the **Right** subtree.

### InOrder Traversal (LNR)
Traverse the **Left** subtree, then visit the **Node**, and finally traverse the **Right** subtree.

### PostOrder Traversal (LRN)
Traverse the **Left** subtree, then the **Right** subtree, and finally visit the **Node**.

### Level Order Traversal
Visit nodes level by level using a queue (Breadth First Search approach).

---

## C++ Implementation of Traversals

```cpp
#include <iostream>
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

// PreOrder Traversal (NLR)
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// InOrder Traversal (LNR)
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// PostOrder Traversal (LRN)
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Level Order Traversal (BFS)
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

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "PreOrder: "; preorder(root); cout << endl;
    cout << "InOrder: "; inorder(root); cout << endl;
    cout << "PostOrder: "; postorder(root); cout << endl;
    cout << "LevelOrder: "; levelOrder(root); cout << endl;

    return 0;
}
```

---

## Outro / Homework
Practice implementing all four traversals and compare the output for different binary tree structures.
