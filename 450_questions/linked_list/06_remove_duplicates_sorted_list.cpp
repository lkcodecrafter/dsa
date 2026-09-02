/*
    QUESTION    : Remove Duplicates from Sorted Linked List
    Company Tags: Amazon, Microsoft, Wipro
    GfG Link    : https://practice.geeksforgeeks.org/problems/remove-duplicate-element-from-sorted-linked-list/1
    LeetCode    : https://leetcode.com/problems/remove-duplicates-from-sorted-list/
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
// T.C : O(N) - Linear traversal comparing adjacent nodes
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    Node* removeDuplicates(Node *head) {
        Node* curr = head;

        while (curr != nullptr && curr->next != nullptr) {
            if (curr->data == curr->next->data) {
                // Duplicate found: bypass next node and free memory
                Node* duplicateNode = curr->next;
                curr->next = curr->next->next;
                delete duplicateNode;
            } else {
                // Values are distinct: move to next node
                curr = curr->next;
            }
        }

        return head;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF DUPLICATE REMOVAL
 * ============================================================================
 *
 * List: 2 -> 2 -> 4 -> 5
 *
 * 1. At first 2: curr->data == curr->next->data (2 == 2) -> skip second 2 -> 2 -> 4
 * 2. At 2: 2 != 4 -> move to 4
 * 3. At 4: 4 != 5 -> move to 5
 *
 * Result: 2 -> 4 -> 5
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `while (curr && curr->next)`:
 *     - If `curr->data == curr->next->data`: `curr->next = curr->next->next;`
 *     - Else: `curr = curr->next;`
 * - Time: O(N), Space: O(1).
 */
