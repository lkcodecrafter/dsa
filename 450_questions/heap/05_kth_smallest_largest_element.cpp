/*
    QUESTION    : Kth smallest and largest element in an unsorted array
    Company Tags: Amazon, Microsoft, Snapdeal, Google
    GfG Link    : https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log K) - Processing N elements with a heap of size K
// S.C : O(K)       - Auxiliary space for the heap
class Solution {
public:
    // Returns Kth smallest element using Max-Heap of size K
    int kthSmallest(int arr[], int l, int r, int k) {
        priority_queue<int> maxHeap; // Standard C++ priority_queue is a Max-Heap

        for (int i = l; i <= r; i++) {
            maxHeap.push(arr[i]);
            if (maxHeap.size() > k) {
                maxHeap.pop(); // Pop largest among the K+1 elements
            }
        }

        return maxHeap.top();
    }

    // Returns Kth largest element using Min-Heap of size K
    int kthLargest(int arr[], int l, int r, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for (int i = l; i <= r; i++) {
            minHeap.push(arr[i]);
            if (minHeap.size() > k) {
                minHeap.pop(); // Pop smallest among the K+1 elements
            }
        }

        return minHeap.top();
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF HEAP COMPARISON
 * ============================================================================
 *
 * For Kth SMALLEST: Use MAX-HEAP of size K.
 *   - The top is the maximum among the K smallest elements -> exactly Kth smallest!
 *
 * For Kth LARGEST: Use MIN-HEAP of size K.
 *   - The top is the minimum among the K largest elements -> exactly Kth largest!
 *
 * ============================================================================
 * DRY RUN (arr = {7, 10, 4, 3, 20, 15}, k = 3)
 * ============================================================================
 * | Element | Max-Heap State for Kth Smallest | Min-Heap State for Kth Largest |
 * | :------ | :------------------------------ | :----------------------------- |
 * | 7       | {7}                             | {7}                            |
 * | 10      | {10, 7}                         | {7, 10}                        |
 * | 4       | {10, 7, 4}                      | {4, 7, 10}                     |
 * | 3       | Push 3, Pop 10 -> {7, 4, 3}     | Push 3, Pop 3 -> {4, 7, 10}    |
 * | 20      | Push 20, Pop 20 -> {7, 4, 3}    | Push 20, Pop 4 -> {7, 10, 20}  |
 * | 15      | Push 15, Pop 15 -> {7, 4, 3}    | Push 15, Pop 7 -> {10, 15, 20} |
 *
 * Top of Max-Heap (3rd Smallest) = 7
 * Top of Min-Heap (3rd Largest)  = 10
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "Opposites Attract"
 * - Need SMALLEST? Build a ceiling (MAX-heap). The lowest ceiling tile is the top.
 * - Need LARGEST? Build a floor (MIN-heap). The lowest floor tile is the top.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Kth Smallest: `priority_queue<int>` (Max-Heap) of size $K$. Top is answer.
 * - Kth Largest: `priority_queue<int, vector<int>, greater<int>>` (Min-Heap) of size $K$. Top is answer.
 * - Time: O(N log K), Space: O(K).
 */
