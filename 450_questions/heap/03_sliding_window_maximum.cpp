/*
    QUESTION    : Maximum of all subarrays of size k (Sliding Window Maximum)
    Company Tags: Amazon, Flipkart, Microsoft, Google
    GfG Link    : https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/
    LeetCode    : https://leetcode.com/problems/sliding-window-maximum/
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Every element is pushed and popped from the deque at most once
// S.C : O(K) - Double-ended queue storing at most K indices
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        vector<int> result;
        deque<int> dq; // Monotonic Decreasing Deque storing indices of nums

        for (int i = 0; i < nums.size(); i++) {
            // 1. Remove indices that are outside the current sliding window [i - k + 1, i]
            if (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }

            // 2. Maintain monotonic decreasing order: remove smaller elements from back
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            // 3. Push current index
            dq.push_back(i);

            // 4. Record maximum (at front of deque) once window reaches size k
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF MONOTONIC DEQUE SLIDING WINDOW
 * ============================================================================
 *
 * Array: [ 1, 3, -1, -3, 5, 3, 6, 7 ], k = 3
 *
 * Window 1: [ 1, 3, -1 ] -> Deque: [3, -1]       -> Max = 3
 * Window 2: [ 3, -1, -3 ]-> Deque: [3, -1, -3]   -> Max = 3
 * Window 3: [ -1, -3, 5 ]-> Deque: [5]           -> Max = 5 (5 knocked out -1, -3!)
 * Window 4: [ -3, 5, 3 ] -> Deque: [5, 3]        -> Max = 5
 * Window 5: [ 5, 3, 6 ]  -> Deque: [6]           -> Max = 6
 * Window 6: [ 3, 6, 7 ]  -> Deque: [7]           -> Max = 7
 *
 * Result: [ 3, 3, 5, 5, 6, 7 ]
 *
 * ============================================================================
 * DRY RUN (nums = {1, 3, -1, -3, 5, 3, 6, 7}, k = 3)
 * ============================================================================
 * | i | nums[i] | Deque Action                        | Deque Content (Indices) | Window Max (nums[dq.front()]) |
 * | :-| :------ | :---------------------------------- | :---------------------- | :---------------------------- |
 * | 0 | 1       | Push 0                              | {0}                     | -                             |
 * | 1 | 3       | Pop 0 (1 < 3), Push 1               | {1}                     | -                             |
 * | 2 | -1      | Push 2                              | {1, 2}                  | nums[1] = 3                   |
 * | 3 | -3      | Push 3                              | {1, 2, 3}               | nums[1] = 3                   |
 * | 4 | 5       | Expire 1 (<=1), Pop 2,3, Push 4     | {4}                     | nums[4] = 5                   |
 * | 5 | 3       | Push 5                              | {4, 5}                  | nums[4] = 5                   |
 * | 6 | 6       | Pop 4, 5, Push 6                    | {6}                     | nums[6] = 6                   |
 * | 7 | 7       | Pop 6, Push 7                       | {7}                     | nums[7] = 7                   |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Rising Star and the Aging Veteran"
 * If a younger player enters the team (`nums[i]`) and is stronger than existing veterans,
 * the weaker veterans get dropped from the roster (`pop_back`).
 * When a veteran gets too old for the time window (`front <= i - k`), they retire (`pop_front`).
 * The best player on the team is always at `front`.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Use a `std::deque<int>` to maintain indices in strictly descending value order.
 * - If `dq.front() <= i - k`: `dq.pop_front()` (out of window bounds).
 * - While `nums[dq.back()] <= nums[i]`: `dq.pop_back()` (smaller elements are obsolete).
 * - `dq.push_back(i)`.
 * - If `i >= k - 1`: `result.push_back(nums[dq.front()])`.
 * - Time: O(N) linear time, Space: O(K).
 */
