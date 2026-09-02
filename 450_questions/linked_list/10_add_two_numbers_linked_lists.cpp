/*
    QUESTION    : Add two numbers represented by linked lists
    Company Tags: Amazon, Microsoft, Qualcomm, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/add-two-numbers-represented-by-linked-lists/1
    LeetCode    : https://leetcode.com/problems/add-two-numbers-ii/
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
// T.C : O(N + M) - Reverse both lists + add digits + reverse result list
// S.C : O(max(N, M)) - Result linked list
class Solution {
private:
    Node* reverse(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        return prev;
    }

public:
    Node* addTwoLists(Node* num1, Node* num2) {
        // Step 1: Reverse both input linked lists to add starting from units place
        num1 = reverse(num1);
        num2 = reverse(num2);

        Node dummy(0);
        Node* tail = &dummy;
        int carry = 0;

        // Step 2: Traverse and add corresponding digits
        while (num1 != nullptr || num2 != nullptr || carry > 0) {
            int digit1 = (num1 != nullptr) ? num1->data : 0;
            int digit2 = (num2 != nullptr) ? num2->data : 0;

            int total = digit1 + digit2 + carry;
            carry = total / 10;

            tail->next = new Node(total % 10);
            tail = tail->next;

            if (num1 != nullptr) num1 = num1->next;
            if (num2 != nullptr) num2 = num2->next;
        }

        // Step 3: Reverse result list to restore most significant digit first
        return reverse(dummy.next);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `num1 = reverse(num1); num2 = reverse(num2);`
 * - Add digits with `carry` using dummy tail.
 * - Return `reverse(dummy.next)`.
 * - Time: O(N + M), Space: O(max(N, M)).
 */
