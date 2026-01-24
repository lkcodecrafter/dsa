# Constructing Binary Tree from Traversals - README

## Problem References
1. **Construct Tree from Inorder & Preorder**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
2. **Construct Tree from Inorder & Postorder**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
3. **Check Tree Traversal**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)

---

## Table of Contents
- 00:00 Introduction
- 00:30 Problem 1 - Construct a Tree from Inorder & Preorder
- 01:00 Trying to Build Tree using only PreOrder
- 02:38 Trying to Build Tree using only InOrder
- 03:34 Trying to Build Tree using only PostOrder
- 05:09 Trying to Build Tree using PreOrder & PostOrder
- 07:09 Trying to Build Tree using PreOrder & InOrder
- 09:01 Why we can't Create Unique Tree using PreOrder & PostOrder
- 13:10 Understanding with Examples
- 20:49 Continuing Problem 1 - Construct Tree from InOrder & PreOrder
- 48:38 Time & Space Complexity
- 49:51 Code Part - Construct Tree from InOrder & PreOrder
- 54:41 Problem 2 - Construct Tree from InOrder & PostOrder
- 1:07:30 Code Part - Construct Tree from InOrder & PostOrder
- 1:10:00 Problem 3 - Check Tree Traversal (Homework)
- 1:11:48 Last Note

---

## Notes & Explanations

### Why Single Traversal is Not Enough?
- **Only PreOrder / Only PostOrder / Only InOrder**: Not enough to uniquely identify a binary tree.
- **PreOrder + InOrder**: Can uniquely construct the tree.
- **PostOrder + InOrder**: Can uniquely construct the tree.
- **PreOrder + PostOrder**: Cannot always construct a unique tree (ambiguous cases).

---

## Problem 1 - Construct a Tree from InOrder & PreOrder

- **PreOrder** gives the **root node first**.
- **InOrder** divides the tree into **left subtree** and **right subtree**.

### Approach
1. Start with PreOrder index = 0.
2. Pick element from PreOrder → this is the root.
3. Find root index in InOrder array.
4. Elements left to root in InOrder → Left Subtree.
5. Elements right to root in InOrder → Right Subtree.
6. Recursively build left and right subtrees.

**Complexity**:
- Time: `O(N)` if we use hashmap for InOrder indices, otherwise `O(N^2)`.
- Space: `O(N)` recursion + hashmap.

---

## Problem 2 - Construct a Tree from InOrder & PostOrder

- **PostOrder** gives the **root node last**.
- **InOrder** divides the tree into **left subtree** and **right subtree**.

### Approach
1. Start from the last element in PostOrder → root.
2. Find root index in InOrder.
3. Right side → Right subtree, Left side → Left subtree.
4. Recurse (important: build right subtree first, then left).

**Complexity**:
- Time: `O(N)` (with hashmap).
- Space: `O(N)`.

---

## Problem 3 - Check Tree Traversal (Homework)
- Given three traversals, check if they belong to the same tree.
- Validate by constructing the tree using two traversals and then checking if the third traversal matches.

---

## C++ Implementations

```cpp
#include <iostream>
#include <unordered_map>
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

// Build Tree from InOrder and PreOrder
Node* buildTreePreIn(int inorder[], int preorder[], int inStart, int inEnd, int &preIndex, unordered_map<int,int>& mp) {
    if (inStart > inEnd) return NULL;
    int curr = preorder[preIndex++];
    Node* node = new Node(curr);
    if (inStart == inEnd) return node;
    int inIndex = mp[curr];
    node->left = buildTreePreIn(inorder, preorder, inStart, inIndex - 1, preIndex, mp);
    node->right = buildTreePreIn(inorder, preorder, inIndex + 1, inEnd, preIndex, mp);
    return node;
}

// Build Tree from InOrder and PostOrder
Node* buildTreePostIn(int inorder[], int postorder[], int inStart, int inEnd, int &postIndex, unordered_map<int,int>& mp) {
    if (inStart > inEnd) return NULL;
    int curr = postorder[postIndex--];
    Node* node = new Node(curr);
    if (inStart == inEnd) return node;
    int inIndex = mp[curr];
    node->right = buildTreePostIn(inorder, postorder, inIndex + 1, inEnd, postIndex, mp);
    node->left = buildTreePostIn(inorder, postorder, inStart, inIndex - 1, postIndex, mp);
    return node;
}

// Utility function for printing InOrder
void printInOrder(Node* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->data << " ";
    printInOrder(root->right);
}

int main() {
    int inorder[] = {4, 2, 5, 1, 6, 3, 7};
    int preorder[] = {1, 2, 4, 5, 3, 6, 7};
    int n = 7;
    unordered_map<int,int> mp;
    for (int i = 0; i < n; i++) mp[inorder[i]] = i;
    int preIndex = 0;
    Node* root1 = buildTreePreIn(inorder, preorder, 0, n - 1, preIndex, mp);

    cout << "Tree from PreOrder & InOrder (InOrder print): ";
    printInOrder(root1);
    cout << endl;

    int postorder[] = {4, 5, 2, 6, 7, 3, 1};
    unordered_map<int,int> mp2;
    for (int i = 0; i < n; i++) mp2[inorder[i]] = i;
    int postIndex = n - 1;
    Node* root2 = buildTreePostIn(inorder, postorder, 0, n - 1, postIndex, mp2);

    cout << "Tree from PostOrder & InOrder (InOrder print): ";
    printInOrder(root2);
    cout << endl;
}
```

---

## Outro / Last Note
- Single traversal is **not enough** to uniquely build a tree.
- **PreOrder + InOrder** or **PostOrder + InOrder** can build a unique tree.
- **PreOrder + PostOrder** may lead to multiple trees (ambiguous).
- Always use a hashmap for InOrder index lookup to achieve `O(N)` construction.
