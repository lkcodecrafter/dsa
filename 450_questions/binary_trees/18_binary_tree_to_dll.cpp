/*
    QUESTION    : Convert Binary Tree to Doubly Linked List (Inorder In-place Conversion)
    Company Tags: Amazon, Microsoft, Morgan Stanley, Goldman Sachs
    GfG Link    : https://practice.geeksforgeeks.org/problems/binary-tree-to-dll/1
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
// T.C : O(N) - Inorder traversal visits each node once
// S.C : O(H) - Recursion stack space (In-place pointer rewiring)
class Solution {
private:
    Node* prev = nullptr;
    Node* head = nullptr;

    void inorder(Node* curr) {
        if (curr == nullptr) return;

        // 1. Convert left subtree
        inorder(curr->left);

        // 2. Process current node
        if (prev == nullptr) {
            head = curr; // The leftmost node becomes the head of the DLL
        } else {
            curr->left = prev;  // Current node's prev pointer
            prev->right = curr; // Previous node's next pointer
        }
        prev = curr;

        // 3. Convert right subtree
        inorder(curr->right);
    }

public:
    Node* bToDLL(Node *root) {
        prev = nullptr;
        head = nullptr;

        inorder(root);

        return head;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF INORDER DLL CONVERSION
 * ============================================================================
 *
 * Binary Tree:
 *             10
 *           /    \
 *         12      15
 *        /  \     /
 *       25  30   36
 *
 * Converted Doubly Linked List (Inorder):
 * 25 <===> 12 <===> 30 <===> 10 <===> 36 <===> 15
 *
 * Node->left acts as DLL `prev` pointer
 * Node->right acts as DLL `next` pointer
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `prev = nullptr`, `head = nullptr`.
 * - In Inorder traversal (`curr`):
 *     - If `prev == nullptr`: `head = curr`.
 *     - Else: `curr->left = prev; prev->right = curr;`.
 *     - `prev = curr`.
 * - Time: O(N), Space: O(H).
 */
