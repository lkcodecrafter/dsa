/*
    QUESTION    : Clone a linked list with next and random pointer
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/clone-a-linked-list-with-next-and-random-pointer/1
    LeetCode    : https://leetcode.com/problems/copy-list-with-random-pointer/
*/

#include <iostream>

using namespace std;

// Definition for Node with next and arb/random pointers
struct Node {
    int data;
    Node *next;
    Node *arb;
    Node(int x) : data(x), next(nullptr), arb(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - 3 passes over linked list
// S.C : O(1) - In-place interleaved node creation without extra hash map
class Solution {
public:
    Node *copyList(Node *head) {
        if (head == nullptr) return nullptr;

        // Step 1: Create duplicate copy of each node and insert it right next to original node
        Node* curr = head;
        while (curr != nullptr) {
            Node* copyNode = new Node(curr->data);
            copyNode->next = curr->next;
            curr->next = copyNode;
            curr = copyNode->next;
        }

        // Step 2: Set random pointers (arb) for copied nodes
        curr = head;
        while (curr != nullptr) {
            if (curr->arb != nullptr) {
                curr->next->arb = curr->arb->next;
            }
            curr = curr->next->next;
        }

        // Step 3: Separate the original and cloned linked lists
        curr = head;
        Node* clonedHead = head->next;
        Node* clonedCurr = clonedHead;

        while (curr != nullptr) {
            curr->next = curr->next->next;
            if (clonedCurr->next != nullptr) {
                clonedCurr->next = clonedCurr->next->next;
            }
            curr = curr->next;
            clonedCurr = clonedCurr->next;
        }

        return clonedHead;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF INTERLEAVED O(1) SPACE CLONING
 * ============================================================================
 *
 * Original: A -> B -> C
 *
 * Step 1 (Interleave):
 *   A -> A' -> B -> B' -> C -> C'
 *
 * Step 2 (Copy Random):
 *   A'->arb = A->arb->next
 *
 * Step 3 (Separate):
 *   Original: A -> B -> C
 *   Cloned  : A' -> B' -> C'
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Pass 1: Insert copy node between `curr` and `curr->next`.
 * - Pass 2: `curr->next->arb = curr->arb ? curr->arb->next : nullptr`.
 * - Pass 3: Unweave original and clone chains.
 * - Time: O(N), Space: O(1) auxiliary space!
 */
