/*
    QUESTION    : Zig-Zag Tree Traversal (Spiral Level Order Traversal)
    Company Tags: Amazon, Microsoft, Flipkart, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/zigzag-tree-traversal/1
    LeetCode    : https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
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
// T.C : O(N) - Level-order BFS visits each node once
// S.C : O(W) = O(N) - Queue storing maximum level width
class Solution {
public:
    vector<int> zigZagTraversal(Node* root) {
        vector<int> result;
        if (root == nullptr) return result;

        queue<Node*> q;
        q.push(root);

        bool leftToRight = true;

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel(levelSize);

            for (int i = 0; i < levelSize; i++) {
                Node* curr = q.front();
                q.pop();

                // Compute index based on current traversal direction
                int idx = leftToRight ? i : (levelSize - 1 - i);
                currentLevel[idx] = curr->data;

                if (curr->left != nullptr) q.push(curr->left);
                if (curr->right != nullptr) q.push(curr->right);
            }

            // Invert direction flag for the next level
            leftToRight = !leftToRight;

            for (int val : currentLevel) {
                result.push_back(val);
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF ZIG-ZAG TRAVERSAL
 * ============================================================================
 *
 * Level 0 (L -> R):          1                 --> [ 1 ]
 *                          /   \
 * Level 1 (R -> L):       2     3              --> [ 3, 2 ]
 *                       /  \   /  \
 * Level 2 (L -> R):    4    5 6    7           --> [ 4, 5, 6, 7 ]
 *
 * Combined Output: [ 1, 3, 2, 4, 5, 6, 7 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Level order traversal with `levelSize = q.size()`.
 * - `idx = leftToRight ? i : (levelSize - 1 - i)`.
 * - `leftToRight = !leftToRight`.
 * - Time: O(N), Space: O(W).
 */
