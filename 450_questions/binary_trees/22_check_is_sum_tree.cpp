/*
    QUESTION    : Check if Binary Tree is Sum Tree or not
    Company Tags: Amazon, Microsoft, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/sum-tree/1
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
// T.C : O(N) - Postorder traversal returns subtree sum or -1 if condition violated
// S.C : O(H) - Recursion stack space
class Solution {
private:
    // Returns sum of subtree if valid Sum Tree, or -1 if invalid
    int checkSumTree(Node* root) {
        if (root == nullptr) return 0;

        // Leaf node is inherently a valid Sum Tree; return its value
        if (root->left == nullptr && root->right == nullptr) {
            return root->data;
        }

        int leftSum = checkSumTree(root->left);
        if (leftSum == -1) return -1;

        int rightSum = checkSumTree(root->right);
        if (rightSum == -1) return -1;

        // Current node's data must equal the sum of its left and right subtrees
        if (root->data != leftSum + rightSum) {
            return -1; // Violation!
        }

        // Return total sum of subtree rooted at this node (root->data + subtrees)
        return root->data + leftSum + rightSum;
    }

public:
    bool isSumTree(Node* root) {
        return checkSumTree(root) != -1;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF SUM TREE
 * ============================================================================
 *
 *               26  (10 + 3 + 4 + 6 + 3 = 26)
 *             /    \
 *            10     3
 *           /  \     \
 *          4    6     3
 *
 * Left Subtree sum = 4 + 6 = 10 (Matches node 10!)
 * Right Subtree sum = 3 (Matches node 3!)
 * Total = 10 + 10 + 3 + 3 = 26 (Matches root 26!) -> Valid Sum Tree!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Base `null` $\rightarrow$ 0, Base `leaf` $\rightarrow$ `root->data`.
 * - If `leftSum == -1 || rightSum == -1 || root->data != leftSum + rightSum`: return `-1`.
 * - Else return `root->data + leftSum + rightSum`.
 * - Time: O(N), Space: O(H).
 */
