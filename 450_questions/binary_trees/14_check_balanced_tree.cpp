/*
    QUESTION    : Check for Balanced Tree (Height-Balanced Binary Tree)
    Company Tags: Amazon, Microsoft, Walmart
    GfG Link    : https://practice.geeksforgeeks.org/problems/check-for-balanced-tree/1
    LeetCode    : https://leetcode.com/problems/balanced-binary-tree/
*/

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Postorder traversal returns height or -1 for early exit if unbalance detected
// S.C : O(H) - Recursion stack space
class Solution {
private:
    // Returns height of subtree if balanced, or -1 if unbalanced
    int checkHeight(Node* root) {
        if (root == nullptr) return 0;

        int lh = checkHeight(root->left);
        if (lh == -1) return -1; // Left subtree unbalanced -> propagate early exit

        int rh = checkHeight(root->right);
        if (rh == -1) return -1; // Right subtree unbalanced -> propagate early exit

        // Height difference between subtrees cannot exceed 1
        if (abs(lh - rh) > 1) {
            return -1; // Current node unbalanced
        }

        return 1 + max(lh, rh);
    }

public:
    bool isBalanced(Node *root) {
        return checkHeight(root) != -1;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF HEIGHT-BALANCE
 * ============================================================================
 *
 * Balanced (|lh - rh| <= 1 for all nodes):
 *             1
 *           /   \
 *          2     3
 *        /
 *       4
 *
 * Unbalanced (At node 1: lh = 3, rh = 0 -> |3 - 0| = 3 > 1):
 *             1
 *           /
 *          2
 *        /
 *       3
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `checkHeight(root)`:
 *     - Base `null`: return `0`.
 *     - If `lh == -1 || rh == -1 || abs(lh - rh) > 1`: return `-1`.
 *     - Return `1 + max(lh, rh)`.
 * - `isBalanced = (checkHeight(root) != -1)`.
 * - Time: O(N), Space: O(H).
 */
