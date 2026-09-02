/*
    QUESTION    : Reverse Level Order Traversal
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/reverse-level-order-traversal/1
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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
// T.C : O(N) - BFS traversal + stack reversal
// S.C : O(N) - Queue and Stack storing N nodes
class Solution {
public:
    vector<int> reverseLevelOrder(Node *root) {
        vector<int> result;
        if (root == nullptr) return result;

        queue<Node*> q;
        stack<int> s;

        q.push(root);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            s.push(curr->data);

            // Important: Push RIGHT child first, then LEFT child to queue
            // so that left child is popped first when emptied from stack
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
        }

        // Pop all elements from stack into result
        while (!s.empty()) {
            result.push_back(s.top());
            s.pop();
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF QUEUE + STACK REVERSE BFS
 * ============================================================================
 *
 *               1
 *             /   \
 *            2     3
 *          /   \
 *         4     5
 *
 * Queue processes (Right then Left): 1 -> 3 -> 2 -> 5 -> 4
 * Stack pushes: [ 1, 3, 2, 5, 4 ]
 * Popping from stack yields: 4 -> 5 -> 2 -> 3 -> 1 (Bottom levels first, left to right!)
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Run BFS pushing right child first, then left child into `queue`.
 * - Push each popped value into a `stack`.
 * - Pop stack into `result` to get bottom-up level order.
 * - Time: O(N), Space: O(N).
 */
