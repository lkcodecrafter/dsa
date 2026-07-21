/*
Question:
You are given the root of a binary search tree (BST), where the values of
exactly two nodes of the tree were swapped by mistake. Recover the tree without
changing its structure.

Explanation:
- We perform an in-order traversal of the BST to find the two nodes that are
swapped.
- During the in-order traversal, we keep track of the previous node and compare
it with the current node. If the current node is less than the previous node,
then we have found the two swapped nodes.
- We swap the values of the two nodes to recover the BST.

Time Complexity:
- The in-order traversal takes O(n) time, where n is the number of nodes in the
BST.

Space Complexity:
- The space complexity is O(h), where h is the height of the BST, as the
recursion stack stores the nodes in the leftmost path of the BST.

*/

class Solution {
private:
  TreeNode *first = nullptr;
  TreeNode *second = nullptr;
  TreeNode *prev = nullptr;

  void inorder(TreeNode *root) {
    if (root == nullptr)
      return;

    inorder(root->left);

    // Violation found
    if (prev != nullptr && prev->val > root->val) {
      if (first == nullptr)
        first = prev;

      second = root;
    }

    prev = root;

    inorder(root->right);
  }

public:
  void recoverTree(TreeNode *root) {
    inorder(root);

    swap(first->val, second->val);
  }
};
