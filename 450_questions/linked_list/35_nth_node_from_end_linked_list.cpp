/*
    QUESTION    : Program for nth node from the end of a Linked List
    Company Tags: Amazon, Microsoft, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/nth-node-from-end-of-linked-list/1
    LeetCode    : https://leetcode.com/problems/remove-nth-node-from-end-of-list/
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
// T.C : O(N) - Fast pointer advances N steps ahead, then both advance until fast reaches null
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int getNthFromLast(Node *head, int n) {
        if (head == nullptr) return -1;

        Node* fast = head;
        Node* slow = head;

        // Step 1: Move fast pointer N steps ahead
        for (int i = 0; i < n; i++) {
            if (fast == nullptr) {
                return -1; // List has fewer than N nodes
            }
            fast = fast->next;
        }

        // Step 2: Advance both slow and fast pointers together
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }

        // slow is now pointing to the Nth node from the end
        return slow->data;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Advance `fast` by `n` steps. If `fast == nullptr` before `n` steps, return `-1`.
 * - `while (fast != nullptr) { slow = slow->next; fast = fast->next; }`.
 * - Return `slow->data`.
 * - Time: O(N), Space: O(1).
 */
