/*
Question:
Given a root node reference of a BST and a key, delete the node with the given
key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

1. Search for a node to remove.
2. If the node is found, delete the node.

Approach:
To delete a node with a given key from the BST, we need to search for the node
first. If the node is found, there are three possible cases:
1. The node to be deleted is a leaf node (no children).
2. The node to be deleted has only one child (left or right child).
3. The node to be deleted has both left and right children.

For the first case, we simply remove the node from the tree and return NULL as
the new root. For the second case, we return the non-NULL child of the node to
be deleted as the new root. For the third case, we find the maximum value node
in the left subtree of the node to be deleted (the rightmost node of the left
subtree), copy its value to the node to be deleted, and then recursively delete
the maximum value node in the left subtree.

Example:
Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
*/

// Time Complexity: O(log n) on average, O(n) in the worst case, where n is the
// number of nodes in the BST. The time complexity of the delete operation in a
// BST depends on the height of the tree, which is log n on average for a
// balanced BST. However, in the worst case, when the BST is skewed (all nodes
// have only one child), the time complexity becomes O(n).

// Space Complexity: O(log n) on average, O(n) in the worst case.
// The space complexity is determined by the recursion stack during the delete
// operation. In the average case, the maximum recursion depth is log n for a
// balanced BST. In the worst case, when the BST is skewed, the recursion depth
// becomes n.

// CODE:-

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    // Tree is empty
    if (root == NULL)
      return NULL;

    // Search for the node
    if (key < root->val) {
      root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
      root->right = deleteNode(root->right, key);
    } else {
      // Case 1: No left child
      if (root->left == NULL) {
        return root->right;
      }

      // Case 2: No right child
      if (root->right == NULL) {
        return root->left;
      }

      // Case 3: Two children
      // Find inorder successor (smallest in right subtree)
      TreeNode *successor = root->right;

      while (successor->left != NULL) {
        successor = successor->left;
      }

      // Copy successor value
      root->val = successor->val;

      // Delete successor node
      root->right = deleteNode(root->right, successor->val);
    }

    return root;
  }
};

/*

Great! This is the classic BST deletion example from LeetCode 450.

Input:

root = [5,3,6,2,4,null,7]
key = 3

The tree looks like this:

       5
      / \
     3   6
    / \   \
   2   4   7

We want to delete 3.

Step 1: Find the node

Start at 5.

Is 3 < 5? ✅ Yes → go left.
We found 3.
       5
      / \
    [3]  6
    / \   \
   2   4   7
Step 2: Check how many children it has

Node 3 has:

Left child = 2 ✅
Right child = 4 ✅

So this is Case 3: Node has two children.

Step 3: Find the inorder successor

The inorder successor is:

The smallest node in the right subtree.

Right subtree of 3:

    4

The smallest node is 4.

Step 4: Copy 4 into node 3

Replace 3 with 4.

       5
      / \
     4   6
    / \   \
   2   4   7

Notice there are now two 4s.

Step 5: Delete the original 4

The original 4 is a leaf, so simply remove it.

Final tree:

       5
      / \
     4   6
    /     \
   2       7
Final Answer
       5
      / \
     4   6
    /     \
   2       7
The trick you'll use every time

When deleting a node, ask these questions:

Found the node?
        │
        ▼
How many children?
        │
 ┌──────┼──────┐
 │      │      │
0      1      2
 │      │      │
Delete  Connect  Find inorder successor
leaf    child    Replace value
                 Delete successor

This flow works for every BST deletion problem.

Let's practice one

Try deleting 5 from the same tree:

       5
      / \
     3   6
    / \   \
   2   4   7

Don't worry about the code yet—just draw the resulting tree. I'll check it step
by step.

*/