/*
    QUESTION    : Lowest Common Ancestor in a BST
    Company Tags: Amazon, Microsoft, Google, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/lowest-common-ancestor-in-a-bst/1
    LeetCode    : https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
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
// T.C : O(H) where H is height of BST (O(log N) for balanced BST)
// S.C : O(1) - Iterative traversal without auxiliary recursion stack
class Solution {
public:
    Node* LCA(Node *root, int n1, int n2) {
        Node* curr = root;

        while (curr != nullptr) {
            // If both n1 and n2 are smaller than current node, LCA must be in left subtree
            if (n1 < curr->data && n2 < curr->data) {
                curr = curr->left;
            }
            // If both n1 and n2 are greater than current node, LCA must be in right subtree
            else if (n1 > curr->data && n2 > curr->data) {
                curr = curr->right;
            }
            // If the paths split (or one value equals curr->data), this node is the LCA!
            else {
                return curr;
            }
        }

        return nullptr;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BST LCA SPLIT POINT
 * ============================================================================
 *
 *               6 (Split point for 2 and 8 -> LCA = 6)
 *             /   \
 *            2     8
 *           / \   / \
 *          0   4 7   9
 *             / \
 *            3   5
 *
 * For nodes 2 and 4:
 * - At 6: 2 < 6 and 4 < 6 -> Go Left.
 * - At 2: 2 == 2 (one matches) -> LCA = 2!
 *
 * ============================================================================
 * DRY RUN (n1 = 2, n2 = 8)
 * ============================================================================
 * | Step | curr Node | (n1 < curr && n2 < curr) | (n1 > curr && n2 > curr) | Decision / Action |
 * | :--- | :-------- | :----------------------- | :----------------------- | :---------------- |
 * | 1    | Node(6)   | (2<6 && 8<6) -> False    | (2>6 && 8>6) -> False    | Split! Return 6   |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Fork in the Road"
 * You and your friend are driving down the BST highway.
 * As long as both destinations lie down the same exit (both left or both right), keep driving together.
 * The exact intersection where you must take different exits is your LCA!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `n1 < curr->data && n2 < curr->data`: `curr = curr->left`.
 * - If `n1 > curr->data && n2 > curr->data`: `curr = curr->right`.
 * - Else: `return curr;` (The first split node is the Lowest Common Ancestor).
 * - Time: O(H), Space: O(1).
 */
