/*
    QUESTION    : Merge 2 Binary Max Heaps
    Company Tags: Amazon, Goldman Sachs
    GfG Link    : https://practice.geeksforgeeks.org/problems/merge-two-binary-max-heap/0
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N + M) - Merging arrays takes O(N + M), buildHeap runs in linear time O(N + M)
// S.C : O(N + M) - Auxiliary vector to store the merged elements
class Solution {
private:
    void heapify(vector<int> &merged, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && merged[left] > merged[largest]) {
            largest = left;
        }

        if (right < n && merged[right] > merged[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(merged[i], merged[largest]);
            heapify(merged, n, largest);
        }
    }

public:
    vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m) {
        // Step 1: Concatenate both heap arrays into one merged array of size N + M
        vector<int> merged;
        merged.reserve(n + m);

        for (int val : a) merged.push_back(val);
        for (int val : b) merged.push_back(val);

        int totalSize = n + m;

        // Step 2: Build Max-Heap from the combined array in O(N + M) time
        for (int i = (totalSize / 2) - 1; i >= 0; i--) {
            heapify(merged, totalSize, i);
        }

        return merged;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF HEAP MERGING
 * ============================================================================
 *
 * Heap A: [ 10, 5, 6, 2 ]
 * Heap B: [ 12, 7, 9 ]
 *
 * Step 1: Concatenate: [ 10, 5, 6, 2, 12, 7, 9 ] (Total = 7 elements)
 *
 * Step 2: Heapify from (7 / 2) - 1 = 2 down to 0:
 *   - Heapify(2): Node 6 compared with 7 and 9 -> Swap 6 & 9.
 *   - Heapify(1): Node 5 compared with 2 and 12 -> Swap 5 & 12.
 *   - Heapify(0): Node 10 compared with 12 and 9 -> Swap 10 & 12.
 *
 * Result Max Heap: [ 12, 10, 9, 2, 5, 7, 6 ]
 *
 * ============================================================================
 * DRY RUN (a = {10, 5}, b = {12, 7})
 * ============================================================================
 * | Step | Array State Before | Heapify Index | Swapped Elements | Array State After |
 * | :--- | :----------------- | :------------ | :--------------- | :---------------- |
 * | 1    | {10, 5, 12, 7}     | i = 1         | 5 and 7          | {10, 7, 12, 5}    |
 * | 2    | {10, 7, 12, 5}     | i = 0         | 10 and 12        | {12, 7, 10, 5}    |
 *
 * Final Merged Max-Heap: {12, 7, 10, 5}
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Joint Company Reorganization"
 * When two separate branch offices merge, dump all employees into one master list
 * and run a single company-wide re-ranking (`buildHeap`) from the middle managers to the CEO.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Concatenate both arrays: `merged = a + b`.
 * - Run `buildHeap` bottom-up from index `((N + M) / 2) - 1` down to `0`.
 * - Total time is linear $O(N + M)$ rather than $O((N + M) \log(N + M))$.
 * - Time: O(N + M), Space: O(N + M).
 */
