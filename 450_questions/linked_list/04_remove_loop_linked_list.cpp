/*
    QUESTION    : Remove loop in Linked List
    Company Tags: Amazon, Microsoft, Snapdeal, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/remove-loop-in-linked-list/1
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
// T.C : O(N) - Floyd's Cycle Detection + Loop Removal in linear time
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    void removeLoop(Node* head) {
        if (head == nullptr || head->next == nullptr) return;

        Node* slow = head;
        Node* fast = head;

        // Step 1: Detect if a loop exists
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }

        // No loop found
        if (slow != fast) return;

        // Step 2: Special case where loop starts at head itself
        if (slow == head) {
            while (fast->next != head) {
                fast = fast->next;
            }
            fast->next = nullptr;
            return;
        }

        // Step 3: Move slow to head; advance slow and fast by 1 step until their next pointers match
        slow = head;
        while (slow->next != fast->next) {
            slow = slow->next;
            fast = fast->next;
        }

        // fast is now pointing to the last node in the cycle
        fast->next = nullptr; // Break the cycle
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF LOOP REMOVAL
 * ============================================================================
 *
 * Distance to loop start = L.
 * Loop start to meeting point = d.
 * Cycle length = C.
 * Formula: L = k*C - d.
 * Moving slow to head and stepping 1-by-1 makes slow and fast meet at loop start!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Detect cycle with `slow` and `fast`.
 * - If `slow == head`: advance `fast` until `fast->next == head`, set `fast->next = nullptr`.
 * - Else: `slow = head; while (slow->next != fast->next) { slow = slow->next; fast = fast->next; }`
 * - `fast->next = nullptr;`
 * - Time: O(N), Space: O(1).
 */
