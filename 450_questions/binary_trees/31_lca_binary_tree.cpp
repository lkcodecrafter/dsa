/*
    QUESTION    : Lowest Common Ancestor in a Binary Tree
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/lowest-common-ancestor-in-a-binary-tree/1
    LeetCode    : https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
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
// T.C : O(N) - Postorder traversal visits each node once
// S.C : O(H) - Recursion stack space
class Solution {
public:
    Node* lca(Node* root, int n1, int n2) {
        // Base Case: If root is null, or matches either n1 or n2
        if (root == nullptr || root->data == n1 || root->data == n2) {
            return root;
        }

        // Search left and right subtrees
        Node* leftSearch = lca(root->left, n1, n2);
        Node* rightSearch = lca(root->right, n1, n2);

        // If both subtrees returned non-null, current root is the LCA
        if (leftSearch != nullptr && rightSearch != nullptr) {
            return root;
        }

        // Otherwise return whichever subtree found a target node
        return (leftSearch != nullptr) ? leftSearch : rightSearch;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BINARY TREE LCA
 * ============================================================================
 *
 *               3
 *             /   \
 *            5     1
 *          /  \   / \
 *         6    2 0   8
 *             / \
 *            7   4
 *
 * LCA(5, 1) = 3 (Left returned 5, Right returned 1 -> Root 3 is LCA)
 * LCA(5, 4) = 5 (Left returned 5, Right of 5 returned 4 -> Node 5 is LCA)
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `if (root == nullptr || root->data == n1 || root->data == n2) return root;`
 * - `left = lca(root->left, n1, n2); right = lca(root->right, n1, n2);`
 * - `if (left && right) return root;`
 * - `return left ? left : right;`
 * - Time: O(N), Space: O(H).
 */
