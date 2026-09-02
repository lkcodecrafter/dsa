/*
 * QUESTION: Sort an array of 0s, 1s, and 2s without using sorting algorithms.
 * Link: https://practice.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s/0
 * 
 * Input: arr[] = {0, 2, 1, 2, 0, 1}
 * Output: arr[] = {0, 0, 1, 1, 2, 2}
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Sorts the array of 0s, 1s, and 2s in-place.
void sort012(std::vector<int>& arr) {
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;
    
    // Dutch National Flag Algorithm
    while (mid <= high) {
        if (arr[mid] == 0) {
            std::swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] == 1) {
            mid++;
        } else { // arr[mid] == 2
            std::swap(arr[mid], arr[high]);
            high--;
        }
    }
}

/*
 * DRY RUN:
 * Initial Array: {0, 2, 1, 2, 0, 1}
 * Pointers: low = 0, mid = 0, high = 5
 * 
 * | Step | low | mid | high | arr[mid] | Action                     | Array State           |
 * | :--- | :-- | :-- | :--- | :------- | :------------------------- | :-------------------- |
 * | Init | 0   | 0   | 5    | 0        | arr[mid]==0: swap(low,mid) | {0, 2, 1, 2, 0, 1}    |
 * | 1    | 1   | 1   | 5    | 2        | arr[mid]==2: swap(mid,high)| {0, 1, 1, 2, 0, 2}    |
 * | 2    | 1   | 1   | 4    | 1        | arr[mid]==1: mid++         | {0, 1, 1, 2, 0, 2}    |
 * | 3    | 1   | 2   | 4    | 1        | arr[mid]==1: mid++         | {0, 1, 1, 2, 0, 2}    |
 * | 4    | 1   | 3   | 4    | 2        | arr[mid]==2: swap(mid,high)| {0, 1, 1, 0, 2, 2}    |
 * | 5    | 1   | 3   | 3    | 0        | arr[mid]==0: swap(low,mid) | {0, 0, 1, 1, 2, 2}    |
 * | 6    | 2   | 4   | 3    | -        | mid > high -> Loop ends    | {0, 0, 1, 1, 2, 2}    |
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine a sorting machine with three zones: Left for red (0s), Middle for white (1s), Right for blue (2s).
 * `low` points to where the next 0 goes.
 * `high` points to where the next 2 goes.
 * `mid` is the inspector scanning the items. If it's red (0), send left; if blue (2), send right; if white (1), leave it.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize: `low = 0`, `mid = 0`, `high = n - 1`.
 * - Loop while `mid <= high`:
 *   - If `arr[mid] == 0`: `swap(arr[low], arr[mid])`, increment `low++` and `mid++`.
 *   - If `arr[mid] == 1`: increment `mid++`.
 *   - If `arr[mid] == 2`: `swap(arr[mid], arr[high])`, decrement `high--`.
 * - Time Complexity: O(N) in a single pass.
 * - Space Complexity: O(1) in-place.
 */
