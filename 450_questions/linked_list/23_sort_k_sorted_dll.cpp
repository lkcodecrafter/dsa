/*
    QUESTION    : Sort a k-sorted Doubly Linked List
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/sort-k-sorted-doubly-linked-list/
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Definition for doubly-linked list node
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log K) - Min-Heap of size K+1 processed over N elements
// S.C : O(K)       - Priority queue of size K+1
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->data > b->data; // Min-Heap
    }
};

class Solution {
public:
    Node* sortAKSortedDLL(Node* head, int k) {
        if (head == nullptr) return head;

        priority_queue<Node*, vector<Node*>, CompareNode> minHeap;

        Node* newHead = nullptr;
        Node* last = nullptr;

        Node* curr = head;

        // Step 1: Insert first k + 1 elements into min-heap
        for (int i = 0; curr != nullptr && i <= k; i++) {
            minHeap.push(curr);
            curr = curr->next;
        }

        // Step 2: Extract min and push next node from list
        while (!minHeap.empty()) {
            if (newHead == nullptr) {
                newHead = minHeap.top();
                newHead->prev = nullptr;
                last = newHead;
            } else {
                last->next = minHeap.top();
                minHeap.top()->prev = last;
                last = minHeap.top();
            }

            minHeap.pop();

            if (curr != nullptr) {
                minHeap.push(curr);
                curr = curr->next;
            }
        }

        last->next = nullptr;
        return newHead;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Seed Min-Heap with first `k + 1` nodes.
 * - Loop: pop min node, link to DLL `last`, push `curr` if not null, advance `curr`.
 * - Time: O(N log K), Space: O(K).
 */
