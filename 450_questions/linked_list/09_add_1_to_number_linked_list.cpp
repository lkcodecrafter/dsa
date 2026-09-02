/*
    QUESTION    : Add 1 to a number represented as a Linked List
    Company Tags: Amazon, Microsoft, Snapdeal
    GfG Link    : https://practice.geeksforgeeks.org/problems/add-1-to-a-number-represented-as-linked-list/1
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
// T.C : O(N) - Backtracking recursion carries carry from right to left in single pass
// S.C : O(N) - Recursion stack
class Solution {
private:
    int addWithCarry(Node* head) {
        if (head == nullptr) {
            return 1; // Base case: carry to add to units digit is 1
        }

        int carry = addWithCarry(head->next);

        int total = head->data + carry;
        head->data = total % 10;

        return total / 10;
    }

public:
    Node* addOne(Node *head) {
        int carry = addWithCarry(head);

        // If carry remains after the most significant digit (e.g. 999 + 1 -> 1000)
        if (carry > 0) {
            Node* newHead = new Node(carry);
            newHead->next = head;
            return newHead;
        }

        return head;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Recursive backtracking propagates carry from right to left without list reversal!
 * - If final carry > 0, create `newHead = new Node(carry)` and prepend.
 * - Time: O(N), Space: O(N).
 */
