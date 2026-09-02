/*
    QUESTION    : Deletion from a Circular Linked List
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/deletion-circular-linked-list/
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
// T.C : O(N) - Linear search and pointer bypass
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    void deleteNode(Node** head, int key) {
        if (*head == nullptr) return;

        Node* curr = *head;
        Node* prev = nullptr;

        // Case 1: List contains only one node
        if (curr->data == key && curr->next == *head) {
            delete *head;
            *head = nullptr;
            return;
        }

        // Case 2: Head node itself is to be deleted
        if (curr->data == key) {
            // Find last node to update its next pointer to new head
            while (curr->next != *head) {
                curr = curr->next;
            }
            curr->next = (*head)->next;
            Node* oldHead = *head;
            *head = (*head)->next;
            delete oldHead;
            return;
        }

        // Case 3: Deleting a middle or last node
        prev = *head;
        curr = (*head)->next;

        while (curr != *head && curr->data != key) {
            prev = curr;
            curr = curr->next;
        }

        // If key found
        if (curr->data == key) {
            prev->next = curr->next;
            delete curr;
        }
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - 3 Cases:
 *     1. Only 1 node: delete and set `*head = nullptr`.
 *     2. Head node: find tail node, set `tail->next = head->next; *head = head->next;`.
 *     3. Middle/Tail node: `prev->next = curr->next; delete curr;`.
 * - Time: O(N), Space: O(1).
 */
