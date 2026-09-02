/*
 * QUESTION: Find the Largest Sum Contiguous Subarray (Kadane's Algorithm)
 * Link: https://practice.geeksforgeeks.org/problems/kadanes-algorithm/0
 * 
 * Input: arr[] = {-2, -3, 4, -1, -2, 1, 5, -3}
 * Output: Max Subarray Sum = 7 (Subarray is {4, -1, -2, 1, 5})
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// Finds the maximum contiguous subarray sum and optionally updates start and end indices.
long long maxSubarraySum(const std::vector<int>& arr, int& start_idx, int& end_idx) {
    long long max_so_far = LLONG_MIN;
    long long max_ending_here = 0;
    
    int temp_start = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        max_ending_here += arr[i];
        
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            start_idx = temp_start;
            end_idx = i;
        }
        
        // If current sum becomes negative, reset it.
        // Also update the temporary start index to i + 1.
        if (max_ending_here < 0) {
            max_ending_here = 0;
            temp_start = i + 1;
        }
    }
    
    return max_so_far;
}

/*
 * DRY RUN (arr = {-2, -3, 4, -1, -2, 1, 5, -3}):
 * 
 * | Step | i | arr[i] | max_ending_here | max_so_far | temp_start | start_idx | end_idx | Action / Reset                   |
 * | :--- | :-| :----- | :-------------- | :--------- | :--------- | :-------- | :------ | :------------------------------- |
 * | Init | - | -      | 0               | LLONG_MIN  | 0          | -1        | -1      | Initialization                   |
 * | 1    | 0 | -2     | -2              | -2         | 0          | 0         | 0       | ending < 0 -> reset ending=0, s=1|
 * | 2    | 1 | -3     | -3              | -2         | 1          | 0         | 0       | ending < 0 -> reset ending=0, s=2|
 * | 3    | 2 | 4      | 4               | 4          | 2          | 2         | 2       | update max_so_far                |
 * | 4    | 3 | -1     | 3               | 4          | 2          | 2         | 2       | ending >= 0 -> no reset          |
 * | 5    | 4 | -2     | 1               | 4          | 2          | 2         | 2       | ending >= 0 -> no reset          |
 * | 6    | 5 | 1      | 2               | 4          | 2          | 2         | 2       | ending >= 0 -> no reset          |
 * | 7    | 6 | 5      | 7               | 7          | 2          | 2         | 6       | update max_so_far                |
 * | 8    | 7 | -3     | 4               | 7          | 2          | 2         | 6       | ending >= 0 -> no reset          |
 * 
 * Max Sum: 7, Subarray: Indices 2 to 6
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine walking down a street collecting coins (+) and paying taxes (-). 
 * If your wallet gets completely empty (negative balance), it's better to throw it away, 
 * start fresh with a balance of 0, and look for the next positive street starting at the next house.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Maintain two variables: `max_so_far` (initialized to minimum integer value) and `max_ending_here` (initialized to 0).
 * - For each element:
 *   - Add it to `max_ending_here`.
 *   - Update `max_so_far` if `max_ending_here > max_so_far`.
 *   - If `max_ending_here` becomes negative, reset it to 0.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1)
 */
