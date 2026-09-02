/*
    QUESTION    : Flattening a Linked List (Multi-level 2D Linked List with next and bottom pointers)
    Company Tags: Amazon, Microsoft, Qualcomm, Paytm, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/flattening-a-linked-list/1
*/

#include <iostream>

using namespace std;

// Definition for Node with next and bottom pointers
struct Node {
    int data;
    Node* next;
    Node* bottom;
    Node(int val) : data(val), next(nullptr), bottom(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - Merges columns from right to left in linear time
// S.C : O(1)     - In-place bottom pointer rewiring (Recursion stack O(K) where K = number of main heads)
class Solution {
private:
    // Helper function to merge two sorted linked lists via bottom pointers
    Node* merge(Node* a, Node* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;

        Node* result = nullptr;

        if (a->data <= b->data) {
            result = a;
            result->bottom = merge(a->bottom, b);
        } else {
            result = b;
            result->bottom = merge(a, b->bottom);
        }

        result->next = nullptr;
        return result;
    }

public:
    Node *flatten(Node *root) {
        // Base case: If list is empty or only one list remains
        if (root == nullptr || root->next == nullptr) {
            return root;
        }

        // Recursively flatten the rest of the list on the right
        root->next = flatten(root->next);

        // Merge current column with the flattened right list
        root = merge(root, root->next);

        return root;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 2D LIST FLATTENING
 * ============================================================================
 *
 * 5 -> 10 -> 19 -> 28
 * |    |     |     |
 * 7    20    22    35
 * |          |     |
 * 8          50    40
 * |                |
 * 30               45
 *
 * Merging right-to-left yields a single flattened list sorted via `bottom` pointers:
 * 5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 30 -> 35 -> 40 -> 45 -> 50
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `root->next = flatten(root->next);`
 * - `root = merge(root, root->next);`
 * - In `merge(a, b)`: use `bottom` pointers instead of `next` pointers.
 * - Time: O(N * M), Space: O(1) auxiliary.
 */
