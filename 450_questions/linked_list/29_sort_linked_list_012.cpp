/*
    QUESTION    : Sort a linked list of 0s, 1s and 2s
    Company Tags: Amazon, Microsoft, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/given-a-linked-list-of-0s-1s-and-2s-sort-it/1
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
// T.C : O(N) - In-place pointer partitioning into 0s, 1s, and 2s lists and connecting them
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    Node* segregate(Node *head) {
        if (head == nullptr || head->next == nullptr) return head;

        // Dummy nodes for 0s, 1s, and 2s sublists
        Node zeroDummy(0), oneDummy(0), twoDummy(0);
        Node *zeroTail = &zeroDummy, *oneTail = &oneDummy, *twoTail = &twoDummy;

        Node* curr = head;

        // Step 1: Partition nodes into three separate chains
        while (curr != nullptr) {
            if (curr->data == 0) {
                zeroTail->next = curr;
                zeroTail = zeroTail->next;
            } else if (curr->data == 1) {
                oneTail->next = curr;
                oneTail = oneTail->next;
            } else {
                twoTail->next = curr;
                twoTail = twoTail->next;
            }
            curr = curr->next;
        }

        // Step 2: Connect 0s list -> 1s list -> 2s list
        zeroTail->next = (oneDummy.next != nullptr) ? oneDummy.next : twoDummy.next;
        oneTail->next = twoDummy.next;
        twoTail->next = nullptr; // Terminate list

        return zeroDummy.next;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - 3 dummy heads (`zeroDummy`, `oneDummy`, `twoDummy`).
 * - Distribute nodes in single pass.
 * - `zeroTail->next = oneDummy.next ? oneDummy.next : twoDummy.next;`
 * - `oneTail->next = twoDummy.next; twoTail->next = nullptr;`
 * - Time: O(N), Space: O(1).
 */
