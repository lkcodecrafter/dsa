/*
    QUESTION    : Merge Sort For Linked Lists
    Company Tags: Amazon, Microsoft, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/sort-a-linked-list/1
    LeetCode    : https://leetcode.com/problems/sort-list/
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
// T.C : O(N log N) - Divide & conquer halving of linked list + linear merge
// S.C : O(log N)   - Recursion stack space (In-place pointer rewiring)
class Solution {
private:
    // Helper to find the middle node of a linked list and split it
    Node* getMid(Node* head) {
        Node* slow = head;
        Node* fast = head->next;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    // Helper to merge two sorted linked lists
    Node* merge(Node* l1, Node* l2) {
        Node dummy(0);
        Node* tail = &dummy;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->data <= l2->data) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        if (l1 != nullptr) tail->next = l1;
        if (l2 != nullptr) tail->next = l2;

        return dummy.next;
    }

public:
    Node* mergeSort(Node* head) {
        // Base case: 0 or 1 node is already sorted
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Step 1: Split list into two halves
        Node* mid = getMid(head);
        Node* rightHead = mid->next;
        mid->next = nullptr; // Disconnect left and right halves

        // Step 2: Recursively sort both halves
        Node* leftSorted = mergeSort(head);
        Node* rightSorted = mergeSort(rightHead);

        // Step 3: Merge sorted halves
        return merge(leftSorted, rightSorted);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Merge Sort is the PREFERRED $O(N \log N)$ sorting algorithm for Linked Lists because
 *   pointers allow $O(1)$ extra space merging without contiguous memory reallocation.
 * - Split at `mid = getMid(head)` where `mid->next = nullptr`.
 * - `return merge(mergeSort(head), mergeSort(rightHead));`
 * - Time: O(N log N), Space: O(log N).
 */
