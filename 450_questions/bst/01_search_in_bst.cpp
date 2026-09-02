/*
    QUESTION    : Find a value in a BST (Search in BST)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
    LeetCode    : https://leetcode.com/problems/search-in-a-binary-search-tree/
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(H) where H is height of BST (O(log N) for balanced BST, O(N) worst case)
// S.C : O(1) iterative (or O(H) recursive stack)
class Solution {
public:
    // Iterative search in BST for O(1) auxiliary space
    TreeNode* searchBST(TreeNode* root, int val) {
        TreeNode* curr = root;

        while (curr != nullptr) {
            if (curr->val == val) {
                return curr; // Value found
            } else if (val < curr->val) {
                curr = curr->left; // Value is smaller -> search left subtree
            } else {
                curr = curr->right; // Value is greater -> search right subtree
            }
        }

        return nullptr; // Value not present in BST
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BST SEARCH
 * ============================================================================
 *
 * Target val = 2:
 *
 *             4  <- 2 < 4: Go Left!
 *           /   \
 *          2     7  <- Found 2! Return node.
 *        /   \
 *       1     3
 *
 * ============================================================================
 * DRY RUN (val = 2)
 * ============================================================================
 * | Step | curr Node Value | Comparison (val vs curr->val) | Action / Next Step |
 * | :--- | :-------------- | :---------------------------- | :----------------- |
 * | 1    | 4               | 2 < 4                         | curr = curr->left  |
 * | 2    | 2               | 2 == 2                        | Return curr (Node 2)|
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Highway Fork"
 * Smaller numbers always exit left; larger numbers always exit right.
 * Never check both branches simultaneously.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - While `curr != nullptr`:
 *     - If `curr->val == val`: return `curr`.
 *     - If `val < curr->val`: `curr = curr->left`.
 *     - Else: `curr = curr->right`.
 * - Return `nullptr` if not found.
 * - Time: O(H), Space: O(1).
 */
