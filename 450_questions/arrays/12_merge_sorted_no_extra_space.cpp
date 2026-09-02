/*
 * QUESTION: Merge 2 sorted arrays without using extra space.
 * Link: https://practice.geeksforgeeks.org/problems/merge-two-sorted-arrays5135/1
 * 
 * Input: arr1[] = {1, 3, 5, 7}, arr2[] = {0, 2, 6, 8, 9}
 * Output: arr1[] = {0, 1, 2, 3}, arr2[] = {5, 6, 7, 8, 9}
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Merges two sorted arrays in-place without using extra space.
void mergeSortedArrays(std::vector<int>& arr1, std::vector<int>& arr2) {
    int n = arr1.size();
    int m = arr2.size();
    
    int i = n - 1; // Start from the end of the first array
    int j = 0;     // Start from the beginning of the second array
    
    // Swap elements if they are out of relative order between arrays
    while (i >= 0 && j < m) {
        if (arr1[i] > arr2[j]) {
            std::swap(arr1[i], arr2[j]);
            i--;
            j++;
        } else {
            // Since arrays are already sorted, if arr1[i] <= arr2[j],
            // all elements to the left of i in arr1 are also <= arr2[j].
            break;
        }
    }
    
    // Sort both arrays to restore their sorted order individually
    std::sort(arr1.begin(), arr1.end());
    std::sort(arr2.begin(), arr2.end());
}

/*
 * DRY RUN (arr1 = {1, 3, 5, 7}, arr2 = {0, 2, 6, 8, 9}):
 * 
 * | Step | i | j | arr1[i] | arr2[j] | Comparison | Action               | arr1 State     | arr2 State     |
 * | :--- | :-| :-| :------ | :------ | :--------- | :------------------ | :------------- | :------------- |
 * | Init | 3 | 0 | 7       | 0       | 7 > 0      | Swap, i--, j++      | {1, 3, 5, 0}   | {7, 2, 6, 8, 9}|
 * | 1    | 2 | 1 | 5       | 2       | 5 > 2      | Swap, i--, j++      | {1, 3, 2, 0}   | {7, 5, 6, 8, 9}|
 * | 2    | 1 | 2 | 3       | 6       | 3 <= 6     | Break loop          | {1, 3, 2, 0}   | {7, 5, 6, 8, 9}|
 * | Sort | - | - | -       | -       | -          | Sort both vectors   | {0, 1, 2, 3}   | {5, 6, 7, 8, 9}|
 * 
 * Final state: arr1 = {0, 1, 2, 3}, arr2 = {5, 6, 7, 8, 9}
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine two files of sorted documents on adjacent desks. 
 * The left desk should have smaller numbers, and the right desk should have larger numbers. 
 * You look at the largest file on the left desk and the smallest on the right. 
 * If the left desk's largest is bigger than the right's smallest, swap them. 
 * Repeat until no swap is needed. Finally, sort the folders on each desk.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Use two pointers: `i = n - 1` (end of first array), `j = 0` (start of second array).
 * - While `i >= 0 && j < m`:
 *   - If `arr1[i] > arr2[j]`, swap `arr1[i]` with `arr2[j]`, decrement `i`, and increment `j`.
 *   - Else, break.
 * - Sort both arrays using `std::sort`.
 * - Time Complexity: O(min(N, M) + N log N + M log M)
 * - Space Complexity: O(1) auxiliary space.
 */
