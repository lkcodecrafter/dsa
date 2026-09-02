/*
    QUESTION    : Sort an Array using heap (HeapSort)
    Company Tags: Amazon, Microsoft, Samsung, Payu
    GfG Link    : https://www.geeksforgeeks.org/heap-sort/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - O(N) build heap + N extractions of O(log N) each
// S.C : O(1)       - In-place sorting algorithm
class Solution {
private:
    // Helper function to maintain max heap property downwards
    void heapify(int arr[], int n, int i) {
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
            heapify(arr, n, largest);
        }
    }

public:
    // Function to build a Heap from array.
    void buildHeap(int arr[], int n) {
        for (int i = (n / 2) - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
    }

    // Function to sort an array using Heap Sort.
    void heapSort(int arr[], int n) {
        // Step 1: Build Max Heap
        buildHeap(arr, n);

        // Step 2: One by one extract elements from heap
        for (int i = n - 1; i > 0; i--) {
            // Move current maximum (root arr[0]) to the end (arr[i])
            swap(arr[0], arr[i]);

            // Call max heapify on the reduced heap of size `i`
            heapify(arr, i, 0);
        }
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF HEAP SORT PROCESS
 * ============================================================================
 *
 * Array: [ 12, 11, 13, 5, 6, 7 ]
 *
 * Step 1: Build Max Heap:
 *   [ 13, 11, 12, 5, 6, 7 ] (13 is at index 0)
 *
 * Step 2: Extract 13 -> Swap with 7 (arr[5]):
 *   Heap (size 5): [ 7, 11, 12, 5, 6 ], Sorted section: [ 13 ]
 *   Heapify root -> [ 12, 11, 7, 5, 6 ]
 *
 * Step 3: Extract 12 -> Swap with 6 (arr[4]):
 *   Heap (size 4): [ 6, 11, 7, 5 ], Sorted section: [ 12, 13 ]
 *   Heapify root -> [ 11, 6, 7, 5 ]
 *
 * Continues until the entire array is sorted ascending: [ 5, 6, 7, 11, 12, 13 ]!
 *
 * ============================================================================
 * DRY RUN (arr = {4, 10, 3, 5, 1})
 * ============================================================================
 * | Iteration | Active Heap Size | Root Value (Max) | Swapped With | Array State After Heapify |
 * | :-------- | :--------------- | :--------------- | :----------- | :------------------------ |
 * | BuildHeap | 5                | 10               | -            | {10, 5, 3, 4, 1}          |
 * | 1         | 4                | 10               | arr[4] = 1   | {5, 4, 3, 1, 10}          |
 * | 2         | 3                | 5                | arr[3] = 1   | {4, 1, 3, 5, 10}          |
 * | 3         | 2                | 4                | arr[2] = 3   | {3, 1, 4, 5, 10}          |
 * | 4         | 1                | 3                | arr[1] = 1   | {1, 3, 4, 5, 10}          |
 *
 * Final Sorted Array: {1, 3, 4, 5, 10}
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Gold Medalist Podium"
 * Build a Max-Heap where the gold medalist is always at index 0.
 * Pop the champion to the very back of the line, shrink the tournament boundary by 1,
 * and let the remaining contenders compete to find the new champion.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `buildHeap(arr, n)` builds a Max Heap in $O(N)$ using bottom-up heapify.
 * - For `i = n - 1` down to `1`:
 *     - `swap(arr[0], arr[i])` (places current max at its final sorted position).
 *     - `heapify(arr, i, 0)` on the remaining `i` elements.
 * - Time: $O(N \log N)$ in all cases (Best, Avg, Worst).
 * - Space: $O(1)$ auxiliary space (in-place).
 */
