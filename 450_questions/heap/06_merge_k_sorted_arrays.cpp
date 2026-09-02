/*
    QUESTION    : Merge K sorted arrays
    Company Tags: Amazon, Microsoft, Flipkart, VMWare
    GfG Link    : https://practice.geeksforgeeks.org/problems/merge-k-sorted-arrays/1
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * K * log K) - Total N*K elements; each heap push/pop takes O(log K)
// S.C : O(K)             - Min-Heap storing K elements at any time
struct Element {
    int val;
    int row;
    int col;

    // Custom comparator for min-heap (lowest value has highest priority)
    bool operator>(const Element &other) const {
        return val > other.val;
    }
};

class Solution {
public:
    vector<int> mergeKArrays(vector<vector<int>> arr, int K) {
        vector<int> result;
        // Min-Heap storing current front element of each of the K arrays
        priority_queue<Element, vector<Element>, greater<Element>> minHeap;

        // 1. Insert the first element of each of the K arrays
        for (int i = 0; i < K; i++) {
            minHeap.push({arr[i][0], i, 0});
        }

        // 2. Extract min element and push the next element from that same array
        while (!minHeap.empty()) {
            Element curr = minHeap.top();
            minHeap.pop();

            result.push_back(curr.val);

            int nextCol = curr.col + 1;
            // If the array still has elements left, push the next element
            if (nextCol < K) {
                minHeap.push({arr[curr.row][nextCol], curr.row, nextCol});
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF K-WAY MERGE WITH MIN-HEAP
 * ============================================================================
 *
 * Arrays (K = 3):
 * Row 0: [ 1, 5, 9 ]
 * Row 1: [ 4, 8, 10 ]
 * Row 2: [ 2, 6, 7 ]
 *
 * Initial Min-Heap:
 *   [ (1, r0, c0), (4, r1, c0), (2, r2, c0) ]
 *
 * Step 1: Pop 1 (from r0) -> Result: [1] -> Push next from r0: (5, r0, c1).
 * Step 2: Pop 2 (from r2) -> Result: [1, 2] -> Push next from r2: (6, r2, c1).
 * Step 3: Pop 4 (from r1) -> Result: [1, 2, 4] -> Push next from r1: (8, r1, c1).
 * Step 4: Pop 5 (from r0) -> Result: [1, 2, 4, 5] -> Push next from r0: (9, r0, c2).
 * ...
 * Merged Output: [ 1, 2, 4, 5, 6, 7, 8, 9, 10 ]
 *
 * ============================================================================
 * DRY RUN (arr = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, K = 3)
 * ============================================================================
 * | Step | Popped Element (val, row, col) | Pushed Element (val, row, col+1) | Result State |
 * | :--- | :------------------------------ | :-------------------------------- | :----------- |
 * | 1    | (1, 0, 0)                       | (2, 0, 1)                         | {1}          |
 * | 2    | (2, 0, 1)                       | (3, 0, 2)                         | {1, 2}       |
 * | 3    | (3, 0, 2)                       | None (Row 0 exhausted)            | {1, 2, 3}    |
 * | 4    | (4, 1, 0)                       | (5, 1, 1)                         | {1, 2, 3, 4} |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The 3-Lane Highway Toll Booth"
 * Vehicles line up in $K$ sorted lanes.
 * The toll booth only lets the single lowest-numbered vehicle through across all $K$ lanes,
 * advancing the vehicle in that specific lane forward.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Store tuple `{value, row, col}` in a Min-Heap of capacity $K$.
 * - Seed heap with first element of all $K$ rows.
 * - Loop: Pop `curr`, append `curr.val` to result, push `{arr[row][col+1]}` if `col + 1 < K`.
 * - Time: O(N * K log K), Space: O(K).
 */
