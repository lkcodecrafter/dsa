/*
    QUESTION    : Construct Binary Tree from Inorder and Preorder Traversal
    Company Tags: Amazon, Microsoft, Accolite
    GfG Link    : https://practice.geeksforgeeks.org/problems/construct-tree-1/1
    LeetCode    : https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Fast O(1) hash map lookup for root position in inorder array
// S.C : O(N) - Hash map storing element indices
class Solution {
private:
    unordered_map<int, int> inMap;

    Node* build(int in[], int pre[], int &preIdx, int inStart, int inEnd) {
        if (inStart > inEnd) return nullptr;

        // Current root is preorder[preIdx]
        int rootVal = pre[preIdx++];
        Node* root = new Node(rootVal);

        // Find index of rootVal in inorder array
        int inIndex = inMap[rootVal];

        // Construct left subtree with inorder range [inStart, inIndex - 1]
        root->left = build(in, pre, preIdx, inStart, inIndex - 1);

        // Construct right subtree with inorder range [inIndex + 1, inEnd]
        root->right = build(in, pre, preIdx, inIndex + 1, inEnd);

        return root;
    }

public:
    Node* buildTree(int in[], int pre[], int n) {
        inMap.clear();
        for (int i = 0; i < n; i++) {
            inMap[in[i]] = i;
        }

        int preIdx = 0;
        return build(in, pre, preIdx, 0, n - 1);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF INORDER-PREORDER PARTITIONING
 * ============================================================================
 *
 * Preorder: [ 3, 9, 20, 15, 7 ] (Root = 3)
 * Inorder : [ 9, 3, 15, 20, 7 ]
 *
 * At Root 3:
 * - Left Subtree Inorder:  [ 9 ]
 * - Right Subtree Inorder: [ 15, 20, 7 ]
 *
 * Constructed Tree:
 *          3
 *        /   \
 *       9     20
 *            /  \
 *           15   7
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Build `inMap[in[i]] = i` for $O(1)$ index lookup.
 * - `root = new Node(pre[preIdx++])`.
 * - `inIndex = inMap[root->data]`.
 * - `root->left = build(inStart, inIndex - 1)`.
 * - `root->right = build(inIndex + 1, inEnd)`.
 * - Time: O(N), Space: O(N).
 */
