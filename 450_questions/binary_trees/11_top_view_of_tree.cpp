/*
    QUESTION    : Top View of Binary Tree
    Company Tags: Amazon, Microsoft, Paytm, Walmart
    GfG Link    : https://practice.geeksforgeeks.org/problems/top-view-of-binary-tree/1
*/

#include <iostream>
#include <vector>
#include <map>
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
// T.C : O(N log N) - Level order BFS with map ordered by vertical horizontal distance (HD)
// S.C : O(N)       - Queue and Map storing nodes and vertical coordinates
class Solution {
public:
    vector<int> topView(Node *root) {
        vector<int> result;
        if (root == nullptr) return result;

        // Map stores: horizontalDistance -> firstNodeData
        map<int, int> topNodeAtHD;

        // Queue stores: pair<Node*, horizontalDistance>
        queue<pair<Node*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            Node* node = curr.first;
            int hd = curr.second;

            // If this horizontal distance (column) is visited for the first time, record it
            if (topNodeAtHD.find(hd) == topNodeAtHD.end()) {
                topNodeAtHD[hd] = node->data;
            }

            if (node->left != nullptr) {
                q.push({node->left, hd - 1});
            }
            if (node->right != nullptr) {
                q.push({node->right, hd + 1});
            }
        }

        // Collect elements from left to right (sorted HD in std::map)
        for (auto &entry : topNodeAtHD) {
            result.push_back(entry.second);
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TOP VIEW VERTICAL COORDINATES
 * ============================================================================
 *
 * HD:          -1     0    +1
 *                     1
 *                   /   \
 *                  2     3
 *                   \
 *                    4
 * Top View: [ 2, 1, 3 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - BFS with `{node, hd}` where `root` is at `hd = 0`.
 * - `node->left` has `hd - 1`, `node->right` has `hd + 1`.
 * - If `topNodeAtHD.find(hd) == end()`: insert `topNodeAtHD[hd] = node->data`.
 * - Time: O(N log N), Space: O(N).
 */
