/*
    QUESTION    : Kth Ancestor of node in a Binary Tree
    Company Tags: Amazon, Flipkart
    GfG Link    : https://www.geeksforgeeks.org/kth-ancestor-node-binary-tree-set-2/
    LeetCode    : https://leetcode.com/problems/kth-ancestor-of-a-tree-node/
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
// T.C : O(N) - Bottom-up backtracking decrements K until K == 0
// S.C : O(H) - Recursion stack space
class Solution {
private:
    Node* solve(Node* root, int &k, int node) {
        if (root == nullptr) return nullptr;

        // Target node found
        if (root->data == node) {
            return root;
        }

        Node* left = solve(root->left, k, node);
        Node* right = solve(root->right, k, node);

        // If target node is present in either subtree, step up to ancestor
        if (left != nullptr || right != nullptr) {
            k--;
            if (k == 0) {
                // When k reaches 0, current root is the Kth ancestor!
                return root;
            }
            // Return non-null node to continue stepping up ancestors
            return (left != nullptr) ? left : right;
        }

        return nullptr;
    }

public:
    int kthAncestor(Node *root, int k, int node) {
        Node* ans = solve(root, k, node);

        // If ans is root of entire tree and k > 0, kth ancestor does not exist
        if (ans == nullptr || ans->data == node) {
            return -1;
        }

        return ans->data;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BOTTOM-UP ANCESTOR COUNTDOWN
 * ============================================================================
 *
 *               1
 *             /   \
 *            2     3
 *          /  \
 *         4    5
 *
 * Find 2nd Ancestor (k = 2) of node 4:
 * 1. At 4: matches node 4 -> return Node(4)
 * 2. At 2: receives Node(4) -> k decrements to 1 -> returns Node(4)
 * 3. At 1: receives Node(4) -> k decrements to 0! -> k == 0 -> returns Node(1)
 *
 * 2nd Ancestor of 4 = 1.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `solve(root, k, node)`:
 *     - If `root == nullptr || root->data == node`: return `root`.
 *     - If `left || right`: `k--; if (k == 0) return root; return left ? left : right;`.
 * - If result is `nullptr` or matches `node`: return `-1`.
 * - Time: O(N), Space: O(H).
 */
