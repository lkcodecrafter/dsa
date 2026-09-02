/*
    QUESTION    : QuickSort on Singly Linked List
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/quick-sort-on-linked-list/1
*/

#include <iostream>
#include <algorithm>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) average case, O(N^2) worst case
// S.C : O(log N) recursion stack depth
class Solution {
private:
    Node* getTail(Node* cur) {
        while (cur != nullptr && cur->next != nullptr) {
            cur = cur->next;
        }
        return cur;
    }

    // Partition the list using tail as pivot
    Node* partition(Node* head, Node* tail, Node** newHead, Node** newTail) {
        Node* pivot = tail;
        Node* prev = nullptr;
        Node* curr = head;
        Node* end = tail;

        // During partition, both head and tail of the list might change
        while (curr != pivot) {
            if (curr->data < pivot->data) {
                // First node with value < pivot becomes the new head
                if (*newHead == nullptr) {
                    *newHead = curr;
                }
                prev = curr;
                curr = curr->next;
            } else {
                // Move current node to the end of the list (after tail)
                if (prev != nullptr) {
                    prev->next = curr->next;
                }
                Node* temp = curr->next;
                curr->next = nullptr;
                end->next = curr;
                end = curr;
                curr = temp;
            }
        }

        // If pivot is smallest element, pivot itself is the new head
        if (*newHead == nullptr) {
            *newHead = pivot;
        }

        *newTail = end;
        return pivot;
    }

    Node* quickSortRecur(Node* head, Node* tail) {
        if (head == nullptr || head == tail) return head;

        Node *newHead = nullptr, *newTail = nullptr;

        Node* pivot = partition(head, tail, &newHead, &newTail);

        // If pivot is not the smallest element, sort the left partition
        if (newHead != pivot) {
            Node* temp = newHead;
            while (temp->next != pivot) {
                temp = temp->next;
            }
            temp->next = nullptr;

            newHead = quickSortRecur(newHead, temp);

            // Connect sorted left list to pivot
            temp = getTail(newHead);
            temp->next = pivot;
        }

        // Sort the right partition
        pivot->next = quickSortRecur(pivot->next, newTail);

        return newHead;
    }

public:
    void quickSort(struct Node **headRef) {
        *headRef = quickSortRecur(*headRef, getTail(*headRef));
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - QuickSort on Linked List partitions nodes around pivot into `< pivot` and `>= pivot`.
 * - Time: O(N log N) avg, Space: O(log N).
 */
