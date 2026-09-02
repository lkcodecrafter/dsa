/*
    QUESTION    : Left View of Binary Tree
    Company Tags: Amazon, Microsoft, Flipkart, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/left-view-of-binary-tree/1
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
// T.C : O(N) - Level-by-level BFS visits each node once
// S.C : O(W) = O(N) - Maximum width queue storage
vector<int> leftView(Node *root) {
    vector<int> result;
    if (root == nullptr) return result;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            Node* curr = q.front();
            q.pop();

            // The very first node encountered at each level (i == 0) is visible from the left
            if (i == 0) {
                result.push_back(curr->data);
            }

            if (curr->left != nullptr) q.push(curr->left);
            if (curr->right != nullptr) q.push(curr->right);
        }
    }

    return result;
}

/*
 * ============================================================================
 * VISUALIZATION OF LEFT VIEW (First node of each level)
 * ============================================================================
 *
 *               1   <-- Left View sees: 1 (Level 0)
 *             /   \
 *            2     3 <-- Left View sees: 2 (Level 1)
 *             \
 *              4     <-- Left View sees: 4 (Level 2)
 *
 * Left View: [ 1, 2, 4 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Level order traversal with `levelSize = q.size()`.
 * - If `i == 0`, `result.push_back(curr->data)`.
 * - Time: O(N), Space: O(W).
 */
