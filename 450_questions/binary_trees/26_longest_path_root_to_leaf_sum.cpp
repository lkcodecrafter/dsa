/*
    QUESTION    : Sum of nodes on the longest path from root to leaf node (Bloodline of a Tree)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/sum-of-the-longest-bloodline-of-a-tree/1
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
// T.C : O(N) - DFS visits each node once
// S.C : O(H) - Recursion stack space
class Solution {
private:
    int maxLen = 0;
    int maxSum = INT_MIN;

    void dfs(Node* root, int currentLen, int currentSum) {
        if (root == nullptr) return;

        currentSum += root->data;
        currentLen++;

        // At leaf node, evaluate longest path and maximum sum
        if (root->left == nullptr && root->right == nullptr) {
            if (currentLen > maxLen) {
                maxLen = currentLen;
                maxSum = currentSum;
            } else if (currentLen == maxLen) {
                maxSum = max(maxSum, currentSum);
            }
            return;
        }

        dfs(root->left, currentLen, currentSum);
        dfs(root->right, currentLen, currentSum);
    }

public:
    int sumOfLongestRootToLeafPath(Node *root) {
        maxLen = 0;
        maxSum = INT_MIN;
        dfs(root, 0, 0);
        return maxSum;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF LONGEST BLOODLINE
 * ============================================================================
 *
 *               4
 *             /   \
 *            2     5
 *          /  \   / \
 *         7    1 2   3
 *             /
 *            6
 *
 * Path 1: 4 -> 2 -> 7 (Len 3, Sum 13)
 * Path 2: 4 -> 2 -> 1 -> 6 (Len 4, Sum 13)  <-- Longest path (Length 4)!
 * Path 3: 4 -> 5 -> 2 (Len 3, Sum 11)
 * Path 4: 4 -> 5 -> 3 (Len 3, Sum 12)
 *
 * Answer = 13.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - DFS with `(currentLen, currentSum)`.
 * - At leaf:
 *     - If `currentLen > maxLen`: `maxLen = currentLen; maxSum = currentSum;`.
 *     - If `currentLen == maxLen`: `maxSum = max(maxSum, currentSum);`.
 * - Time: O(N), Space: O(H).
 */
