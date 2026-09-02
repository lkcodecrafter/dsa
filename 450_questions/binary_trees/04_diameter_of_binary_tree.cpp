/*
    QUESTION    : Diameter of a Binary Tree (Longest path between any two nodes)
    Company Tags: Amazon, Microsoft, Directi, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/diameter-of-binary-tree/1
    LeetCode    : https://leetcode.com/problems/diameter-of-binary-tree/
*/

#include <iostream>
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
// T.C : O(N) - Computes height and updates maximum diameter in a single bottom-up pass
// S.C : O(H) - Recursion stack space
class Solution {
private:
    int maxDiameter = 0;

    int calculateHeight(Node* root) {
        if (root == nullptr) return 0;

        int lh = calculateHeight(root->left);
        int rh = calculateHeight(root->right);

        // Path passing through current root as curving peak has length (1 + lh + rh) in nodes
        maxDiameter = max(maxDiameter, 1 + lh + rh);

        // Return height to parent
        return 1 + max(lh, rh);
    }

public:
    int diameter(Node* root) {
        maxDiameter = 0;
        calculateHeight(root);
        return maxDiameter;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF DIAMETER AS PATH THROUGH HIGHEST ARCH
 * ============================================================================
 *
 *               1  [lh = 2, rh = 1 -> Diameter through 1 = 1 + 2 + 1 = 4]
 *             /   \
 *            2     3
 *          /
 *         4
 *
 * Longest Path: 4 -> 2 -> 1 -> 3 (4 nodes).
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Global `maxDiameter = 0`.
 * - In postorder height function:
 *     - `maxDiameter = max(maxDiameter, 1 + lh + rh)`.
 *     - Return `1 + max(lh, rh)`.
 * - Time: O(N), Space: O(H).
 */
