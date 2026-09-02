/*
    QUESTION    : Merge K Sorted Linked Lists
    Company Tags: Amazon, Microsoft, Google, VMWare
    GfG Link    : https://practice.geeksforgeeks.org/problems/merge-k-sorted-linked-lists/1
    LeetCode    : https://leetcode.com/problems/merge-k-sorted-lists/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(Total_Nodes * log K) - Priority queue of size K processed for all nodes
// S.C : O(K)                   - Min-Heap storing K list node heads
struct NodeCompare {
    bool operator()(Node* a, Node* b) {
        return a->data > b->data; // Min-Heap: smaller value has higher priority
    }
};

class Solution {
public:
    Node* mergeKLists(Node* arr[], int K) {
        priority_queue<Node*, vector<Node*>, NodeCompare> minHeap;

        // 1. Push the head node of each of the K non-empty linked lists
        for (int i = 0; i < K; i++) {
            if (arr[i] != nullptr) {
                minHeap.push(arr[i]);
            }
        }

        Node dummy(0);
        Node* tail = &dummy;

        // 2. Extract min node, attach to result list, and push its next node
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
 * VISUALIZATION OF K-WAY LINKED LIST MERGE
 * ============================================================================
 *
 * List 1: 1 -> 4 -> 5
 * List 2: 1 -> 3 -> 4
 * List 3: 2 -> 6
 *
 * Initial Min-Heap: [ Node(1_L1), Node(1_L2), Node(2_L3) ]
 *
 * 1. Pop 1_L1 -> Dummy -> 1_L1. Push 4_L1.
 * 2. Pop 1_L2 -> Dummy -> 1_L1 -> 1_L2. Push 3_L2.
 * 3. Pop 2_L3 -> Dummy -> 1_L1 -> 1_L2 -> 2_L3. Push 6_L3.
 * 4. Pop 3_L2 -> ...
 *
 * Result List: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6
 *
 * ============================================================================
 * DRY RUN
 * ============================================================================
 * | Step | Min-Heap Top | Attached Node Value | Next Pushed Node |
 * | :--- | :----------- | :------------------ | :--------------- |
 * | 1    | Node(1)      | 1                   | Node(4)          |
 * | 2    | Node(1)      | 1                   | Node(3)          |
 * | 3    | Node(2)      | 2                   | Node(6)          |
 * | 4    | Node(3)      | 3                   | Node(4)          |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Multi-Lane Zipper Merge"
 * Imagine $K$ conveyor belts feeding boxes onto a single track.
 * At every moment, take the lightest box among all $K$ belt fronts,
 * which advances only that specific conveyor belt forward.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Custom comparator struct with `operator()` for `Node* a->data > b->data`.
 * - Push valid heads into `priority_queue<Node*, vector<Node*>, NodeCompare>`.
 * - While heap not empty: `tail->next = curr`, if `curr->next != nullptr` push `curr->next`.
 * - Time: O(N log K) where N = total nodes, Space: O(K).
 */
