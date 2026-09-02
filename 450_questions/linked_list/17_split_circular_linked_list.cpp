/*
    QUESTION    : Split a Circular Linked List into two halves
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/split-a-circular-linked-list-into-two-halves/1
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
// T.C : O(N) - Tortoise and Hare algorithm
// S.C : O(1) - In-place pointer rewiring
void splitList(Node *head, Node **head1_ref, Node **head2_ref) {
    if (head == nullptr) return;

    Node* slow = head;
    Node* fast = head;

    // For even length, fast reaches head->next; for odd length, fast reaches head
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // For even length lists, fast->next->next is head; move fast one more step
    if (fast->next->next == head) {
        fast = fast->next;
    }

    // Set head of first half
    *head1_ref = head;

    // Set head of second half
    if (head->next != head) {
        *head2_ref = slow->next;
    }

    // Make second half circular
    fast->next = slow->next;

    // Make first half circular
    slow->next = head;
}

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Find mid with `while (fast->next != head && fast->next->next != head)`.
 * - `*head1_ref = head; *head2_ref = slow->next;`
 * - `fast->next = slow->next; slow->next = head;`
 * - Time: O(N), Space: O(1).
 */
