/*
    QUESTION    : Maximum sum of nodes in Binary tree such that no two are adjacent (House Robber III)
    Company Tags: Amazon, Flipkart, Google
    GfG Link    : https://www.geeksforgeeks.org/maximum-sum-nodes-binary-tree-no-two-adjacent/
    LeetCode    : https://leetcode.com/problems/house-robber-iii/
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
// T.C : O(N) - Postorder tree DP returns pair<includeRootSum, excludeRootSum>
// S.C : O(H) - Recursion stack space
class Solution {
private:
    // Returns pair<int, int>: {sum_including_node, sum_excluding_node}
    pair<int, int> solve(Node* root) {
        if (root == nullptr) {
            return {0, 0};
        }

        auto leftPair = solve(root->left);
        auto rightPair = solve(root->right);

        // Option 1: Include current node -> CANNOT include children
        int includeRoot = root->data + leftPair.second + rightPair.second;

        // Option 2: Exclude current node -> CAN choose best of include/exclude for each child
        int excludeRoot = max(leftPair.first, leftPair.second) +
                          max(rightPair.first, rightPair.second);

        return {includeRoot, excludeRoot};
    }

public:
    int getMaxSum(Node *root) {
        auto res = solve(root);
        return max(res.first, res.second);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TREE DP (Include vs Exclude)
 * ============================================================================
 *
 *               3
 *             /   \
 *            2     3
 *             \     \
 *              3     1
 *
 * Leaf 3: {3, 0}, Leaf 1: {1, 0}
 * Node 2: {2 + 0, max(3, 0)} = {2, 3}
 * Node 3 (right): {3 + 0, max(1, 0)} = {3, 1}
 * Root 3: {3 + 3 + 1, max(2,3) + max(3,1)} = {7, 3 + 3} = {7, 6}
 * Max = 7!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `includeRoot = root->data + left.exclude + right.exclude`.
 * - `excludeRoot = max(left.inc, left.exc) + max(right.inc, right.exc)`.
 * - Return `{includeRoot, excludeRoot}`.
 * - Time: O(N), Space: O(H).
 */
