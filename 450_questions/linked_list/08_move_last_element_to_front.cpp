/*
    QUESTION    : Move last element to Front in a Linked List
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/move-last-element-to-front-of-a-given-linked-list/
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
// T.C : O(N) - Linear traversal to locate the second to last node
// S.C : O(1) - Constant space
class Solution {
public:
    Node* moveToFront(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* secLast = nullptr;
        Node* last = head;

        // Traverse to find the second-to-last node and last node
        while (last->next != nullptr) {
            secLast = last;
            last = last->next;
        }

        // Detach last node from tail
        secLast->next = nullptr;

        // Attach last node to front as new head
        last->next = head;
        return last;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Find `secLast` and `last`.
 * - `secLast->next = nullptr; last->next = head; return last;`
 * - Time: O(N), Space: O(1).
 */
