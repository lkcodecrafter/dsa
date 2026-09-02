/*
    QUESTION    : Check if a Linked List is Circular
    Company Tags: Amazon, Microsoft, SAP Labs
    GfG Link    : https://practice.geeksforgeeks.org/problems/circular-linked-list/1
*/

#include <iostream>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear traversal
// S.C : O(1) - Constant space
bool isCircular(Node *head) {
    // Empty list is considered circular
    if (head == nullptr) return true;

    Node* curr = head->next;

    // Traverse until we hit nullptr or loop back to head
    while (curr != nullptr && curr != head) {
        curr = curr->next;
    }

    // If curr points back to head, it is a circular linked list
    return (curr == head);
}

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `curr = head->next;`
 * - `while (curr && curr != head) curr = curr->next;`
 * - `return curr == head;`
 * - Time: O(N), Space: O(1).
 */
