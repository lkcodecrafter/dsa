/*
    QUESTION    : Reverse a Linked List (Iterative & Recursive)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://www.geeksforgeeks.org/reverse-a-linked-list/
    LeetCode    : https://leetcode.com/problems/reverse-linked-list/
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
// T.C : O(N) - Visits each node once
// S.C : O(1) iterative, O(N) recursive stack
class Solution {
public:
    // Approach 1: Iterative 3-pointer reversal (O(1) Space)
    Node* reverseListIterative(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;
        Node* nextNode = nullptr;

        while (curr != nullptr) {
            nextNode = curr->next; // 1. Save next node
            curr->next = prev;     // 2. Reverse current node's pointer
            prev = curr;           // 3. Move prev forward
            curr = nextNode;       // 4. Move curr forward
        }

        return prev; // prev is the new head
    }

    // Approach 2: Recursive reversal
    Node* reverseListRecursive(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* newHead = reverseListRecursive(head->next);

        // Make the next node point back to current node
        head->next->next = head;
        head->next = nullptr;

        return newHead;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 3-POINTER ITERATIVE REVERSAL
 * ============================================================================
 *
 * Initial:
 *   prev = null, curr = 1 -> 2 -> 3 -> null
 *
 * Step 1:
 *   nextNode = 2
 *   1 -> null
 *   prev = 1, curr = 2
 *
 * Step 2:
 *   nextNode = 3
 *   2 -> 1 -> null
 *   prev = 2, curr = 3
 *
 * Step 3:
 *   nextNode = null
 *   3 -> 2 -> 1 -> null
 *   prev = 3, curr = null
 *
 * New Head = 3!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `Node* prev = nullptr, *curr = head, *nextNode = nullptr;`
 * - While `curr != nullptr`:
 *     - `nextNode = curr->next; curr->next = prev; prev = curr; curr = nextNode;`
 * - Return `prev`.
 * - Time: O(N), Space: O(1).
 */
