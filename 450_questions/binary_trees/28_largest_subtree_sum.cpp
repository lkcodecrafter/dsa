/*
    QUESTION    : Find largest subtree sum in a tree
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/find-largest-subtree-sum-tree/
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
// T.C : O(N) - Postorder traversal visits each node once
// S.C : O(H) - Recursion stack space
class Solution {
private:
    int maxSubtreeSum = INT_MIN;

    int postorderSum(Node* root) {
        if (root == nullptr) return 0;

        int currentSum = root->data + postorderSum(root->left) + postorderSum(root->right);

        maxSubtreeSum = max(maxSubtreeSum, currentSum);

        return currentSum;
    }

public:
    int findLargestSubtreeSum(Node* root) {
        maxSubtreeSum = INT_MIN;
        postorderSum(root);
        return maxSubtreeSum;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF LARGEST SUBTREE SUM
 * ============================================================================
 *
 *               1  [Sum = 1 - 2 + 3 + 4 + 5 - 6 + 2 = 7]
 *             /   \
 *           -2     3
 *          /  \   / \
 *         4    5 -6  2
 *
 * Subtree at Node -2: -2 + 4 + 5 = 7
 * Subtree at Node 3 : 3 - 6 + 2 = -1
 * Subtree at Node 1 : 1 + 7 - 1 = 7
 *
 * Max Subtree Sum = 7.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `currentSum = root->data + postorder(root->left) + postorder(root->right)`.
 * - `maxSubtreeSum = max(maxSubtreeSum, currentSum)`.
 * - Return `currentSum`.
 * - Time: O(N), Space: O(H).
 */
