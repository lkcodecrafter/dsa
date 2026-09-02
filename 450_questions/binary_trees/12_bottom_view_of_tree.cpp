/*
    QUESTION    : Bottom View of Binary Tree
    Company Tags: Amazon, Microsoft, Paytm, Walmart
    GfG Link    : https://practice.geeksforgeeks.org/problems/bottom-view-of-binary-tree/1
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
// T.C : O(N log N) - Level order BFS with map overwriting latest node for each HD
// S.C : O(N)       - Queue and Map
class Solution {
public:
    vector<int> bottomView(Node *root) {
        vector<int> result;
        if (root == nullptr) return result;

        // Map stores: horizontalDistance -> latestSeenNodeData
        map<int, int> bottomNodeAtHD;

        // Queue stores: pair<Node*, horizontalDistance>
        queue<pair<Node*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            Node* node = curr.first;
            int hd = curr.second;

            // In Bottom View, always overwrite with the most recent (deepest) node at this HD
            bottomNodeAtHD[hd] = node->data;

            if (node->left != nullptr) {
                q.push({node->left, hd - 1});
            }
            if (node->right != nullptr) {
                q.push({node->right, hd + 1});
            }
        }

        // Collect elements from left to right
        for (auto &entry : bottomNodeAtHD) {
            result.push_back(entry.second);
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BOTTOM VIEW
 * ============================================================================
 *
 * HD:          -1     0    +1
 *                     1
 *                   /   \
 *                  2     3
 *                   \
 *                    4  <-- Overwrites 1 at HD = 0!
 * Bottom View: [ 2, 4, 3 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - BFS with `{node, hd}`.
 * - Always overwrite: `bottomNodeAtHD[hd] = node->data`.
 * - Iterate `bottomNodeAtHD` to get left-to-right view.
 * - Time: O(N log N), Space: O(N).
 */
