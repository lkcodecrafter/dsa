/*
    QUESTION    : K-th Largest Sum Contiguous Subarray
    Company Tags: Amazon, Microsoft, Snapdeal
    GfG Link    : https://www.geeksforgeeks.org/k-th-largest-sum-contiguous-subarray/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2 * log K) - Generates all N*(N+1)/2 subarray sums and maintains a Min-Heap of size K
// S.C : O(K)           - Min-Heap storing K largest sums
class Solution {
public:
    int kthLargest(vector<int> &Arr, int N, int K) {
        // Min-Heap to maintain the top K largest subarray sums
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // Iterate over all possible subarrays using nested loops
        for (int i = 0; i < N; i++) {
            int currentSum = 0;
            for (int j = i; j < N; j++) {
                currentSum += Arr[j];

                // If heap has fewer than K elements, add current sum
                if (minHeap.size() < K) {
                    minHeap.push(currentSum);
                } else if (currentSum > minHeap.top()) {
                    // If current sum is larger than the smallest in the top K, replace it
                    minHeap.pop();
                    minHeap.push(currentSum);
                }
            }
        }

        return minHeap.top();
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF SUBARRAY SUMS WITH MIN-HEAP
 * ============================================================================
 *
 * Array: [ 3, 2, 1 ], K = 2
 *
 * Subarrays & Sums:
 * [3]       = 3
 * [3, 2]    = 5
 * [3, 2, 1] = 6
 * [2]       = 2
 * [2, 1]    = 3
 * [1]       = 1
 *
 * Sorted Subarray Sums: [ 6, 5, 3, 3, 2, 1 ]
 * 2nd Largest Subarray Sum = 5!
 *
 * ============================================================================
 * DRY RUN (Arr = {20, -5, -1}, N = 3, K = 3)
 * ============================================================================
 * | Subarray | Sum | Min-Heap Action (Size <= 3) | Heap State |
 * | :------- | :-- | :-------------------------- | :--------- |
 * | [20]     | 20  | Push 20                     | {20}       |
 * | [20, -5] | 15  | Push 15                     | {15, 20}   |
 * | [20,-5,-1| 14  | Push 14                     | {14, 15, 20}|
 * | [-5]     | -5  | -5 < minHeap.top() (14)     | {14, 15, 20}|
 * | [-5, -1] | -6  | -6 < 14                     | {14, 15, 20}|
 * | [-1]     | -1  | -1 < 14                     | {14, 15, 20}|
 *
 * Top of Min-Heap (3rd largest) = 14.
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The High-Score Filter"
 * As you compute every continuous block score, funnel it into a Min-Heap of size $K$.
 * Small scores get blocked; only top $K$ high-scores fit in the bucket.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Generate contiguous sums on the fly using `currentSum += Arr[j]` in $O(N^2)$.
 * - Maintain a Min-Heap of size $K$.
 * - If `currentSum > minHeap.top()`, pop and push `currentSum`.
 * - `minHeap.top()` gives the K-th largest subarray sum.
 * - Time: O(N^2 log K), Space: O(K).
 */
