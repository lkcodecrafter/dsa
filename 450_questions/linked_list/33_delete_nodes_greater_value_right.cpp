/*
    QUESTION    : Delete nodes which have a greater value on right side
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/delete-nodes-having-greater-value-on-right/1
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
// T.C : O(N) - Reverse + filter strictly decreasing sequence + reverse
// S.C : O(1) - Constant space
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
    Node *compute(Node *head) {
        // Step 1: Reverse the list so we can scan from right to left
        head = reverse(head);

        // Step 2: Track max node seen from right; delete any node with value < max
        Node* curr = head;
        Node* maxNode = head;

        while (curr != nullptr && curr->next != nullptr) {
            if (curr->next->data < maxNode->data) {
                Node* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
            } else {
                curr = curr->next;
                maxNode = curr;
            }
        }

        // Step 3: Reverse the list back to restore original left-to-right order
        return reverse(head);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Reverse list.
 * - Maintain running `maxNode`. If `curr->next->data < maxNode->data`, bypass next node.
 * - Reverse list back and return.
 * - Time: O(N), Space: O(1).
 */
