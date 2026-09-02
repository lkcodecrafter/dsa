/*
    QUESTION    : Smallest range in K Lists (Smallest range covering at least one element from each of the K lists)
    Company Tags: Amazon, Flipkart, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/find-smallest-range-containing-elements-from-k-lists/1
    LeetCode    : https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * K * log K) - Each element processed through Min-Heap of size K
// S.C : O(K)             - Min-Heap storing K list elements
struct RangeElement {
    int val;
    int row;
    int col;

    bool operator>(const RangeElement &other) const {
        return val > other.val;
    }
};

class Solution {
public:
    pair<int, int> findSmallestRange(int KSortedArray[][500], int n, int k) {
        priority_queue<RangeElement, vector<RangeElement>, greater<RangeElement>> minHeap;

        int currentMax = INT_MIN;

        // 1. Insert the 0th element of each of the K lists and track the maximum
        for (int i = 0; i < k; i++) {
            minHeap.push({KSortedArray[i][0], i, 0});
            currentMax = max(currentMax, KSortedArray[i][0]);
        }

        int rangeStart = 0;
        int rangeEnd = INT_MAX;

        // 2. Continuous window extraction
        while (true) {
            RangeElement minElement = minHeap.top();
            minHeap.pop();

            int currentMin = minElement.val;

            // Check if current range [currentMin, currentMax] is smaller than our best range
            if (currentMax - currentMin < rangeEnd - rangeStart) {
                rangeStart = currentMin;
                rangeEnd = currentMax;
            }

            // Advance pointer in the array that contained currentMin
            int nextCol = minElement.col + 1;
            if (nextCol == n) {
                // If any list is completely exhausted, we can no longer cover all K lists
                break;
            }

            minHeap.push({KSortedArray[minElement.row][nextCol], minElement.row, nextCol});
            currentMax = max(currentMax, KSortedArray[minElement.row][nextCol]);
        }

        return {rangeStart, rangeEnd};
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF MIN-MAX SLIDING WINDOW WITH HEAP
 * ============================================================================
 *
 * Lists (K = 3):
 * L1: [ 4, 10, 15, 24, 26 ]
 * L2: [ 0, 9, 12, 20 ]
 * L3: [ 5, 18, 22, 30 ]
 *
 * Step 1: Initial Heap: [ 0(L2), 4(L1), 5(L3) ], currentMax = 5.
 *   Range: [0, 5] (diff = 5). Pop 0, push 9(L2) -> max becomes 9.
 * Step 2: Heap: [ 4(L1), 5(L3), 9(L2) ], currentMax = 9.
 *   Range: [4, 9] (diff = 5). Pop 4, push 10(L1) -> max becomes 10.
 * Step 3: Heap: [ 5(L3), 9(L2), 10(L1) ], currentMax = 10.
 *   Range: [5, 10] (diff = 5). Pop 5, push 18(L3) -> max becomes 18.
 * ...
 * Best Smallest Range: [20, 24] (diff = 4)!
 *
 * ============================================================================
 * DRY RUN
 * ============================================================================
 * | Step | minHeap.top() (currentMin) | currentMax | Window [min, max] | Best Range [start, end] | Next Pushed Element |
 * | :--- | :------------------------- | :--------- | :---------------- | :---------------------- | :------------------ |
 * | 1    | 0 (L2)                     | 5          | [0, 5] (len 5)    | [0, 5]                  | 9 (L2)              |
 * | 2    | 4 (L1)                     | 9          | [4, 9] (len 5)    | [0, 5]                  | 10 (L1)             |
 * | 3    | 5 (L3)                     | 10         | [5, 10] (len 5)   | [0, 5]                  | 18 (L3)             |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Tightest Rubber Band"
 * Stretch a rubber band from the minimum element (`minHeap.top()`) to the maximum element (`currentMax`).
 * To shrink the rubber band, pull up the lowest peg by replacing it with the next number in its list.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Track `currentMax` explicitly across all elements currently in the Min-Heap.
 * - Current candidate range is `[minHeap.top().val, currentMax]`.
 * - If `(currentMax - currentMin < rangeEnd - rangeStart)`, update best range.
 * - Pop min, push `nextCol` element from same row, update `currentMax = max(currentMax, newVal)`.
 * - Stop immediately when any list runs out of elements (`nextCol == n`).
 * - Time: O(N * K log K), Space: O(K).
 */
