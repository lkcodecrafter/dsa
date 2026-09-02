/*
    QUESTION    : Convert a normal BST into a Balanced BST
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/convert-normal-bst-balanced-bst/
    LeetCode    : https://leetcode.com/problems/balance-a-binary-search-tree/
*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Inorder traversal O(N) + Divide & Conquer binary construction O(N)
// S.C : O(N) - Vector to store sorted inorder nodes
class Solution {
private:
    void getInorder(Node* root, vector<int> &inorder) {
        if (root == nullptr) return;
        getInorder(root->left, inorder);
        inorder.push_back(root->data);
        getInorder(root->right, inorder);
    }

    // Constructs height-balanced BST from sorted array in O(N)
    Node* buildBalancedBST(const vector<int> &inorder, int start, int end) {
        if (start > end) return nullptr;

        // Choose middle element as root to ensure equal height in left and right subtrees
        int mid = start + (end - start) / 2;
        Node* root = new Node(inorder[mid]);

        root->left = buildBalancedBST(inorder, start, mid - 1);
        root->right = buildBalancedBST(inorder, mid + 1, end);

        return root;
    }

public:
    Node* buildBalancedTree(Node* root) {
        vector<int> inorder;

        // 1. Extract sorted elements
        getInorder(root, inorder);

        // 2. Recursively build balanced tree picking mid element as root
        return buildBalancedBST(inorder, 0, inorder.size() - 1);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BALANCING A SKEWED BST
 * ============================================================================
 *
 * Skewed BST (Linked list shape):
 *       4
 *        \
 *         3
 *          \
 *           2
 *            \
 *             1
 *
 * Sorted Inorder: [ 1, 2, 3, 4 ]
 *
 * Balanced BST:
 *           2 (mid)
 *         /   \
 *        1     3
 *               \
 *                4
 *
 * Height reduced from O(N) to O(log N)!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Store Inorder of skewed BST into a vector `inorder`.
 * - Build Balanced BST using `mid = (start + end) / 2`:
 *     - `root = new Node(inorder[mid])`.
 *     - `root->left = build(start, mid - 1)`.
 *     - `root->right = build(mid + 1, end)`.
 * - Time: O(N), Space: O(N).
 */
