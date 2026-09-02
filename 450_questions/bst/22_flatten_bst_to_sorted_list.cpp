/*
    QUESTION    : Flatten BST to sorted list (Increasing Order Search Tree)
    Company Tags: Amazon, Adobe
    GfG Link    : https://www.geeksforgeeks.org/flatten-bst-to-sorted-list-increasing-order/
    LeetCode    : https://leetcode.com/problems/increasing-order-search-tree/
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
// T.C : O(N) - Inorder traversal visits each node once
// S.C : O(H) - Recursion stack space (In-place pointer rewiring)
class Solution {
private:
    Node* prev = nullptr;
    Node* newHead = nullptr;

    void inorder(Node* curr) {
        if (curr == nullptr) return;

        // 1. Visit left subtree
        inorder(curr->left);

        // 2. Process current node
        if (newHead == nullptr) {
            newHead = curr; // First node visited in inorder becomes the new head
        } else {
            prev->right = curr; // Link previous node to current node
            prev->left = nullptr; // Clear left pointer
        }

        prev = curr;

        // 3. Visit right subtree
        inorder(curr->right);
    }

public:
    Node* flatten(Node* root) {
        prev = nullptr;
        newHead = nullptr;

        inorder(root);

        if (prev != nullptr) {
            prev->left = nullptr;
            prev->right = nullptr;
        }

        return newHead;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF FLATTENING BST TO SKEWED LIST
 * ============================================================================
 *
 * Given BST:
 *             5
 *           /   \
 *          3     7
 *        /  \   /  \
 *       2    4 6    8
 *
 * Flattened Increasing List:
 *   2
 *    \
 *     3
 *      \
 *       4
 *        \
 *         5
 *          \
 *           6
 *            \
 *             7
 *              \
 *               8
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Maintain `prev` and `newHead`.
 * - In Inorder traversal (`curr`):
 *     - If `newHead == nullptr`: `newHead = curr`.
 *     - Else: `prev->right = curr; prev->left = nullptr;`.
 *     - `prev = curr`.
 * - At end: `prev->left = nullptr; prev->right = nullptr;`.
 * - Time: O(N), Space: O(H).
 */
