/*
    QUESTION    : Boundary Traversal of Binary Tree
    Company Tags: Amazon, Microsoft, Flipkart, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/boundary-traversal-of-binary-tree/1
    LeetCode    : https://leetcode.com/problems/boundary-of-binary-tree/
*/

#include <iostream>
#include <vector>
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
// T.C : O(N) - Traversing left boundary O(H) + leaf nodes O(N) + right boundary O(H)
// S.C : O(H) - Recursion stack space
class Solution {
private:
    bool isLeaf(Node* node) {
        return node->left == nullptr && node->right == nullptr;
    }

    // 1. Traverse Left Boundary (excluding leaves) top-down
    void addLeftBoundary(Node* root, vector<int> &res) {
        Node* curr = root->left;
        while (curr != nullptr) {
            if (!isLeaf(curr)) res.push_back(curr->data);
            if (curr->left != nullptr) curr = curr->left;
            else curr = curr->right;
        }
    }

    // 2. Traverse all Leaf Nodes left-to-right
    void addLeaves(Node* root, vector<int> &res) {
        if (root == nullptr) return;
        if (isLeaf(root)) {
            res.push_back(root->data);
            return;
        }
        addLeaves(root->left, res);
        addLeaves(root->right, res);
    }

    // 3. Traverse Right Boundary (excluding leaves) bottom-up
    void addRightBoundary(Node* root, vector<int> &res) {
        Node* curr = root->right;
        vector<int> temp;
        while (curr != nullptr) {
            if (!isLeaf(curr)) temp.push_back(curr->data);
            if (curr->right != nullptr) curr = curr->right;
            else curr = curr->left;
        }
        // Reverse to get bottom-up order
        for (int i = temp.size() - 1; i >= 0; i--) {
            res.push_back(temp[i]);
        }
    }

public:
    vector<int> boundary(Node *root) {
        vector<int> res;
        if (root == nullptr) return res;

        // Add root node if it's not a leaf
        if (!isLeaf(root)) {
            res.push_back(root->data);
        }

        addLeftBoundary(root, res);
        addLeaves(root, res);
        addRightBoundary(root, res);

        return res;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 3-PART BOUNDARY WALK
 * ============================================================================
 *
 *               1  [Root: 1]
 *             /   \
 *   [Left]   2     3  [Right]
 *          /  \     \
 * [Leaves]4    5     6 [Leaves]
 *
 * Traversal:
 * 1. Root: 1
 * 2. Left Boundary: 2
 * 3. Leaves: 4, 5, 6
 * 4. Right Boundary (bottom-up): 3
 *
 * Boundary: [ 1, 2, 4, 5, 6, 3 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - 4 distinct parts:
 *     1. Root node (if not leaf).
 *     2. Left boundary (top-down, non-leaf nodes).
 *     3. Leaf nodes (inorder sweep from left to right).
 *     4. Right boundary (bottom-up, non-leaf nodes via stack/reversal).
 * - Time: O(N), Space: O(H).
 */
