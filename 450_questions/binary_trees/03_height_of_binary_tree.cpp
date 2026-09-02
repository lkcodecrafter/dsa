/*
    QUESTION    : Height of a Binary Tree (Maximum Depth)
    Company Tags: Amazon, Microsoft, VMWare
    GfG Link    : https://practice.geeksforgeeks.org/problems/height-of-binary-tree/1
    LeetCode    : https://leetcode.com/problems/maximum-depth-of-binary-tree/
*/

#include <iostream>
#include <algorithm>

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
// S.C : O(H) - Recursion stack space (H = height of tree)
class Solution {
public:
    int height(struct Node* node) {
        // Base Condition: Height of empty tree is 0
        if (node == nullptr) {
            return 0;
        }

        // Compute height of left and right subtrees
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        // Current height is 1 + max of both subtrees
        return 1 + max(leftHeight, rightHeight);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF HEIGHT COMPUTATION
 * ============================================================================
 *
 *               1  [height = 1 + max(2, 1) = 3]
 *             /   \
 *   [h=2]    2     3 [h=1]
 *          /
 *  [h=1]  4
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `if (node == nullptr) return 0;`
 * - `return 1 + max(height(node->left), height(node->right));`
 * - Time: O(N), Space: O(H).
 */
