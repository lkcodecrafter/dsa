/*
    QUESTION    : K largest elements in an array
    Company Tags: Amazon, Microsoft, Walmart
    GfG Link    : https://practice.geeksforgeeks.org/problems/k-largest-elements4206/1
    LeetCode    : https://leetcode.com/problems/kth-largest-element-in-an-array/
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log K) - Min-Heap of size K processed over N elements
// S.C : O(K)       - Space for maintaining Min-Heap of size K
class Solution {
public:
    vector<int> kLargest(int arr[], int n, int k) {
        // Min-Heap stores the K largest elements seen so far
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for (int i = 0; i < n; i++) {
            minHeap.push(arr[i]);

            // If heap size exceeds k, pop the minimum element (which cannot be among the top K largest)
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }

        // Extract elements from minHeap into result vector
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }

        // Return in descending order (largest first) as per standard GFG format
        reverse(result.begin(), result.end());
        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF MIN-HEAP OF SIZE K
 * ============================================================================
 *
 * Array: [ 12, 5, 787, 1, 23 ], k = 2
 *
 * Incoming 12  -> MinHeap: [12]
 * Incoming 5   -> MinHeap: [5, 12]
 * Incoming 787 -> MinHeap: [5, 12, 787] -> Size > 2 -> Pop Min (5) -> [12, 787]
 * Incoming 1   -> MinHeap: [1, 12, 787] -> Size > 2 -> Pop Min (1) -> [12, 787]
 * Incoming 23  -> MinHeap: [12, 23, 787]-> Size > 2 -> Pop Min (12)-> [23, 787]
 *
 * Top 2 Largest Elements: [ 787, 23 ]
 *
 * ============================================================================
 * DRY RUN (arr = {1, 23, 12, 9, 30, 2, 50}, k = 3)
 * ============================================================================
 * | i | arr[i] | Min-Heap Action        | Min-Heap State (Size <= 3) |
 * | :-| :----- | :--------------------- | :------------------------- |
 * | 0 | 1      | Push 1                 | {1}                        |
 * | 1 | 23     | Push 23                | {1, 23}                    |
 * | 2 | 12     | Push 12                | {1, 12, 23}                |
 * | 3 | 9      | Push 9, Pop Min (1)    | {9, 12, 23}                |
 * | 4 | 30     | Push 30, Pop Min (9)   | {12, 23, 30}               |
 * | 5 | 2      | Push 2, Pop Min (2)    | {12, 23, 30}               |
 * | 6 | 50     | Push 50, Pop Min (12)  | {23, 30, 50}               |
 *
 * Reversed Output: {50, 30, 23}
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Bouncer with a Capacity of K"
 * To find the top $K$ richest people in a crowd, open a VIP lounge of size $K$.
 * The poorest person in the VIP lounge is at the door (`minHeap.top()`).
 * If a richer person arrives, kick the poorest person out into the cold.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - To find $K$ LARGEST elements: use a MIN-HEAP of size $K$.
 * - If `minHeap.size() > k`: `minHeap.pop()`.
 * - Reverse the extracted elements to get descending order.
 * - Time Complexity: O(N log K), Space Complexity: O(K).
 */
