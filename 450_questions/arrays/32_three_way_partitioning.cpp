/*
 * QUESTION: Three way partitioning of an array around a given range [a, b]
 * Link: https://practice.geeksforgeeks.org/problems/three-way-partitioning/1
 * 
 * Input: arr[] = {1, 14, 5, 20, 4, 2, 54, 20, 87, 98, 3, 1, 32}, range = [10, 20]
 * Output: Partitioned array where elements < 10 come first, [10, 20] second, and > 20 last.
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Partitions the array around the given range [a, b] in-place.
void threeWayPartition(std::vector<int>& arr, int a, int b) {
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;
    
    while (mid <= high) {
        if (arr[mid] < a) {
            std::swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] > b) {
            std::swap(arr[mid], arr[high]);
            high--;
        } else {
            mid++;
        }
    }
}

/*
 * DRY RUN (arr = {1, 14, 5, 22}, range = [10, 20]):
 * low = 0, mid = 0, high = 3, a = 10, b = 20
 * 
 * | Step | low | mid | high | arr[mid] | Condition/Action                     | Array State     |
 * | :--- | :-- | :-- | :--- | :------- | :----------------------------------- | :-------------- |
 * | Init | 0   | 0   | 3    | 1        | arr[mid] < 10 -> swap(low,mid), l++,m++| {1, 14, 5, 22}  |
 * | 1    | 1   | 1   | 3    | 14       | 10 <= 14 <= 20 -> mid++              | {1, 14, 5, 22}  |
 * | 2    | 1   | 2   | 3    | 5        | arr[mid] < 10 -> swap(low,mid), l++,m++| {1, 5, 14, 22}  |
 * | 3    | 2   | 3   | 3    | 22       | arr[mid] > 20 -> swap(mid,high), h-- | {1, 5, 14, 22}  |
 * | 4    | 2   | 3   | 2    | -        | mid > high -> loop ends              | {1, 5, 14, 22}  |
 * 
 * Partitioned: {1, 5, 14, 22} (elements < 10: {1, 5}; [10, 20]: {14}; > 20: {22})
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine a sorting tray with three sections. 
 * Small toys (< a) go in the left bin (`low`). 
 * Large toys (> b) go in the right bin (`high`). 
 * Medium toys go in the middle. 
 * You inspect elements one by one with `mid`, throwing them left or right and moving pointers accordingly.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize `low = 0`, `mid = 0`, `high = n - 1`.
 * - Loop while `mid <= high`:
 *   - If `arr[mid] < a`: `swap(arr[low], arr[mid])`, increment `low++` and `mid++`.
 *   - If `arr[mid] > b`: `swap(arr[mid], arr[high])`, decrement `high--`.
 *   - Otherwise: increment `mid++`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1) in-place.
 */
