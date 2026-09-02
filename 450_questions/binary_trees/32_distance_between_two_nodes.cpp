/*
    QUESTION    : Min distance between two given nodes of a Binary Tree
    Company Tags: Amazon, Microsoft, Paytm, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/min-distance-between-two-given-nodes-of-a-binary-tree/1
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - LCA computation O(N) + Depth finding O(N)
// S.C : O(H) - Recursion stack space
class Solution {
private:
    Node* findLCA(Node* root, int a, int b) {
        if (root == nullptr || root->data == a || root->data == b) {
            return root;
        }

        Node* left = findLCA(root->left, a, b);
        Node* right = findLCA(root->right, a, b);

        if (left != nullptr && right != nullptr) return root;
        return (left != nullptr) ? left : right;
    }

    // Helper function to find distance from a given root to target node val
    int findDistance(Node* root, int val, int dist) {
        if (root == nullptr) return -1;
        if (root->data == val) return dist;

        int leftDist = findDistance(root->left, val, dist + 1);
        if (leftDist != -1) return leftDist;

        return findDistance(root->right, val, dist + 1);
    }

public:
    int findDist(Node* root, int a, int b) {
        // Step 1: Find the Lowest Common Ancestor (LCA) of nodes a and b
        Node* lcaNode = findLCA(root, a, b);

        // Step 2: Distance = dist(LCA, a) + dist(LCA, b)
        int distA = findDistance(lcaNode, a, 0);
        int distB = findDistance(lcaNode, b, 0);

        return distA + distB;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF DISTANCE VIA LCA
 * ============================================================================
 *
 *               1  (LCA for 4 and 6)
 *             /   \
 *            2     3
 *          /  \     \
 *         4    5     6
 *
 * LCA(4, 6) = 1
 * Distance(1, 4) = 2 edges (1 -> 2 -> 4)
 * Distance(1, 6) = 2 edges (1 -> 3 -> 6)
 * Total Distance = 2 + 2 = 4!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `lcaNode = findLCA(root, a, b)`.
 * - Total distance = `findDistance(lcaNode, a, 0) + findDistance(lcaNode, b, 0)`.
 * - Time: O(N), Space: O(H).
 */
