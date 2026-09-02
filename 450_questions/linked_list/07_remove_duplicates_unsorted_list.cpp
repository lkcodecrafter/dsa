/*
    QUESTION    : Remove Duplicates from an Unsorted Linked List
    Company Tags: Amazon, Microsoft, Intuit
    GfG Link    : https://practice.geeksforgeeks.org/problems/remove-duplicates-from-an-unsorted-linked-list/1
*/

#include <iostream>
#include <unordered_set>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Hash set tracks seen values in a single pass
// S.C : O(N) - Hash set storing unique node values
class Solution {
public:
    Node * removeDuplicates(Node *head) {
        if (head == nullptr) return nullptr;

        unordered_set<int> seen;
        Node* curr = head;
        Node* prev = nullptr;

        while (curr != nullptr) {
            // If value already seen, delete current node
            if (seen.find(curr->data) != seen.end()) {
                prev->next = curr->next;
                Node* duplicate = curr;
                curr = curr->next;
                delete duplicate;
            } else {
                // First time seeing this value
                seen.insert(curr->data);
                prev = curr;
                curr = curr->next;
            }
        }

        return head;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `unordered_set<int> seen;`
 * - If `seen.count(curr->data)`: `prev->next = curr->next; delete curr;`
 * - Else: `seen.insert(curr->data); prev = curr;`
 * - Time: O(N), Space: O(N).
 */
