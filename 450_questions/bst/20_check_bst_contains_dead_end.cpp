/*
    QUESTION    : Check whether BST contains Dead End (No new node can be inserted)
    Company Tags: Amazon, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/check-whether-bst-contains-dead-end/1
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
// T.C : O(N) - Visits each node once with its valid insertion interval [minVal, maxVal]
// S.C : O(H) - Recursion stack space (H = height of tree)
class Solution {
private:
    bool solve(Node* root, int minVal, int maxVal) {
        if (root == nullptr) return false;

        // A dead end occurs at a LEAF node where the allowable range [minVal, maxVal] has collapsed to minVal == maxVal
        if (root->left == nullptr && root->right == nullptr) {
            if (minVal == maxVal) {
                return true; // Dead end found!
            }
            return false;
        }

        // Check recursively for left subtree in range [minVal, root->data - 1]
        // and right subtree in range [root->data + 1, maxVal]
        return solve(root->left, minVal, root->data - 1) ||
               solve(root->right, root->data + 1, maxVal);
    }

public:
    bool isDeadEnd(Node *root) {
        // Values in BST are positive integers >= 1, so minimum possible value is 1
        return solve(root, 1, 1e9);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF DEAD END RANGE COLLAPSE
 * ============================================================================
 *
 *               8  [1, inf]
 *             /   \
 *   [1, 7]   5     11  [9, inf]
 *          /  \
 *  [1, 4] 2    7  [6, 7]
 *        /
 *       1  [1, 1]  <-- DEAD END! (minVal == maxVal == 1, no number < 1 allowed)
 *
 * Notice Leaf 1 has range [1, 1]. Neither left child (< 1) nor right child (> 1 and < 2) is possible.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Minimum allowed BST value is $1$. Initial range: `[1, 1e9]`.
 * - For node with value `x`:
 *     - Left subtree allowable range: `[minVal, x - 1]`.
 *     - Right subtree allowable range: `[x + 1, maxVal]`.
 * - If at any leaf node `minVal == maxVal`, return `true` (Dead end exists).
 * - Time: O(N), Space: O(H).
 */
