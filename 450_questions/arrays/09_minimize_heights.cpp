/*
 * QUESTION: Minimise the maximum difference between heights [V.IMP]
 * Link: https://practice.geeksforgeeks.org/problems/minimize-the-heights3351/1
 * 
 * Input: arr[] = {1, 15, 10}, k = 6
 * Output: Min Difference = 5
 * Explanation: Modify to {1+6, 15-6, 10-6} = {7, 9, 4}. Max difference is 9 - 4 = 5.
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Returns the minimum possible difference between the heights of the shortest and tallest towers.
int getMinDiff(std::vector<int>& arr, int k) {
    int n = arr.size();
    if (n == 1) return 0;
    
    // Step 1: Sort the array
    std::sort(arr.begin(), arr.end());
    
    // Initialize difference without modification
    int ans = arr[n - 1] - arr[0];
    
    int smallest = arr[0] + k;
    int largest = arr[n - 1] - k;
    
    // Step 2: Traverse and find minimum difference
    for (int i = 1; i < n; i++) {
        // Height cannot be negative, so we skip if we can't subtract k
        if (arr[i] - k < 0) {
            continue;
        }
        
        int min_val = std::min(smallest, arr[i] - k);
        int max_val = std::max(largest, arr[i - 1] + k);
        
        ans = std::min(ans, max_val - min_val);
    }
    
    return ans;
}

/*
 * DRY RUN (arr = {1, 15, 10}, k = 6):
 * Sorted Array: {1, 10, 15}, n = 3
 * Initial ans = 15 - 1 = 14
 * smallest = 1 + 6 = 7
 * largest = 15 - 6 = 9
 * 
 * | Step | i | arr[i] | arr[i]-k < 0 | min_val = min(7, arr[i]-6) | max_val = max(9, arr[i-1]+6) | max_val - min_val | ans updated |
 * | :--- | :-| :----- | :----------- | :------------------------- | :-------------------------- | :----------------- | :---------- |
 * | 1    | 1 | 10     | 10-6=4 >= 0  | min(7, 4) = 4              | max(9, 1+6) = 9             | 9 - 4 = 5          | min(14,5)=5 |
 * | 2    | 2 | 15     | 15-6=9 >= 0  | min(7, 9) = 7              | max(9, 10+6) = 16           | 16 - 7 = 9         | min(5,9)=5  |
 * 
 * Final Min Difference: 5
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine you want to level out a row of plants by growing the short ones (adding k) and cutting the tall ones (subtracting k). 
 * By sorting, you can partition the plants: everything before the split gets tall (+k) and everything after gets short (-k). 
 * Test each split point to see which one makes the tallest and shortest as close as possible.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Sort the array. Initialize `ans = arr[n-1] - arr[0]`.
 * - Find boundaries: `smallest = arr[0] + k` and `largest = arr[n-1] - k`.
 * - For each index `i` from `1` to `n-1`:
 *   - Check `arr[i] - k >= 0`.
 *   - Compute current `min_val = min(smallest, arr[i] - k)`.
 *   - Compute current `max_val = max(largest, arr[i-1] + k)`.
 *   - Update `ans = min(ans, max_val - min_val)`.
 * - Time Complexity: O(N log N) (due to sorting).
 * - Space Complexity: O(1) auxiliary space.
 */
