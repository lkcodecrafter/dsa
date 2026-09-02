/*
    QUESTION    : Convert Binary tree into Sum tree (Transform to Sum Tree)
    Company Tags: Amazon, Microsoft, Snapdeal
    GfG Link    : https://practice.geeksforgeeks.org/problems/transform-to-sum-tree/1
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Postorder traversal updates node values to sum of subtrees
// S.C : O(H) - Recursion stack space
class Solution {
private:
    int toSumTreeUtil(Node* root) {
        if (root == nullptr) return 0;

        int oldVal = root->data;

        // Recursively compute sums of left and right subtrees
        int leftSum = toSumTreeUtil(root->left);
        int rightSum = toSumTreeUtil(root->right);

        // Update current node's value to sum of values in its subtrees
        root->data = leftSum + rightSum;

        // Return total sum of subtree rooted at this node (new data + old data)
        return root->data + oldVal;
    }

public:
    void toSumTree(Node *node) {
        toSumTreeUtil(node);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TRANSFORMATION TO SUM TREE
 * ============================================================================
 *
 * Given Tree:                     Transformed Sum Tree:
 *             10                                  20 (4-2+8-4+6+8)
 *           /    \                               /    \
 *         -2      6                            4        14
 *        /  \    / \                         /  \      /  \
 *       8   -4  7   5                       0    0    0    0
 *
 * Leaf nodes become 0!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `oldVal = root->data`.
 * - `leftSum = util(root->left); rightSum = util(root->right);`.
 * - `root->data = leftSum + rightSum;`.
 * - `return root->data + oldVal;`.
 * - Time: O(N), Space: O(H).
 */
