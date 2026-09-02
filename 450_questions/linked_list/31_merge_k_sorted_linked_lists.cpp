/*
    QUESTION    : Merge K sorted Linked lists
    Company Tags: Amazon, Microsoft, Google, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/merge-k-sorted-linked-lists/1
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(Total_Nodes * log K) - Priority queue of size K processed for all nodes
// S.C : O(K)                   - Min-Heap storing K list node heads
struct NodeCompare {
    bool operator()(Node* a, Node* b) {
        return a->data > b->data; // Min-Heap
    }
};

class Solution {
public:
    Node* mergeKLists(Node* arr[], int K) {
        priority_queue<Node*, vector<Node*>, NodeCompare> minHeap;

        // Push initial heads into heap
        for (int i = 0; i < K; i++) {
            if (arr[i] != nullptr) {
                minHeap.push(arr[i]);
            }
        }

        Node dummy(0);
        Node* tail = &dummy;

        while (!minHeap.empty()) {
            Node* curr = minHeap.top();
            minHeap.pop();

            tail->next = curr;
            tail = tail->next;

            if (curr->next != nullptr) {
                minHeap.push(curr->next);
            }
        }

        return dummy.next;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Push non-null list heads into Min-Heap.
 * - Loop: Pop `curr`, attach to `tail->next`, advance `tail`, push `curr->next` if non-null.
 * - Time: O(N log K), Space: O(K).
 */
