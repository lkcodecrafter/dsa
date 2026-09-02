/*
    QUESTION    : Create a mirror tree from the given binary tree (Invert Binary Tree)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://www.geeksforgeeks.org/create-a-mirror-tree-from-the-given-binary-tree/
    LeetCode    : https://leetcode.com/problems/invert-binary-tree/
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
// T.C : O(N) - Visits each node once and swaps its left and right child pointers
// S.C : O(H) - Recursion stack space
class Solution {
public:
    void mirror(Node* node) {
        if (node == nullptr) return;

        // 1. Swap left and right child pointers of current node
        swap(node->left, node->right);

        // 2. Recursively mirror the left and right subtrees
        mirror(node->left);
        mirror(node->right);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TREE INVERSION / MIRROR
 * ============================================================================
 *
 * Original Tree:                 Mirror Tree:
 *          1                            1
 *        /   \                        /   \
 *       2     3          --->        3     2
 *     /   \                              /   \
 *    4     5                            5     4
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `if (node == nullptr) return;`
 * - `swap(node->left, node->right);`
 * - `mirror(node->left); mirror(node->right);`
 * - Time: O(N), Space: O(H).
 */
