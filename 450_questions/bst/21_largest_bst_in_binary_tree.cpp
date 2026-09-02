/*
    QUESTION    : Largest BST in a Binary Tree (Find size of largest subtree that is a valid BST)
    Company Tags: Amazon, Microsoft, Samsung, D-E-Shaw
    GfG Link    : https://practice.geeksforgeeks.org/problems/largest-bst/1
    LeetCode    : https://leetcode.com/problems/largest-bst-subtree/
*/

#include <iostream>
#include <climits>
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
// T.C : O(N) - Postorder bottom-up traversal passes subtree validation stats in O(1) per node
// S.C : O(H) - Recursion stack space (H = height of tree)
struct NodeInfo {
    bool isBST;
    int size;
    int minVal;
    int maxVal;
};

class Solution {
private:
    int maxBSTSize = 0;

    NodeInfo postorder(Node* root) {
        // Base Case: Empty subtree is a valid BST of size 0
        if (root == nullptr) {
            return {true, 0, INT_MAX, INT_MIN};
        }

        // Postorder traversal: compute information for left and right subtrees first
        NodeInfo leftInfo = postorder(root->left);
        NodeInfo rightInfo = postorder(root->right);

        NodeInfo curr;
        curr.size = leftInfo.size + rightInfo.size + 1;

        // Current subtree is a BST if:
        // 1. Both left and right subtrees are valid BSTs
        // 2. root->data > left subtree maximum
        // 3. root->data < right subtree minimum
        if (leftInfo.isBST && rightInfo.isBST &&
            root->data > leftInfo.maxVal && root->data < rightInfo.minVal) {
            curr.isBST = true;
            curr.minVal = min(root->data, leftInfo.minVal);
            curr.maxVal = max(root->data, rightInfo.maxVal);

            maxBSTSize = max(maxBSTSize, curr.size);
        } else {
            curr.isBST = false;
            // Min and Max don't matter once isBST is false, but set for safety
            curr.minVal = INT_MIN;
            curr.maxVal = INT_MAX;
        }

        return curr;
    }

public:
    int largestBst(Node *root) {
        maxBSTSize = 0;
        postorder(root);
        return maxBSTSize;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BOTTOM-UP POSTORDER STATS
 * ============================================================================
 *
 *               5
 *             /   \
 *            2     4
 *          /   \
 *         1     3
 *
 * Subtree at Node 2:
 *   Left(1): isBST=true, min=1, max=1, size=1
 *   Right(3): isBST=true, min=3, max=3, size=1
 *   Node(2): 1 < 2 < 3 -> isBST=true, min=1, max=3, size=3! (Max BST so far = 3)
 *
 * Subtree at Node 5:
 *   Left(2): maxVal = 3 (5 > 3: Valid)
 *   Right(4): minVal = 4 (5 < 4: INVALID!) -> Node 5 is NOT a BST.
 *
 * Largest BST size = 3!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Return struct `NodeInfo { bool isBST, int size, int minVal, int maxVal }`.
 * - Base `null`: `{true, 0, INT_MAX, INT_MIN}`.
 * - If `left.isBST && right.isBST && root->data > left.max && root->data < right.min`:
 *     - `curr.isBST = true; maxBSTSize = max(maxBSTSize, curr.size);`
 * - Time: O(N), Space: O(H).
 */
