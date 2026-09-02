/*
    QUESTION    : Implement a MaxHeap/MinHeap using arrays and recursion (Build Heap)
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://www.geeksforgeeks.org/building-heap-from-array/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Building a heap from an array using bottom-up heapify runs in linear time
// S.C : O(log N) - Recursion stack space during heapify
class MaxHeap {
private:
    vector<int> heap;

    // Helper function to maintain Max-Heap property downwards from index `i`
    void heapify(int i, int n) {
        int largest = i;
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        // Compare with left child
        if (leftChild < n && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }

        // Compare with right child
        if (rightChild < n && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        // If largest is not the current root, swap and continue heapifying
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest, n); // Recursive call on the affected child subtree
        }
    }

public:
    // Builds a max heap from an unorganized array in O(N) time
    void buildHeap(const vector<int> &arr) {
        heap = arr;
        int n = heap.size();

        // Start heapifying from the last non-leaf node: (n / 2) - 1 down to 0
        for (int i = (n / 2) - 1; i >= 0; i--) {
            heapify(i, n);
        }
    }

    void printHeap() const {
        for (int val : heap) {
            cout << val << " ";
        }
        cout << "\n";
    }

    int getMax() const {
        return heap.empty() ? -1 : heap[0];
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF HEAP TREE & ARRAY MAPPING
 * ============================================================================
 *
 * Array: [ 4, 10, 3, 5, 1 ]
 *
 * Initial Tree Representation:
 *             4 (idx 0)
 *           /   \
 *   (idx 1)10    3 (idx 2)
 *         /  \
 * (idx 3)5    1 (idx 4)
 *
 * Last non-leaf node = (5 / 2) - 1 = 1 (Node 10).
 * - Heapify(1): 10 > 5 and 10 > 1 (No swap needed).
 * - Heapify(0): 4 < 10 (Left child). Swap 4 and 10!
 *   Subtree at idx 1 now has 4. Heapify(1): 4 < 5. Swap 4 and 5!
 *
 * Final Max Heap:
 *             10 (idx 0)
 *           /    \
 *   (idx 1)5      3 (idx 2)
 *         / \
 * (idx 3)4   1 (idx 4)
 *
 * Array: [ 10, 5, 3, 4, 1 ]
 *
 * ============================================================================
 * DRY RUN (arr = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17})
 * ============================================================================
 * | Step | Node Index i | Value heap[i] | Largest Child Found | Swapped With | Subtree Heapified |
 * | :--- | :----------- | :------------ | :------------------ | :----------- | :---------------- |
 * | 1    | i = 4        | 6             | heap[10] = 17       | Swap 6 & 17  | Complete          |
 * | 2    | i = 3        | 4             | heap[8] = 9         | Swap 4 & 9   | Complete          |
 * | 3    | i = 2        | 5             | heap[5] = 13        | Swap 5 & 13  | Complete          |
 * | 4    | i = 1        | 3             | heap[4] = 17        | Swap 3 & 17  | Recurse idx 4...  |
 * | 5    | i = 0        | 1             | heap[1] = 17        | Swap 1 & 17  | Final Max Heap!   |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Heavy Bubbles Sink / Sift Down"
 * In an organization, the most qualified leader must rise to the top.
 * You inspect managers starting from the bottom tier (`(n/2) - 1`) up to the CEO (`0`).
 * If a manager is less skilled than their direct report, promote the report and demote the manager down.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Array indices for node `i`:
 *     - Left Child: `2 * i + 1`
 *     - Right Child: `2 * i + 2`
 *     - Parent: `(i - 1) / 2`
 * - Last non-leaf node is at index `(n / 2) - 1`.
 * - Bottom-up `heapify` loop from `(n / 2) - 1` down to `0` runs in $O(N)$ total time (not $O(N \log N)$).
 * - Time: O(N), Space: O(log N).
 */
