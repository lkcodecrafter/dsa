/*
    QUESTION    : Check whether Singly Linked List is Palindrome
    Company Tags: Amazon, Microsoft, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/check-if-linked-list-is-pallindrome/1
    LeetCode    : https://leetcode.com/problems/palindrome-linked-list/
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
// T.C : O(N) - Find middle + reverse second half + compare both halves
// S.C : O(1) - In-place reversal of second half
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
    bool isPalindrome(Node *head) {
        if (head == nullptr || head->next == nullptr) return true;

        // Step 1: Find middle using slow and fast pointers
        Node* slow = head;
        Node* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse second half starting from slow->next
        Node* secondHalf = reverse(slow->next);
        Node* firstHalf = head;

        // Step 3: Compare first half and reversed second half
        bool palindrome = true;
        Node* p2 = secondHalf;
        while (p2 != nullptr) {
            if (firstHalf->data != p2->data) {
                palindrome = false;
                break;
            }
            firstHalf = firstHalf->next;
            p2 = p2->next;
        }

        // Step 4: Restore original list structure
        slow->next = reverse(secondHalf);

        return palindrome;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Find mid `slow`.
 * - Reverse second half: `secondHalf = reverse(slow->next)`.
 * - Compare `firstHalf->data == secondHalf->data`.
 * - Restore list with `slow->next = reverse(secondHalf)`.
 * - Time: O(N), Space: O(1).
 */
