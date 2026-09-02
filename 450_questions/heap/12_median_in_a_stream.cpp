/*
    QUESTION    : Find Median in a stream of Integers
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/find-median-in-a-stream/0
    LeetCode    : https://leetcode.com/problems/find-median-from-data-stream/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : insertHeap: O(log N), getMedian: O(1)
// S.C : O(N) - Storage across two heaps (leftMaxHeap and rightMinHeap)
class Solution {
private:
    // leftMaxHeap stores the smaller half of numbers (max element is at top)
    priority_queue<int> leftMaxHeap;

    // rightMinHeap stores the larger half of numbers (min element is at top)
    priority_queue<int, vector<int>, greater<int>> rightMinHeap;

public:
    // Function to insert heap.
    void insertHeap(int &x) {
        // Step 1: Insert into leftMaxHeap or rightMinHeap
        if (leftMaxHeap.empty() || x <= leftMaxHeap.top()) {
            leftMaxHeap.push(x);
        } else {
            rightMinHeap.push(x);
        }

        // Step 2: Balance the two heaps so sizes differ by at most 1
        balanceHeaps();
    }

    // Function to balance heaps.
    void balanceHeaps() {
        // leftMaxHeap can have at most 1 more element than rightMinHeap
        if (leftMaxHeap.size() > rightMinHeap.size() + 1) {
            rightMinHeap.push(leftMaxHeap.top());
            leftMaxHeap.pop();
        } else if (rightMinHeap.size() > leftMaxHeap.size()) {
            leftMaxHeap.push(rightMinHeap.top());
            rightMinHeap.pop();
        }
    }

    // Function to return Median.
    double getMedian() {
        if (leftMaxHeap.size() == rightMinHeap.size()) {
            return (leftMaxHeap.top() + rightMinHeap.top()) / 2.0;
        }
        // If total elements is odd, leftMaxHeap holds the extra median element
        return leftMaxHeap.top();
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TWO-HEAP MEDIAN BALANCING
 * ============================================================================
 *
 * Stream: [ 5, 15, 1, 3 ]
 *
 * Incoming 5:
 *   leftMaxHeap: [ 5 ], rightMinHeap: [ ] -> Median = 5.0
 *
 * Incoming 15:
 *   leftMaxHeap: [ 5 ], rightMinHeap: [ 15 ] -> Median = (5 + 15) / 2 = 10.0
 *
 * Incoming 1:
 *   leftMaxHeap: [ 5, 1 ], rightMinHeap: [ 15 ] -> Median = 5.0
 *
 * Incoming 3:
 *   leftMaxHeap: [ 3, 1 ], rightMinHeap: [ 5, 15 ] -> Median = (3 + 5) / 2 = 4.0
 *
 * ============================================================================
 * DRY RUN
 * ============================================================================
 * | Number x | leftMaxHeap (Smaller Half) | rightMinHeap (Larger Half) | Calculated Median |
 * | :------- | :------------------------- | :------------------------- | :---------------- |
 * | 5        | {5}                        | {}                         | 5.0               |
 * | 15       | {5}                        | {15}                       | (5 + 15)/2 = 10.0 |
 * | 1        | {5, 1}                     | {15}                       | 5.0               |
 * | 3        | {3, 1}                     | {5, 15}                    | (3 + 5)/2 = 4.0   |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Balanced Scales"
 * Keep smaller numbers in the left pan (`Max-Heap`) and larger numbers in the right pan (`Min-Heap`).
 * The scale's center balance pin points directly at the median in $O(1)$!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `leftMaxHeap` (stores smaller half), `rightMinHeap` (stores larger half).
 * - If `x <= leftMaxHeap.top()`: push left; else push right.
 * - Balance: maintain `leftMaxHeap.size() == rightMinHeap.size()` or `left.size() == right.size() + 1`.
 * - Median:
 *     - If equal sizes: `(left.top() + right.top()) / 2.0`.
 *     - Else: `left.top()`.
 * - Time: O(log N) per insert, O(1) for median query. Space: O(N).
 */
