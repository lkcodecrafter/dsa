/*
    QUESTION    : Construct BST from preorder traversal
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/construct-bst-from-given-preorder-traversa/
    LeetCode    : https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Uses upper bound range to construct BST in a single linear pass
// S.C : O(H) - Recursion stack space (H <= N)
class Solution {
private:
    TreeNode* buildBST(const vector<int> &preorder, int &idx, int bound) {
        // Base Condition: Index out of bounds or current element exceeds upper bound
        if (idx >= preorder.size() || preorder[idx] > bound) {
            return nullptr;
        }

        // Create current root from preorder
        TreeNode* root = new TreeNode(preorder[idx++]);

        // Left child's upper bound is current root's value
        root->left = buildBST(preorder, idx, root->val);

        // Right child's upper bound remains the parent's upper bound
        root->right = buildBST(preorder, idx, bound);

        return root;
    }

public:
    TreeNode* bstFromPreorder(vector<int> &preorder) {
        int idx = 0;
        return buildBST(preorder, idx, INT_MAX);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF UPPER-BOUND BST RECONSTRUCTION
 * ============================================================================
 *
 * Preorder: [ 8, 5, 1, 7, 10, 12 ]
 *
 * 1. Root = 8 (bound = INT_MAX)
 * 2. Left child of 8 -> sees 5 (5 < 8) -> Node(5) (bound = 8)
 *    - Left child of 5 -> sees 1 (1 < 5) -> Node(1) (bound = 5)
 *      - Left of 1: 7 > 1 -> null
 *      - Right of 1: 7 > 5 -> null
 *    - Right child of 5: sees 7 (7 < 8) -> Node(7) (bound = 8)
 * 3. Right child of 8 -> sees 10 (10 < INT_MAX) -> Node(10) (bound = INT_MAX)
 *    - Right child of 10 -> sees 12 (12 < INT_MAX) -> Node(12)
 *
 * Constructed BST:
 *             8
 *           /   \
 *          5     10
 *        /  \      \
 *       1    7      12
 *
 * ============================================================================
 * DRY RUN (preorder = {8, 5, 1})
 * ============================================================================
 * | Call Frame | idx | preorder[idx] | Upper Bound | Created Node | Returned Node |
 * | :--------- | :-- | :------------ | :---------- | :----------- | :------------ |
 * | 1          | 0   | 8             | INT_MAX     | Node(8)      | Root          |
 * | 2 (Left 8) | 1   | 5             | 8           | Node(5)      | 8->left       |
 * | 3 (Left 5) | 2   | 1             | 5           | Node(1)      | 5->left       |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Upper Ceiling Pass"
 * Preorder visits root first. As you step down left, the ceiling is `root->val`.
 * If an incoming number punches through the ceiling (`preorder[idx] > bound`),
 * it belongs to an ancestor's right subtree!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Linear $O(N)$ approach: track a single `bound` parameter initialized to `INT_MAX`.
 * - If `idx >= n || preorder[idx] > bound`: return `nullptr`.
 * - `root = new TreeNode(preorder[idx++])`.
 * - `root->left = buildBST(preorder, idx, root->val)`.
 * - `root->right = buildBST(preorder, idx, bound)`.
 * - Time: O(N), Space: O(H).
 */
