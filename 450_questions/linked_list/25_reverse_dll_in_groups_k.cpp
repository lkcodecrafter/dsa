/*
    QUESTION    : Reverse a Doubly Linked List in groups of given size K
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/reverse-doubly-linked-list-groups-given-size/
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
// T.C : O(N) - Reverses each group of size K
// S.C : O(N / K) - Recursion stack space
class Solution {
public:
    Node* reverseDLLInGroups(Node* head, int k) {
        if (head == nullptr) return nullptr;

        Node* current = head;
        Node* nextNode = nullptr;
        Node* newHead = nullptr;
        int count = 0;

        // Reverse first k nodes of the doubly linked list
        while (current != nullptr && count < k) {
            nextNode = current->next;
            current->next = newHead;
            current->prev = nullptr;

            if (newHead != nullptr) {
                newHead->prev = current;
            }

            newHead = current;
            current = nextNode;
            count++;
        }

        // Recursively reverse the rest of the list
        if (nextNode != nullptr) {
            head->next = reverseDLLInGroups(nextNode, k);
            if (head->next != nullptr) {
                head->next->prev = head;
            }
        }

        return newHead;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Reverse `k` DLL nodes by updating `next` and `prev` pointers.
 * - Recursively connect: `head->next = reverseDLLInGroups(nextNode, k); head->next->prev = head;`.
 * - Return `newHead`.
 * - Time: O(N), Space: O(N / K).
 */
