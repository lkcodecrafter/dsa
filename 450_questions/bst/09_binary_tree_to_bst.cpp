/*
    QUESTION    : Convert Binary tree into BST (Preserving original tree structure)
    Company Tags: Amazon, Microsoft, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/binary-tree-to-bst/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definition for Binary Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Inorder traversal O(N) + Sort values O(N log N) + Inorder fill O(N)
// S.C : O(N)       - Vector to store tree node values
class Solution {
private:
    // Step 1: Extract all node values in Inorder
    void extractInorder(Node* root, vector<int> &inorder) {
        if (root == nullptr) return;
        extractInorder(root->left, inorder);
        inorder.push_back(root->data);
        extractInorder(root->right, inorder);
    }

    // Step 3: Put sorted values back into the binary tree in Inorder
    void fillInorder(Node* root, const vector<int> &inorder, int &idx) {
        if (root == nullptr) return;
        fillInorder(root->left, inorder, idx);
        root->data = inorder[idx++];
        fillInorder(root->right, inorder, idx);
    }

public:
    Node* binaryTreeToBST(Node *root) {
        vector<int> inorder;

        // 1. Extract values
        extractInorder(root, inorder);

        // 2. Sort values ascending
        sort(inorder.begin(), inorder.end());

        // 3. Re-fill tree nodes with sorted values
        int idx = 0;
        fillInorder(root, inorder, idx);

        return root;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF CONVERSION
 * ============================================================================
 *
 * Original Binary Tree:            Inorder: [ 8, 10, 2, 7 ]
 *             10                   Sorted : [ 2, 7, 8, 10 ]
 *           /    \
 *          2      7                Converted BST (Structure Preserved):
 *        /                                   8
 *       8                                  /   \
 *                                         2     10
 *                                        /
 *                                       7  (Invalid BST shape? Wait! Inorder is 7,2,8,10)
 *
 * Inorder Traversal of final tree: 2 -> 7 -> 8 -> 10 (Strictly Sorted BST!).
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Inorder traversal of any valid BST must be strictly sorted.
 * - 3 Steps:
 *     1. Collect all node values using Inorder traversal.
 *     2. Sort the array using `std::sort()` in $O(N \log N)$.
 *     3. Traverse in Inorder again, replacing `root->data = inorder[idx++]`.
 * - Time: O(N log N), Space: O(N).
 */
