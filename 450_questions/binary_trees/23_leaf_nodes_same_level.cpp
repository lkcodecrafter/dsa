/*
    QUESTION    : Check if all leaf nodes are at same level or not
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/leaf-at-same-level/1
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
// T.C : O(N) - DFS traversal checks level of every leaf node
// S.C : O(H) - Recursion stack space
class Solution {
private:
    int leafLevel = -1;

    bool checkUtil(Node* root, int level) {
        if (root == nullptr) return true;

        // If current node is a leaf
        if (root->left == nullptr && root->right == nullptr) {
            // If this is the first leaf encountered, record its level
            if (leafLevel == -1) {
                leafLevel = level;
                return true;
            }
            // Check if current leaf matches the level of previous leaves
            return level == leafLevel;
        }

        // Recursively check left and right subtrees
        return checkUtil(root->left, level + 1) &&
               checkUtil(root->right, level + 1);
    }

public:
    bool check(Node *root) {
        leafLevel = -1;
        return checkUtil(root, 0);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF LEAF LEVEL CHECK
 * ============================================================================
 *
 * Valid (All leaves at level 2):
 *             1 (lvl 0)
 *           /   \
 *          2     3 (lvl 1)
 *        /   \  /  \
 *       4     5 6   7 (lvl 2) -> All leaves at level 2!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `leafLevel = -1`.
 * - In DFS at leaf node:
 *     - If `leafLevel == -1`: `leafLevel = level; return true;`
 *     - Else: `return level == leafLevel;`
 * - Time: O(N), Space: O(H).
 */
