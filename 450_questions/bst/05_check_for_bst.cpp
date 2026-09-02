/*
    QUESTION    : Check if a binary tree is a BST or not (Validate BST)
    Company Tags: Amazon, Microsoft, Google, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/check-for-bst/1
    LeetCode    : https://leetcode.com/problems/validate-binary-search-tree/
*/

#include <iostream>
#include <climits>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Visits each node of the tree exactly once
// S.C : O(H) - Recursion stack space (H = height of tree)
class Solution {
private:
    // Helper function enforcing (minAllowed < node->data < maxAllowed) using long long to avoid overflow
    bool validate(Node* root, long long minAllowed, long long maxAllowed) {
        if (root == nullptr) return true;

        // Current node's value must be strictly within bounds
        if (root->data <= minAllowed || root->data >= maxAllowed) {
            return false;
        }

        // Left child must be in (minAllowed, root->data)
        // Right child must be in (root->data, maxAllowed)
        return validate(root->left, minAllowed, root->data) &&
               validate(root->right, root->data, maxAllowed);
    }

public:
    bool isBST(Node* root) {
        return validate(root, LLONG_MIN, LLONG_MAX);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF VALIDATION RANGE PROPAGATION
 * ============================================================================
 *
 *               10  (-inf, +inf)
 *             /    \
 * (-inf, 10) 5      15  (10, +inf)
 *           / \    /  \
 * (-inf, 5)1   8  12   20 (15, +inf)
 *           (5,10) (10,15)
 *
 * Invalid Case (Node 6 under 15 violates 10 < node):
 *               10
 *             /    \
 *            5      15
 *                  /
 *                 6  <- Invalid! 6 is NOT > 10.
 *
 * ============================================================================
 * DRY RUN (Root = 10, left = 5, right = 15)
 * ============================================================================
 * | Node | (minAllowed, maxAllowed) | Check Condition | Status |
 * | :--- | :----------------------- | :-------------- | :----- |
 * | 10   | (-inf, +inf)             | -inf < 10 < +inf| Valid  |
 * | 5    | (-inf, 10)               | -inf < 5 < 10   | Valid  |
 * | 15   | (10, +inf)               | 10 < 15 < +inf  | Valid  |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Strict Border Control"
 * It's not enough to check `root->left < root`.
 * Every node inherits an absolute global min and max ceiling from all its ancestors above.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `validate(root, minVal, maxVal)`.
 * - If `root == nullptr`, return `true`.
 * - If `root->data <= minVal || root->data >= maxVal`, return `false`.
 * - Recurse: `validate(left, minVal, root->data) && validate(right, root->data, maxVal)`.
 * - Time: O(N), Space: O(H).
 */
