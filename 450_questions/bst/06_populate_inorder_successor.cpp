/*
    QUESTION    : Populate Inorder Successor of all nodes
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/populate-inorder-successor-for-all-nodes/1
*/

#include <iostream>

using namespace std;

// Definition for Node with next pointer
struct Node {
    int data;
    Node* left;
    Node* right;
    Node* next;
    Node(int val) : data(val), left(nullptr), right(nullptr), next(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Reverse Inorder traversal (Right -> Root -> Left) visits each node once
// S.C : O(H) - Recursion stack space
class Solution {
private:
    // Tracks previously visited node in reverse inorder traversal
    Node* nextSuccessor = nullptr;

    void reverseInorder(Node* root) {
        if (root == nullptr) return;

        // 1. Visit right subtree first
        reverseInorder(root->right);

        // 2. Point current node's next to the previously visited node
        root->next = nextSuccessor;
        nextSuccessor = root; // Update nextSuccessor to be current node

        // 3. Visit left subtree
        reverseInorder(root->left);
    }

public:
    void populateNext(Node *root) {
        nextSuccessor = nullptr;
        reverseInorder(root);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF REVERSE INORDER LINKING
 * ============================================================================
 *
 * Tree:
 *             10
 *           /    \
 *          8      12
 *        /
 *       3
 *
 * Inorder Traversal: 3 -> 8 -> 10 -> 12
 * Reverse Inorder Traversal Order: 12 -> 10 -> 8 -> 3
 *
 * Step 1: Visit 12 -> 12->next = nullptr. nextSuccessor = 12.
 * Step 2: Visit 10 -> 10->next = 12.      nextSuccessor = 10.
 * Step 3: Visit 8  -> 8->next = 10.       nextSuccessor = 8.
 * Step 4: Visit 3  -> 3->next = 8.        nextSuccessor = 3.
 *
 * ============================================================================
 * DRY RUN
 * ============================================================================
 * | Node Visited (Reverse Inorder) | nextSuccessor Before | root->next Assigned | nextSuccessor After |
 * | :----------------------------- | :------------------- | :------------------ | :------------------ |
 * | Node(12)                       | nullptr              | nullptr             | Node(12)            |
 * | Node(10)                       | Node(12)             | Node(12)            | Node(10)            |
 * | Node(8)                        | Node(10)             | Node(10)            | Node(8)             |
 * | Node(3)                        | Node(8)              | Node(8)             | Node(3)             |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Reverse Baton Pass"
 * If you walk backwards through a line of runners (Right $\rightarrow$ Root $\rightarrow$ Left),
 * you already know who was standing directly ahead of you.
 * Hand your successor link (`next`) to them before stepping backwards!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Traverse in REVERSE INORDER: `Right -> Root -> Left`.
 * - Maintain global/pointer `nextSuccessor`.
 * - For current node: `root->next = nextSuccessor; nextSuccessor = root;`.
 * - Time: O(N), Space: O(H).
 */
