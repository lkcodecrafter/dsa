/*
    QUESTION    : Detect Loop in Linked List (Floyd's Tortoise and Hare Cycle Detection)
    Company Tags: Amazon, Microsoft, Samsung, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/detect-loop-in-linked-list/1
    LeetCode    : https://leetcode.com/problems/linked-list-cycle/
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
// T.C : O(N) - Fast pointer moves twice as fast and catches slow pointer within cycle
// S.C : O(1) - Two pointer technique with constant space
class Solution {
public:
    bool detectLoop(Node* head) {
        if (head == nullptr || head->next == nullptr) return false;

        Node* slow = head;
        Node* fast = head;

        // Move slow by 1 step, fast by 2 steps
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            // If slow and fast pointers meet, a cycle exists
            if (slow == fast) {
                return true;
            }
        }

        return false; // Fast reached end of list -> No loop
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF FLOYD'S TORTOISE AND HARE
 * ============================================================================
 *
 * 1 -> 2 -> 3 -> 4 -> 5
 *           ^         |
 *           |---------| (Loop from 5 back to 3)
 *
 * Slow moves 1 step: 1 -> 2 -> 3 -> 4 -> 5 -> 3
 * Fast moves 2 steps: 1 -> 3 -> 5 -> 4 -> 3 (Meets slow at node 3!)
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `slow = head, fast = head`.
 * - `while (fast && fast->next)`:
 *     - `slow = slow->next; fast = fast->next->next;`
 *     - `if (slow == fast) return true;`
 * - Return `false`.
 * - Time: O(N), Space: O(1).
 */
