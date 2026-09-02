/*
    QUESTION    : Reverse a Doubly Linked List
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/reverse-a-doubly-linked-list/1
*/

#include <iostream>
#include <algorithm>

using namespace std;

// Definition for doubly-linked list node
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Swapping next and prev pointers of every node
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    Node* reverseDLL(Node * head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* curr = head;
        Node* temp = nullptr;

        // Swap next and prev pointers for all nodes
        while (curr != nullptr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;

            // Move to next node in original list (which is now curr->prev)
            curr = curr->prev;
        }

        // temp was pointing to prev of old tail (now new head)
        if (temp != nullptr) {
            head = temp->prev;
        }

        return head;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `while (curr != nullptr)`:
 *     - `swap(curr->next, curr->prev);`
 *     - `temp = curr; curr = curr->prev;`
 * - `return temp;`
 * - Time: O(N), Space: O(1).
 */
