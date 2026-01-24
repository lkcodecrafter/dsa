# Binary Tree Traversals (Iterative) - README

## Problem References
1. **PreOrder Traversal Iterative**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
2. **PostOrder Traversal Iterative**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)
3. **InOrder Traversal Iterative**: [GeeksforGeeks Problem](https://www.geeksforgeeks.org/problem...)

---

## Table of Contents
- 00:00 Introduction
- 03:00 Problem 1 - PreOrder Traversal (Iterative)
- 10:33 Calculating Time and Space Complexity of Problem 1
- 11:27 Code Part - PreOrder Traversal Iterative
- 13:33 Problem 2 - PostOrder Traversal (Iterative)
- 20:48 Time and Space Complexity of Problem 2
- 21:01 Code Part - PostOrder Traversal Iterative
- 22:18 Problem 3 - InOrder Traversal (Iterative)
- 42:05 Code Part - InOrder Traversal Iterative
- 46:28 Last Note

---

## Notes & Explanations

### 1. PreOrder Traversal (NLR)
- **Order**: Node → Left → Right
- **Iterative Approach**: Use a stack. Push root, then push right child, then left child (so left is processed first).
- **Complexity**:
  - Time: `O(N)` (each node visited once)
  - Space: `O(N)` (stack can hold up to N nodes)

### 2. PostOrder Traversal (LRN)
- **Order**: Left → Right → Node
- **Iterative Approach**: Two stacks method (push root to first stack, process children, then reverse order in second stack).  
  Alternative: Use one stack with markers.
- **Complexity**:
  - Time: `O(N)`
  - Space: `O(N)` (two stacks or recursion simulation)

### 3. InOrder Traversal (LNR)
- **Order**: Left → Node → Right
- **Iterative Approach**: Use a stack. Keep pushing left children, then process node, then move to right.
- **Complexity**:
  - Time: `O(N)`
  - Space: `O(N)` (stack for nodes)

---

## C++ Implementations

```cpp
#include <iostream>
#include <stack>
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

// 1. PreOrder Traversal (Iterative)
void preorderIterative(Node* root) {
    if (!root) return;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* curr = st.top(); st.pop();
        cout << curr->data << " ";
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
    }
}

// 2. PostOrder Traversal (Iterative - using 2 stacks)
void postorderIterative(Node* root) {
    if (!root) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);
        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// 3. InOrder Traversal (Iterative)
void inorderIterative(Node* root) {
    stack<Node*> st;
    Node* curr = root;
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        cout << curr->data << " ";
        curr = curr->right;
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

    cout << "PreOrder Iterative: "; preorderIterative(root); cout << endl;
    cout << "PostOrder Iterative: "; postorderIterative(root); cout << endl;
    cout << "InOrder Iterative: "; inorderIterative(root); cout << endl;

    return 0;
}
```

---

## Outro / Last Note
- Iterative traversals simulate recursion using **stack(s)**.  
- **PreOrder** → Push root, then right, then left.  
- **PostOrder** → Use two stacks or marker technique.  
- **InOrder** → Push left until NULL, then backtrack and go right.  
- Practice on small trees to clearly see the visiting order.
