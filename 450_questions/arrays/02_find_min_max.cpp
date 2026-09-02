/*
 * QUESTION: Find the maximum and minimum element in an array
 * Link: https://www.geeksforgeeks.org/maximum-and-minimum-in-an-array/
 * 
 * Input: arr[] = {3, 5, 4, 1, 9}
 * Output: Minimum: 1, Maximum: 9
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

// Returns a pair of {min, max} elements of the vector.
std::pair<int, int> getMinMax(const std::vector<int>& arr) {
    if (arr.empty()) {
        return {-1, -1}; // Handle edge case of empty array
    }
    
    int min_val = arr[0];
    int max_val = arr[0];
    
    // Traverse the array starting from the second element
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < min_val) {
            min_val = arr[i]; // Update minimum
        } else if (arr[i] > max_val) {
            max_val = arr[i]; // Update maximum
        }
    }
    
    return {min_val, max_val};
}

/*
 * DRY RUN:
 * Initial Array: {3, 5, 4, 1, 9}
 * Initial State: min_val = 3, max_val = 3
 * 
 * | Step | Index | Value | min_val | max_val | Action/Update                 |
 * | :--- | :---- | :---- | :------ | :------ | :---------------------------- |
 * | Init | -     | -     | 3       | 3       | Initialized to arr[0]         |
 * | 1    | 1     | 5     | 3       | 5       | arr[i] > max_val -> update max|
 * | 2    | 2     | 4     | 3       | 5       | No update                     |
 * | 3    | 3     | 1     | 1       | 5       | arr[i] < min_val -> update min|
 * | 4    | 4     | 9     | 1       | 9       | arr[i] > max_val -> update max|
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine keeping two boxes: "Smallest" and "Largest". 
 * Initially, you put the first item in both boxes. 
 * For every new item, if it's lighter than what's in "Smallest", swap it. 
 * If it's heavier than what's in "Largest", swap it.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize `min_val` and `max_val` with the first element.
 * - Iterate from `index 1` to `n-1`.
 * - Update `min_val` if the current element is smaller; update `max_val` if the current element is larger.
 * - Time Complexity: O(N) since we loop through the array once.
 * - Space Complexity: O(1) as we only use two variables.
 */
