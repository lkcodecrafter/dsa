/*
Question:
Given a binary tree. Find the size of its largest subtree that is a Binary
Search Tree.

Explanation:
- We use a recursive function to traverse the binary tree in a bottom-up manner.
- At each node, we check if the left and right subtrees are binary search trees.
- If the current node satisfies the binary search tree condition (i.e., the
value of the current node is greater than the maximum value in the left subtree
and less than the minimum value in the right subtree), then we update the size
of the largest subtree.
- We return a triplet containing the size of the subtree, the minimum value in
the subtree, and the maximum value in the subtree.

Time Complexity:
- The recursive function visits each node once, so the time complexity is O(n),
where n is the number of nodes in the binary tree.

Space Complexity:
- The space complexity is O(h), where h is the height of the binary tree, as the
recursion stack stores the nodes in the path from the root to the deepest leaf
node.

*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int data;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  // Helper class to store information about a subtree.
  struct NodeValue {
    int minNode, maxNode, maxSize;
    NodeValue(int minNode, int maxNode, int maxSize)
        : minNode(minNode), maxNode(maxNode), maxSize(maxSize) {}
  };

  // Helper function to recursively find the largest BST subtree.
  NodeValue largestBSTSubtreeHelper(TreeNode *node) {
    // Base case: if the node is null, return a default NodeValue.
    if (!node) {
      return NodeValue(INT_MAX, INT_MIN, 0);
    }

    // Recursively get values from the left and right subtrees.
    NodeValue left = largestBSTSubtreeHelper(node->left);
    NodeValue right = largestBSTSubtreeHelper(node->right);

    // Check if the current node is a valid BST node.
    if (left.maxNode < node->data && node->data < right.minNode) {
      // Current subtree is a valid BST.
      return NodeValue(min(node->data, left.minNode),
                       max(node->data, right.maxNode),
                       left.maxSize + right.maxSize + 1);
    }

    // Current subtree is not a valid BST.
    return NodeValue(INT_MIN, INT_MAX, max(left.maxSize, right.maxSize));
  }

  int largestBST(TreeNode *root) {
    // Initialize the recursive process and return the size of the largest BST
    // subtree.
    return largestBSTSubtreeHelper(root).maxSize;
  }
};

int main() {
  // Example binary tree
  TreeNode *root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(3);

  Solution sol;
  cout << sol.largestBST(root) << endl; // Output: 3

  // Additional test case
  TreeNode *root2 = new TreeNode(10);
  root2->left = new TreeNode(5);
  root2->right = new TreeNode(15);
  root2->left->left = new TreeNode(1);
  root2->left->right = new TreeNode(8);
  root2->right->right = new TreeNode(7);

  cout << sol.largestBST(root2)
       << endl; // Output: 3 (The subtree 5-1-8 is the largest BST)

  return 0;
}

/*

Define a NodeValue class that holds three properties:
minNode: The minimum value in the current subtree.
maxNode: The maximum value in the current subtree.
maxSize: The size of the largest valid BST subtree encountered so far.

Implement a helper function largestBSTSubtreeHelper which takes the root node as
input and performs the following steps: Start with a recursive traversal of the
tree. For each node, retrieve the minNode, maxNode, and maxSize from the left
and right subtrees. If the current subtree's left maximum value is less than the
current node's value, and the right subtree's minimum value is greater than the
current node's value, it satisfies the BST property. Update the maxSize by
summing the sizes of the left and right subtrees and adding 1 for the current
node. If the current subtree does not satisfy the BST property, set the maxSize
to the maximum size found so far, and mark the current subtree as invalid by
setting minNode to INT_MIN and maxNode to INT_MAX. The function should return
the largest maxSize found across all subtrees.

*/