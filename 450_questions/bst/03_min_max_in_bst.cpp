/*
    QUESTION    : Find min and max value in a BST
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-element-in-bst/1
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
// S.C : O(1) - Iterative traversal
class Solution {
public:
    // Minimum element is always located at the leftmost node
    int minValue(Node* root) {
        if (root == nullptr) return -1;

        Node* curr = root;
        while (curr->left != nullptr) {
            curr = curr->left;
        }

        return curr->data;
    }

    // Maximum element is always located at the rightmost node
    int maxValue(Node* root) {
        if (root == nullptr) return -1;

        Node* curr = root;
        while (curr->right != nullptr) {
            curr = curr->right;
        }

        return curr->data;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF MIN AND MAX IN BST
 * ============================================================================
 *
 *               20
 *             /    \
 *            10     30
 *           /  \      \
 *     MIN->5   15      40 <- MAX
 *
 * - Minimum: Keep going LEFT -> 5
 * - Maximum: Keep going RIGHT -> 40
 *
 * ============================================================================
 * DRY RUN
 * ============================================================================
 * | Operation | Traversal Path | Result |
 * | :-------- | :------------- | :----- |
 * | minValue  | 20 -> 10 -> 5  | 5      |
 * | maxValue  | 20 -> 30 -> 40 | 40     |
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `minValue`: `while (curr->left != nullptr) curr = curr->left; return curr->data;`
 * - `maxValue`: `while (curr->right != nullptr) curr = curr->right; return curr->data;`
 * - Time: O(H), Space: O(1).
 */
