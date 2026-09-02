/*
    QUESTION    : Connect N ropes with minimum cost
    Company Tags: Amazon, Microsoft, Goldman Sachs, OYO Rooms
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-cost-of-ropes/0
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - N-1 merge operations using a Min-Heap
// S.C : O(N)       - Priority queue storing N ropes
class Solution {
public:
    // Function to return the minimum cost of connecting the ropes.
    long long minCost(long long arr[], long long n) {
        // Min-Heap to greedily extract the two shortest ropes at each step
        priority_queue<long long, vector<long long>, greater<long long>> minHeap;

        for (int i = 0; i < n; i++) {
            minHeap.push(arr[i]);
        }

        long long totalCost = 0;

        // While more than one rope remains in the heap
        while (minHeap.size() > 1) {
            long long rope1 = minHeap.top(); minHeap.pop();
            long long rope2 = minHeap.top(); minHeap.pop();

            long long combinedLength = rope1 + rope2;
            totalCost += combinedLength;

            // Put the newly merged rope back into the heap
            minHeap.push(combinedLength);
        }

        return totalCost;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF GREEDY ROPE MERGING (Huffman-like Tree)
 * ============================================================================
 *
 * Ropes: [ 4, 3, 2, 6 ]
 *
 * Step 1: Pick two smallest -> 2 and 3.
 *   Cost = 2 + 3 = 5.
 *   Heap: [ 4, 5, 6 ], totalCost = 5.
 *
 * Step 2: Pick two smallest -> 4 and 5.
 *   Cost = 4 + 5 = 9.
 *   Heap: [ 6, 9 ], totalCost = 5 + 9 = 14.
 *
 * Step 3: Pick two smallest -> 6 and 9.
 *   Cost = 6 + 9 = 15.
 *   Heap: [ 15 ], totalCost = 14 + 15 = 29.
 *
 * Minimum Total Cost = 29!
 *
 * ============================================================================
 * DRY RUN (arr = {4, 2, 7, 6, 9})
 * ============================================================================
 * | Step | Popped Ropes | Combined Length | Cost Added | minHeap After Push | Total Cost |
 * | :--- | :----------- | :-------------- | :--------- | :----------------- | :--------- |
 * | 1    | 2 and 4      | 6               | +6         | {6, 6, 7, 9}       | 6          |
 * | 2    | 6 and 6      | 12              | +12        | {7, 9, 12}         | 18         |
 * | 3    | 7 and 9      | 16              | +16        | {12, 16}           | 34         |
 * | 4    | 12 and 16    | 28              | +28        | {28}               | 62         |
 *
 * Output = 62.
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Greedy Knot Tier"
 * When tying ropes together, earlier connected ropes pay the penalty of being
 * re-counted in every subsequent knot. Therefore, keep the lengths connected earliest
 * as tiny as possible (Huffman greedy strategy).
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Push all rope lengths into `priority_queue<long long, vector<long long>, greater<long long>>`.
 * - While `heap.size() > 1`:
 *     - Pop two smallest `r1` and `r2`.
 *     - `totalCost += (r1 + r2)`.
 *     - Push `(r1 + r2)` back to heap.
 * - Time: O(N log N), Space: O(N).
 */
