# Trees Data Structure

## Table of Contents
- 00:00 Introduction
- 01:00 Definition of Trees Data Structure
- 01:17 Understanding Trees with Example
- 08:22 More Example of Trees Data Structure
- 13:03 What is Binary Tree
- 14:11 Understanding Terminologies of Trees
- 25:28 How to create Binary Tree Data Structure ?
- 40:35 How to code Binary Tree Data Structure ?
- 51:07 Code Part - Implementing Binary Tree Data Structure
- 59:23 Outro/Last Note

## Introduction
Trees are a widely used data structure in computer science that represent hierarchical relationships.

## Definition of Trees Data Structure
A tree is a non-linear data structure that consists of nodes connected by edges. It starts with a root node and can have multiple levels of children nodes.

## Understanding Trees with Example
Think of a family tree or an organizational hierarchy. The top-most person is the root, and the subordinates or children continue the branching.

## More Example of Trees Data Structure
Examples: Directory structures in computers, JSON/XML parsing, decision trees in AI.

## What is Binary Tree
A binary tree is a tree data structure where each node can have at most two children: left child and right child.

## Terminologies of Trees
- **Root**: The top-most node.
- **Child**: Node directly connected to another node.
- **Parent**: Node which has children.
- **Leaf**: Node with no children.
- **Height**: Longest path from root to leaf.

## How to create Binary Tree Data Structure ?
We can define a `Node` class with attributes for data, left child, and right child.

## How to code Binary Tree Data Structure ?
By linking nodes together using pointers (C++/Java) or references (Python).

## Code Part - Implementing Binary Tree Data Structure
```cpp
#include <iostream>
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

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    cout << "Binary Tree Created" << endl;
    return 0;
}
```

## Outro/Last Note
Trees are essential for hierarchical data representation and efficient problem solving in computer science.
