/*
    QUESTION    : Intersection of two Sorted Linked Lists
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/intersection-of-two-sorted-linked-lists/1
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
// T.C : O(N + M) - Two-pointer linear merge of sorted linked lists
// S.C : O(min(N, M)) - Intersection result linked list
class Solution {
public:
    Node* findIntersection(Node* head1, Node* head2) {
        Node dummy(0);
        Node* tail = &dummy;

        Node* p1 = head1;
        Node* p2 = head2;

        while (p1 != nullptr && p2 != nullptr) {
            if (p1->data == p2->data) {
                tail->next = new Node(p1->data);
                tail = tail->next;
                p1 = p1->next;
                p2 = p2->next;
            } else if (p1->data < p2->data) {
                p1 = p1->next;
            } else {
                p2 = p2->next;
            }
        }

        return dummy.next;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Two-pointer technique on sorted lists:
 *     - If `p1->data == p2->data`: append node to dummy, advance both.
 *     - If `p1->data < p2->data`: `p1 = p1->next`.
 *     - Else: `p2 = p2->next`.
 * - Time: O(N + M), Space: O(min(N, M)).
 */
