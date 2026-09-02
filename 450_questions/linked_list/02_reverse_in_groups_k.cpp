/*
    QUESTION    : Reverse a Linked List in groups of given size K
    Company Tags: Amazon, Microsoft, Paytm, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/reverse-a-linked-list-in-groups-of-given-size/1
    LeetCode    : https://leetcode.com/problems/reverse-nodes-in-k-group/
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
// T.C : O(N) - Reverses each group of size K in linear time
// S.C : O(N / K) - Recursion stack space
class Solution {
public:
    Node* reverse(Node *head, int k) {
        if (head == nullptr) return nullptr;

        Node* prev = nullptr;
        Node* curr = head;
        Node* nextNode = nullptr;
        int count = 0;

        // Step 1: Reverse first K nodes of the linked list
        while (curr != nullptr && count < k) {
            nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
            count++;
        }

        // Step 2: `head` is now the tail of the reversed first group.
        // Recursively reverse remaining list and connect head->next to it.
        if (nextNode != nullptr) {
            head->next = reverse(nextNode, k);
        }

        // prev is the new head of this reversed group
        return prev;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF K-GROUP REVERSAL (k = 3)
 * ============================================================================
 *
 * Given List: [ 1 -> 2 -> 3 ] -> [ 4 -> 5 -> 6 ] -> [ 7 -> 8 ]
 *
 * 1. Reverse first 3: [ 3 -> 2 -> 1 ]
 * 2. Reverse next 3 : [ 6 -> 5 -> 4 ]
 * 3. Reverse last 2 : [ 8 -> 7 ]
 *
 * Connected: 3 -> 2 -> 1 -> 6 -> 5 -> 4 -> 8 -> 7
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Reverse `k` nodes iteratively using standard 3 pointers (`prev`, `curr`, `next`).
 * - If `nextNode != nullptr`: `head->next = reverse(nextNode, k)`.
 * - Return `prev`.
 * - Time: O(N), Space: O(N / K).
 */
