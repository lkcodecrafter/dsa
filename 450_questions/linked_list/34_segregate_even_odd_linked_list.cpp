/*
    QUESTION    : Segregate even and odd nodes in a Linked List
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/segregate-even-and-odd-nodes-in-a-linked-list/0
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
// T.C : O(N) - In-place partition into even and odd chains
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    Node* divide(int N, Node *head) {
        if (head == nullptr || head->next == nullptr) return head;

        Node evenDummy(0), oddDummy(0);
        Node *evenTail = &evenDummy, *oddTail = &oddDummy;

        Node* curr = head;

        while (curr != nullptr) {
            if (curr->data % 2 == 0) {
                evenTail->next = curr;
                evenTail = evenTail->next;
            } else {
                oddTail->next = curr;
                oddTail = oddTail->next;
            }
            curr = curr->next;
        }

        // Connect even chain to odd chain
        evenTail->next = oddDummy.next;
        oddTail->next = nullptr;

        return (evenDummy.next != nullptr) ? evenDummy.next : oddDummy.next;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `evenDummy` and `oddDummy`.
 * - Partition nodes based on `curr->data % 2 == 0`.
 * - `evenTail->next = oddDummy.next; oddTail->next = nullptr;`
 * - Time: O(N), Space: O(1).
 */
