/*
    QUESTION    : Convert Min Heap to Max Heap
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/convert-min-heap-to-max-heap/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Bottom-up Max-Heapify from index (N / 2) - 1 down to 0
// S.C : O(log N) - Recursion stack space for heapify
class Solution {
private:
    // Sifts down smaller elements to maintain Max-Heap property
    void maxHeapify(vector<int> &arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            maxHeapify(arr, n, largest);
        }
    }

public:
    void convertMinToMaxHeap(vector<int> &arr, int N) {
        // Start Max-Heapify from the last internal node down to the root
        for (int i = (N / 2) - 1; i >= 0; i--) {
            maxHeapify(arr, N, i);
        }
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF CONVERSION
 * ============================================================================
 *
 * Input Min-Heap:
 *             3
 *           /   \
 *          5     9
 *        /  \
 *       6    8
 * Array: [ 3, 5, 9, 6, 8 ]
 *
 * Heapify bottom-up:
 * - Start at index (5 / 2) - 1 = 1 (Node 5): Compare with 6 and 8 -> Swap 5 & 8.
 *   Array: [ 3, 8, 9, 6, 5 ]
 * - Index 0 (Node 3): Compare with 8 and 9 -> Swap 3 & 9.
 *   Subtree at idx 2 is a leaf.
 *   Array: [ 9, 8, 3, 6, 5 ]
 *
 * Result Max Heap:
 *             9
 *           /   \
 *          8     3
 *        /  \
 *       6    5
 *
 * ============================================================================
 * DRY RUN (arr = {3, 5, 9, 6, 8, 20, 10, 12, 18, 9})
 * ============================================================================
 * | Step | Index i | Value arr[i] | Largest Child Found | Swapped With | Array State |
 * | :--- | :------ | :----------- | :------------------ | :----------- | :---------- |
 * | 1    | i = 4   | 8            | 9 (idx 9)           | Swap 8 & 9   | Partial     |
 * | 2    | i = 3   | 6            | 18 (idx 8)          | Swap 6 & 18  | Partial     |
 * | 3    | i = 2   | 9            | 20 (idx 5)          | Swap 9 & 20  | Partial     |
 * | 4    | i = 1   | 5            | 18 (idx 3)          | Swap 5 & 18  | Partial     |
 * | 5    | i = 0   | 3            | 20 (idx 2)          | Swap 3 & 20  | Complete!   |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Universal Heap Reset"
 * A Min-Heap is just an arbitrary array that satisfies min-heap rules.
 * To turn any array into a Max-Heap, simply run standard `buildHeap` (bottom-up `maxHeapify`)
 * from index `(N/2)-1` down to `0`.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Apply `maxHeapify(arr, N, i)` from `i = (N / 2) - 1` down to `0`.
 * - Time Complexity: O(N) linear time.
 * - Space Complexity: O(log N) stack space.
 */
