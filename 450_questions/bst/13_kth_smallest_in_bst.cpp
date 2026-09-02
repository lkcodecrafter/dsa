/*
    QUESTION    : Find Kth smallest element in a BST
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/find-k-th-smallest-element-in-bst/1
    LeetCode    : https://leetcode.com/problems/kth-smallest-element-in-a-bst/
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
// T.C : O(H + K) - Standard Inorder traversal visits nodes in ascending order and stops at K
// S.C : O(H)     - Recursion stack space
class Solution {
private:
    int result = -1;
    int count = 0;

    // Standard Inorder traversal: Left -> Root -> Right gives elements in ASCENDING order
    void inorder(Node* root, int k) {
        if (root == nullptr || count >= k) return;

        // 1. Traverse left subtree
        inorder(root->left, k);

        // 2. Visit root
        count++;
        if (count == k) {
            result = root->data;
            return;
        }

        // 3. Traverse right subtree
        inorder(root->right, k);
    }

public:
    int KthSmallestElement(Node *root, int K) {
        result = -1;
        count = 0;
        inorder(root, K);
        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF INORDER ASCENDING TRAVERSAL
 * ============================================================================
 *
 *               50
 *             /    \
 *           30      70
 *          /  \    /  \
 *        20   40  60   80
 *
 * Inorder Traversal Order:
 * 1st Smallest: 20
 * 2nd Smallest: 30
 * 3rd Smallest: 40
 * 4th Smallest: 50
 *
 * If K = 3 -> Stops at Node 40. Answer = 40!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - For Kth SMALLEST: Use STANDARD INORDER (`Left -> Root -> Right`).
 * - Increment `count++`. When `count == K`: record `result = root->data` and return.
 * - Time: O(H + K), Space: O(H).
 */
