/*
    QUESTION    : Level Order Traversal of Binary Tree (BFS)
    Company Tags: Amazon, Microsoft, Flipkart, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/level-order-traversal/1
    LeetCode    : https://leetcode.com/problems/binary-tree-level-order-traversal/
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
// T.C : O(N) - Visits each node of the tree exactly once
// S.C : O(W) = O(N) - Queue stores at most maximum width of the tree
class Solution {
public:
    vector<int> levelOrder(Node* root) {
        vector<int> result;
        if (root == nullptr) return result;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            result.push_back(curr->data);

            if (curr->left != nullptr) {
                q.push(curr->left);
            }
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BFS QUEUE LEVEL ORDER TRAVERSAL
 * ============================================================================
 *
 *               1          Level 0 -> [ 1 ]
 *             /   \
 *            2     3        Level 1 -> [ 2, 3 ]
 *          /   \     \
 *         4     5     6     Level 2 -> [ 4, 5, 6 ]
 *
 * Queue Progression:
 * [1] -> pop 1, push 2, 3 -> [2, 3] -> pop 2, push 4, 5 -> [3, 4, 5] -> ...
 * Result: [ 1, 2, 3, 4, 5, 6 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Use a standard FIFO `std::queue<Node*>`.
 * - Push `root`.
 * - While `!q.empty()`:
 *     - Pop front node `curr`.
 *     - `result.push_back(curr->data)`.
 *     - Push `curr->left` and `curr->right` if not null.
 * - Time: O(N), Space: O(W).
 */
