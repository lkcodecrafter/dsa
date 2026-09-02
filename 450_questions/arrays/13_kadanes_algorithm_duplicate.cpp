/*
 * QUESTION: Kadane's Algorithm (Duplicate of Q8 - Variation: Return the actual subarray elements)
 * Link: https://practice.geeksforgeeks.org/problems/kadanes-algorithm/0
 * 
 * Input: arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4}
 * Output: Max Subarray = {4, -1, 2, 1}, Sum = 6
 */

#include <iostream>
#include <vector>
#include <climits>

// Returns the maximum subarray sum and returns the actual subarray elements by reference.
std::vector<int> getMaxSubarray(const std::vector<int>& arr) {
    if (arr.empty()) return {};
    
    int max_so_far = INT_MIN;
    int max_ending_here = 0;
    
    int start_idx = 0;
    int end_idx = 0;
    int temp_start = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        max_ending_here += arr[i];
        
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            start_idx = temp_start;
            end_idx = i;
        }
        
        if (max_ending_here < 0) {
            max_ending_here = 0;
            temp_start = i + 1;
        }
    }
    
    // Construct the actual subarray
    std::vector<int> result;
    for (int i = start_idx; i <= end_idx; i++) {
        result.push_back(arr[i]);
    }
    
    return result;
}

/*
 * DRY RUN (arr = {-2, 1, -3, 4, -1, 2, 1}):
 * 
 * | Step | i | arr[i] | max_ending_here | max_so_far | temp_start | start_idx | end_idx | Action / Reset                   |
 * | :--- | :-| :----- | :-------------- | :--------- | :--------- | :-------- | :------ | :------------------------------- |
 * | Init | - | -      | 0               | INT_MIN    | 0          | 0         | 0       | Initialization                   |
 * | 1    | 0 | -2     | -2              | -2         | 0          | 0         | 0       | ending < 0 -> reset ending=0, s=1|
 * | 2    | 1 | 1      | 1               | 1          | 1          | 1         | 1       | update max_so_far                |
 * | 3    | 2 | -3     | -2              | 1          | 1          | 1         | 1       | ending < 0 -> reset ending=0, s=3|
 * | 4    | 3 | 4      | 4               | 4          | 3          | 3         | 3       | update max_so_far                |
 * | 5    | 4 | -1     | 3               | 4          | 3          | 3         | 3       | ending >= 0                      |
 * | 6    | 5 | 2      | 5               | 5          | 3          | 3         | 5       | update max_so_far                |
 * | 7    | 6 | 1      | 6               | 6          | 3          | 3         | 6       | update max_so_far                |
 * 
 * Subarray is arr[3...6] = {4, -1, 2, 1} with Sum = 6
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Remember that when `max_ending_here` dips below 0, it dragging down any future subarray. 
 * Therefore, we reset `max_ending_here = 0` and update `temp_start` to `i + 1` to mark the potential new beginning.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Use standard Kadane's algorithm but keep track of a `temp_start` index.
 * - When `max_ending_here` is updated to a value > `max_so_far`, update `start_idx = temp_start` and `end_idx = i`.
 * - When `max_ending_here < 0`, reset `max_ending_here = 0` and set `temp_start = i + 1`.
 * - Build the result array from index `start_idx` to `end_idx`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(N) to store the result subarray, O(1) auxiliary space.
 */
