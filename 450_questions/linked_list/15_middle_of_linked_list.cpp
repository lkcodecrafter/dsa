/*
    QUESTION    : Find the middle Element of a Linked List
    Company Tags: Amazon, Microsoft, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/finding-middle-element-in-a-linked-list/1
    LeetCode    : https://leetcode.com/problems/middle-of-the-linked-list/
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
// T.C : O(N) - Fast pointer travels at 2x speed, slow pointer reaches middle when fast reaches end
// S.C : O(1) - Two-pointer technique
class Solution {
public:
    int getMiddle(Node *head) {
        if (head == nullptr) return -1;

        Node* slow = head;
        Node* fast = head;

        // When fast reaches the end, slow is at the exact middle (or second middle for even length)
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow->data;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `slow = head, fast = head`.
 * - `while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }`
 * - `return slow->data;`
 * - Time: O(N), Space: O(1).
 */
