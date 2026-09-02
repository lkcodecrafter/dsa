/*
    QUESTION    : Right View of Binary Tree
    Company Tags: Amazon, Microsoft, Flipkart, OYO
    GfG Link    : https://practice.geeksforgeeks.org/problems/right-view-of-binary-tree/1
    LeetCode    : https://leetcode.com/problems/binary-tree-right-side-view/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Level order BFS
// S.C : O(W) = O(N) - Maximum level width queue storage
class Solution {
public:
    vector<int> rightView(Node *root) {
        vector<int> result;
        if (root == nullptr) return result;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {
                Node* curr = q.front();
                q.pop();

                // The last node encountered at each level (i == levelSize - 1) is visible from the right
                if (i == levelSize - 1) {
                    result.push_back(curr->data);
                }

                if (curr->left != nullptr) q.push(curr->left);
                if (curr->right != nullptr) q.push(curr->right);
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF RIGHT VIEW (Last node of each level)
 * ============================================================================
 *
 *               1   --> Right View sees: 1 (Level 0)
 *             /   \
 *            2     3 --> Right View sees: 3 (Level 1)
 *          /
 *         4          --> Right View sees: 4 (Level 2)
 *
 * Right View: [ 1, 3, 4 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Level order traversal with `levelSize = q.size()`.
 * - If `i == levelSize - 1`, `result.push_back(curr->data)`.
 * - Time: O(N), Space: O(W).
 */
