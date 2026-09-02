/*
    QUESTION    : Find Kth largest element in a BST
    Company Tags: Amazon, Microsoft, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/kth-largest-element-in-bst/1
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
// T.C : O(H + K) - Reverse Inorder traversal stops immediately when Kth largest is visited
// S.C : O(H)     - Recursion stack space
class Solution {
private:
    int result = -1;
    int count = 0;

    // Reverse Inorder traversal: Right -> Root -> Left gives elements in DESCENDING order
    void reverseInorder(Node* root, int k) {
        if (root == nullptr || count >= k) return;

        // 1. Traverse right subtree
        reverseInorder(root->right, k);

        // 2. Visit root
        count++;
        if (count == k) {
            result = root->data;
            return;
        }

        // 3. Traverse left subtree
        reverseInorder(root->left, k);
    }

public:
    int kthLargest(Node *root, int K) {
        result = -1;
        count = 0;
        reverseInorder(root, K);
        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF REVERSE INORDER (DESCENDING ORDER)
 * ============================================================================
 *
 *               50
 *             /    \
 *           30      70
 *          /  \    /  \
 *        20   40  60   80
 *
 * Reverse Inorder Traversal Order:
 * 1st Largest: 80
 * 2nd Largest: 70
 * 3rd Largest: 60
 * 4th Largest: 50
 * 5th Largest: 40
 *
 * If K = 3 -> Stops at Node 60. Answer = 60!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - For Kth LARGEST: Use REVERSE INORDER (`Right -> Root -> Left`).
 * - Increment `count++` at each node.
 * - When `count == K`: record `result = root->data` and terminate early.
 * - Time: O(H + K), Space: O(H).
 */
