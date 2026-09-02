/*
 * QUESTION: Find the triplet that sum to a given value
 * Link: https://practice.geeksforgeeks.org/problems/triplet-sum-in-array/0
 * 
 * Input: arr[] = {1, 4, 45, 6, 10, 8}, sum = 13
 * Output: True (Triplet is {1, 4, 8})
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Returns true if there exists a triplet with the given sum, else false.
bool find3Numbers(std::vector<int>& arr, int target) {
    int n = arr.size();
    if (n < 3) return false;
    
    // Step 1: Sort the array
    std::sort(arr.begin(), arr.end());
    
    // Step 2: Fix the first element and find the other two using two pointers
    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;
        
        while (left < right) {
            int current_sum = arr[i] + arr[left] + arr[right];
            
            if (current_sum == target) {
                return true; // Triplet found
            } else if (current_sum < target) {
                left++; // Move left pointer right to increase sum
            } else {
                right--; // Move right pointer left to decrease sum
            }
        }
    }
    
    return false;
}

/*
 * DRY RUN (arr = {1, 4, 45, 6, 10, 8}, target = 13):
 * Sorted Array: {1, 4, 6, 8, 10, 45}
 * 
 * | Iteration i | arr[i] | left | right | arr[left] | arr[right] | Sum (arr[i] + arr[left] + arr[right]) | Action                        |
 * | :---------- | :----- | :--- | :---- | :-------- | :--------- | :------------------------------------ | :---------------------------- |
 * | i = 0        | 1      | 1    | 5     | 4         | 45         | 1 + 4 + 45 = 50                       | Sum > 13 -> right--           |
 * |              | 1      | 1    | 4     | 4         | 10         | 1 + 4 + 10 = 15                       | Sum > 13 -> right--           |
 * |              | 1      | 1    | 3     | 4         | 8          | 1 + 4 + 8 = 13                        | Sum == 13 -> return true!     |
 * 
 * Result: true
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * To find a triplet, fix one element `i`. 
 * This reduces the problem to finding two elements (`left` and `right`) in the sorted remaining array that sum to `target - arr[i]`. 
 * Use two pointers at both ends of the remaining array and move them inward.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Sort the array in ascending order.
 * - Iterate `i` from `0` to `n-3`:
 *   - Initialize `left = i + 1` and `right = n - 1`.
 *   - While `left < right`:
 *     - If `arr[i] + arr[left] + arr[right] == target`, return `true`.
 *     - If the sum is less than `target`, increment `left`.
 *     - Otherwise, decrement `right`.
 * - Return `false` if loop ends without finding a match.
 * - Time Complexity: O(N^2)
 * - Space Complexity: O(1) auxiliary space (excluding sorting space).
 */
