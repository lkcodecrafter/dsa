/*
 * QUESTION: Smallest Subarray with sum greater than a given value
 * Link: https://practice.geeksforgeeks.org/problems/smallest-subarray-with-sum-greater-than-x/0
 * 
 * Input: arr[] = {1, 4, 45, 6, 0, 19}, x = 51
 * Output: Min Length = 3 (Subarray is {4, 45, 6})
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Returns the minimum length of a subarray with sum > x. Returns 0 if none exists.
int smallestSubarrayWithSum(const std::vector<int>& arr, int x) {
    int n = arr.size();
    int current_sum = 0;
    int min_len = n + 1;
    int start = 0;
    
    for (int end = 0; end < n; end++) {
        // Add current element to sum
        current_sum += arr[end];
        
        // While sum becomes greater than x, shrink the window from the left
        while (current_sum > x) {
            min_len = std::min(min_len, end - start + 1);
            current_sum -= arr[start];
            start++;
        }
    }
    
    // If min_len was not updated, no such subarray exists
    return (min_len == n + 1) ? 0 : min_len;
}

/*
 * DRY RUN (arr = {1, 4, 45, 6}, x = 51):
 * Initial: current_sum = 0, min_len = 5, start = 0
 * 
 * | Step | end | arr[end] | current_sum | Condition (current_sum > 51) | Inner Action (min_len, current_sum, start updates) | min_len |
 * | :--- | :-- | :------- | :---------- | :--------------------------- | :------------------------------------------------- | :------ |
 * | 1    | 0   | 1        | 1           | 1 > 51 -> False              | None                                               | 5       |
 * | 2    | 1   | 4        | 5           | 5 > 51 -> False              | None                                               | 5       |
 * | 3    | 2   | 45       | 50          | 50 > 51 -> False             | None                                               | 5       |
 * | 4    | 3   | 6        | 56          | 56 > 51 -> True              | min_len = min(5, 3-0+1) = 4                        | 3       |
 * |      |     |          |             |                              | current_sum -= arr[0] -> 56 - 1 = 55, start = 1    |         |
 * |      |     |          | 55          | 55 > 51 -> True              | min_len = min(4, 3-1+1) = 3                        | 3       |
 * |      |     |          |             |                              | current_sum -= arr[1] -> 55 - 4 = 51, start = 2    |         |
 * |      |     |          | 51          | 51 > 51 -> False             | Loop ends                                          | 3       |
 * 
 * Final Min Length = 3 (Subarray arr[1...3] = {4, 45, 6})
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine a flexible tube. You feed elements from the right (`end`) to fill the tube until its contents weigh more than `x`. 
 * To find the shortest possible tube, you start squeezing elements out from the left (`start`) while keeping the weight > `x`. 
 * Keep track of the shortest tube length recorded.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize `current_sum = 0`, `min_len = n + 1`, and `start = 0`.
 * - Iterate `end` from `0` to `n-1`:
 *   - Add `arr[end]` to `current_sum`.
 *   - While `current_sum > x`:
 *     - Update `min_len = min(min_len, end - start + 1)`.
 *     - Subtract `arr[start]` from `current_sum` and increment `start`.
 * - Return `0` if `min_len` remains `n + 1`, else return `min_len`.
 * - Time Complexity: O(N) (each pointer advances at most N times).
 * - Space Complexity: O(1) auxiliary space.
 */
