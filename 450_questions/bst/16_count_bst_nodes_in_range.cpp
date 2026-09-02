/*
    QUESTION    : Count BST nodes that lie in a given range [l, h]
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/count-bst-nodes-that-lie-in-a-given-range/1
    LeetCode    : https://leetcode.com/problems/range-sum-of-bst/
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
// T.C : O(K + H) where K is number of nodes in range and H is height of BST (Pruned search)
// S.C : O(H)     - Recursion stack space
class Solution {
public:
    int getCount(Node *root, int l, int h) {
        if (root == nullptr) return 0;

        // Case 1: Current node is strictly within [l, h]
        if (root->data >= l && root->data <= h) {
            return 1 + getCount(root->left, l, h) + getCount(root->right, l, h);
        }
        // Case 2: Current node is smaller than l -> All left subtree nodes are also < l (Prune left)
        else if (root->data < l) {
            return getCount(root->right, l, h);
        }
        // Case 3: Current node is greater than h -> All right subtree nodes are also > h (Prune right)
        else {
            return getCount(root->left, l, h);
        }
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF PRUNED RANGE SEARCH
 * ============================================================================
 *
 * Range [5, 45]:
 *
 *               10  (In range: count 1, check both)
 *             /    \
 *            5      50  (50 > 45: PRUNE right subtree, check only left!)
 *           / \     /
 *          1   40  40
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `root->data < l`: skip left subtree, search `getCount(root->right, l, h)`.
 * - If `root->data > h`: skip right subtree, search `getCount(root->left, l, h)`.
 * - If `root->data >= l && root->data <= h`: `1 + left + right`.
 * - Time: O(K + H), Space: O(H).
 */
