/*
 * QUESTION: Move all the negative elements to one side of the array
 * Link: https://www.geeksforgeeks.org/move-negative-numbers-beginning-positive-end-constant-extra-space/
 * 
 * Input: arr[] = {-12, 11, -13, -5, 6, -7, 5, -3, -6}
 * Output: arr[] = {-12, -13, -5, -7, -3, -6, 11, 5, 6} (Order doesn't matter)
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Moves all negative numbers to the beginning of the array.
void moveNegatives(std::vector<int>& arr) {
    int pivot_idx = 0; // Pointer where the next negative number should be swapped
    
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] < 0) {
            std::swap(arr[i], arr[pivot_idx]);
            pivot_idx++;
        }
    }
}

/*
 * DRY RUN:
 * Initial Array: {11, -13, -5, 6}
 * 
 * | Step | Index i | arr[i] | pivot_idx | Action                      | Array State      |
 * | :--- | :------ | :----- | :-------- | :-------------------------- | :--------------- |
 * | Init | -       | -      | 0         | Start loop                  | {11, -13, -5, 6} |
 * | 1    | 0       | 11     | 0         | positive -> no swap         | {11, -13, -5, 6} |
 * | 2    | 1       | -13    | 0         | negative -> swap(arr[1], [0])| {-13, 11, -5, 6} |
 * |      |         |        | 1         | increment pivot_idx to 1    |                  |
 * | 3    | 2       | -5     | 1         | negative -> swap(arr[2], [1])| {-13, -5, 11, 6} |
 * |      |         |        | 2         | increment pivot_idx to 2    |                  |
 * | 4    | 3       | 6      | 2         | positive -> no swap         | {-13, -5, 11, 6} |
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Think of it as a line of people where children (negative values) need to stand at the front.
 * You keep a pointer `pivot_idx` at the first adult. 
 * Every time you spot a child down the line, you swap them with the first adult, moving the boundary.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Maintain a pointer `pivot_idx = 0` to track the boundary of negative numbers.
 * - Iterate through the array using `i`.
 * - If `arr[i] < 0`, swap `arr[i]` with `arr[pivot_idx]` and increment `pivot_idx`.
 * - Time Complexity: O(N) since we do a single scan.
 * - Space Complexity: O(1) as we swap in-place.
 */
