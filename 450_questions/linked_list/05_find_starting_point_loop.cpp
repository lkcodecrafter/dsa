/*
    QUESTION    : Find the first node / starting point of loop in a Linked List
    Company Tags: Amazon, Microsoft, Adobe
    GfG Link    : https://www.geeksforgeeks.org/find-first-node-of-loop-in-a-linked-list/
    LeetCode    : https://leetcode.com/problems/linked-list-cycle-ii/
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
// T.C : O(N) - Floyd's Cycle Algorithm
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    Node* findFirstNode(Node* head) {
        if (head == nullptr || head->next == nullptr) return nullptr;

        Node* slow = head;
        Node* fast = head;

        // Step 1: Detect meeting point in cycle
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }

        if (slow != fast) return nullptr; // No loop

        // Step 2: Reset slow to head; advance both 1 step at a time
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }

        // Both meet at the starting node of the loop!
        return slow;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF LOOP START POINT DISCOVERY
 * ============================================================================
 *
 * Distance head -> loop start = a
 * Distance loop start -> meet point = b
 * Distance meet point -> loop start = c
 * Fast traveled 2 * (a + b) = a + b + k*(b + c)
 * => a = (k - 1)(b + c) + c
 * Moving slow to head and advancing 1-by-1 ensures they collide at loop start!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Find meeting point with `slow` (1 step) and `fast` (2 steps).
 * - If loop exists: `slow = head; while (slow != fast) { slow = slow->next; fast = fast->next; }`.
 * - Return `slow`.
 * - Time: O(N), Space: O(1).
 */
