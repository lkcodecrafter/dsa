/*
    QUESTION    : Rotate Doubly Linked List by N nodes
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/rotate-doubly-linked-list-n-nodes/
*/

#include <iostream>

using namespace std;

// Definition for doubly-linked list node
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Traversing to Nth node and tail
// S.C : O(1) - In-place pointer modification
class Solution {
public:
    Node* rotateDLL(Node* head, int N) {
        if (N == 0 || head == nullptr) return head;

        Node* current = head;

        // Traverse to N-th node
        int count = 1;
        while (count < N && current != nullptr) {
            current = current->next;
            count++;
        }

        if (current == nullptr || current->next == nullptr) {
            return head; // N >= length of DLL
        }

        Node* NthNode = current;

        // Find the tail of the DLL
        Node* tail = current;
        while (tail->next != nullptr) {
            tail = tail->next;
        }

        // Connect old tail to old head
        tail->next = head;
        head->prev = tail;

        // NthNode->next becomes the new head
        head = NthNode->next;
        head->prev = nullptr;

        // Break connection after NthNode
        NthNode->next = nullptr;

        return head;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Traverse to `NthNode` and `tail`.
 * - `tail->next = head; head->prev = tail;`
 * - `head = NthNode->next; head->prev = nullptr;`
 * - `NthNode->next = nullptr;`
 * - Time: O(N), Space: O(1).
 */
