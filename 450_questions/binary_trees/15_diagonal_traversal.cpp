/*
    QUESTION    : Diagonal Traversal of Binary Tree
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/diagonal-traversal-of-binary-tree/
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
// T.C : O(N) - Visits each node once using Queue-based diagonal sweep
// S.C : O(N) - Queue storing left child pointers
vector<int> diagonal(Node *root) {
    vector<int> result;
    if (root == nullptr) return result;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        // Traverse the complete right slope of the current diagonal
        while (curr != nullptr) {
            result.push_back(curr->data);

            // If a left child exists, it starts a new diagonal slope below; push to queue
            if (curr->left != nullptr) {
                q.push(curr->left);
            }

            curr = curr->right; // Continue along the same diagonal slope
        }
    }

    return result;
}

/*
 * ============================================================================
 * VISUALIZATION OF DIAGONAL SLOPES
 * ============================================================================
 *
 *               8
 *             /   \
 *            3     10
 *          /   \     \
 *         1     6     14
 *             /  \    /
 *            4    7  13
 *
 * Diagonal 0 (Slope 0): 8 -> 10 -> 14
 * Diagonal 1 (Slope 1): 3 -> 6 -> 7 -> 13
 * Diagonal 2 (Slope 2): 1 -> 4
 *
 * Combined Diagonal Output: [ 8, 10, 14, 3, 6, 7, 13, 1, 4 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `queue<Node*> q; q.push(root);`
 * - While `!q.empty()`:
 *     - `curr = q.front(); q.pop();`
 *     - `while (curr != nullptr)`:
 *         - `result.push_back(curr->data);`
 *         - If `curr->left != nullptr`: `q.push(curr->left);`
 *         - `curr = curr->right;`
 * - Time: O(N), Space: O(N).
 */
