#include<iostream>
#include<vector>
using namespace std;

#ifndef TREE_NODE_DECLARED
#define TREE_NODE_DECLARED
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#endif

/*
 * Problem: Validate Binary Search Tree (LeetCode 98)
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 *
 * Pattern: Binary Tree / DFS Recursion / BST Properties
 *
 * Complexity:
 * - Time Complexity: O(N) where N is the number of nodes in the binary tree. We visit each node exactly once.
 * - Space Complexity: O(H) recursion stack space where H is the height of the tree. In the worst case (skewed tree), H = N.
 *
 * Visualizations:
 * Valid range constraints for BST nodes:
 *
 *                     10  [Range: -∞ to +∞]
 *                    /  \
 *                   /    \
 *                  5      15  [Range: 10 to +∞]
 *          [Range: -∞ to 10]
 *                /   \
 *               3     7
 *      [Range: -∞ to 5] [Range: 5 to 10]
 *
 * Memorization Hook:
 * "isValid(node, min_val, max_val). Empty tree is valid. 
 * Node's value must be strictly between min_val and max_val. 
 * Recurse left with max updated to current; recurse right with min updated to current."
 *
 * 1-Minute Quick Revision:
 * 1. Implement a helper function `isValid(node, min_val, max_val)` using `long long` (LLONG_MIN/LLONG_MAX) to prevent overflow.
 * 2. Base case: If `node` is nullptr, return `true`.
 * 3. Range check: If `node->val <= min_val` or `node->val >= max_val`, return `false`.
 * 4. Recursive case: Check left subtree with updated max constraint `isValid(node->left, min_val, node->val)`.
 * 5. Check right subtree with updated min constraint `isValid(node->right, node->val, max_val)`.
 * 6. Return `left_subtree_is_valid && right_subtree_is_valid`.
 *
 * Dry Run:
 * Tree: 10 / \ 5 15 / \ 3 7 (where 10 is root, 5 and 15 are left and right child, 3 and 7 are children of 5)
 *
 * | Step / DFS Call        | Node | Current Range [min, max]          | Condition: node->val <= min or >= max | Left DFS Recursive Call             | Right DFS Recursive Call            | Result |
 * |------------------------|------|-----------------------------------|---------------------------------------|-------------------------------------|-------------------------------------|--------|
 * | isValid(root, -∞, +∞)  | 10   | [LLONG_MIN, LLONG_MAX]            | 10 <= -∞ or >= +∞ (false)             | isValid(5, LLONG_MIN, 10)           | isValid(15, 10, LLONG_MAX)          | true   |
 * | isValid(left, -∞, 10)  | 5    | [LLONG_MIN, 10]                   | 5 <= -∞ or >= 10 (false)              | isValid(3, LLONG_MIN, 5)            | isValid(7, 5, 10)                   | true   |
 * | isValid(left, -∞, 5)   | 3    | [LLONG_MIN, 5]                    | 3 <= -∞ or >= 5 (false)               | isValid(nullptr, LLONG_MIN, 3)->true| isValid(nullptr, 3, 5)->true        | true   |
 * | isValid(right, 5, 10)  | 7    | [5, 10]                           | 7 <= 5 or >= 10 (false)               | isValid(nullptr, 5, 7)->true        | isValid(nullptr, 7, 10)->true       | true   |
 * | isValid(right, 10, +∞) | 15   | [10, LLONG_MAX]                   | 15 <= 10 or >= +∞ (false)             | isValid(nullptr, 10, 15)->true      | isValid(nullptr, 15, LLONG_MAX)->true| true   |
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        // Use LLONG_MIN and LLONG_MAX to handle edge cases where nodes contain INT_MIN or INT_MAX
        return isValid(root, LLONG_MIN, LLONG_MAX);
    }

private:
    bool isValid(TreeNode* root, long long minVal, long long maxVal) {
        // Base case: An empty tree or node is a valid BST
        if (root == nullptr) {
            return true;
        }
        
        // The current node's value must sit strictly within the allowed range [minVal, maxVal]
        if (root->val <= minVal || root->val >= maxVal) {
            return false;
        }
        
        // Recurse left (updating maxVal) and right (updating minVal)
        return isValid(root->left, minVal, root->val) 
            && isValid(root->right, root->val, maxVal);
    }
};