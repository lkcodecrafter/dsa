/*
 * QUESTION: Count Inversions in an array
 * Link: https://practice.geeksforgeeks.org/problems/inversion-of-array/0
 * 
 * Input: arr[] = {2, 4, 1, 3, 5}
 * Output: Inversion Count = 3
 * Explanation: The sequence has 3 inversions: (2, 1), (4, 1), (4, 3).
 */

#include <iostream>
#include <vector>

// Merges two sorted halves of the array and counts cross-inversions.
long long mergeAndCount(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right) {
    int i = left;      // Starting index for left subarray
    int j = mid + 1;   // Starting index for right subarray
    int k = left;      // Starting index to be filled in temp array
    long long inv_count = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // arr[i] > arr[j], which means there is an inversion.
            // Since the left subarray is sorted, all remaining elements 
            // in the left subarray (from index i to mid) are also greater than arr[j].
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }
    
    // Copy the remaining elements of left subarray (if any)
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    // Copy the remaining elements of right subarray (if any)
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    // Copy back the merged elements to original array
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
    
    return inv_count;
}

// Helper function that sorts the array and returns inversion count.
long long mergeSortAndCount(std::vector<int>& arr, std::vector<int>& temp, int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Count inversions in left half
        inv_count += mergeSortAndCount(arr, temp, left, mid);
        
        // Count inversions in right half
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right);
        
        // Count split inversions during merge
        inv_count += mergeAndCount(arr, temp, left, mid, right);
    }
    return inv_count;
}

// Wrapper function to find inversion count.
long long getInversionCount(std::vector<int>& arr) {
    std::vector<int> temp(arr.size());
    return mergeSortAndCount(arr, temp, 0, arr.size() - 1);
}

/*
 * DRY RUN (arr = {8, 4, 2, 1}):
 * 
 * | Step | Sub-range [L, R] | Left Half | Right Half | Merging | Inversion Contribution | Total Inv | Array State |
 * | :--- | :--------------- | :-------- | :--------- | :------ | :--------------------- | :-------- | :---------- |
 * | Init | [0, 3]           | {8, 4}    | {2, 1}     | -       | -                      | 0         | {8,4,2,1}   |
 * | 1    | [0, 1]           | {8}       | {4}        | 8 > 4   | mid - i + 1 = 0 - 0 + 1 = 1| 1      | {4,8,2,1}   |
 * | 2    | [2, 3]           | {2}       | {1}        | 2 > 1   | mid - i + 1 = 2 - 2 + 1 = 1| 2      | {4,8,1,2}   |
 * | 3    | [0, 3]           | {4, 8}    | {1, 2}     | Merge:  |                        |           |             |
 * |      |                  |           |            | 4 > 1   | mid - i + 1 = 1 - 0 + 1 = 2| 4      |             |
 * |      |                  |           |            | 4 > 2   | mid - i + 1 = 1 - 0 + 1 = 2| 6      | {1,2,4,8}   |
 * 
 * Total Inversion Count = 6
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Think of standing in a queue where taller people are in front of shorter ones. 
 * Split the queue in half. If someone in the right half (representing the later part of the array) 
 * is shorter than someone in the left half, they must jump over that person AND everyone standing behind them 
 * in the left half (since the left half is already sorted by height).
 * 
 * 1-MINUTE QUICK REVISION:
 * - Use a modified Merge Sort.
 * - In the `merge` function, maintain two pointers: `i` for left half, `j` for right half.
 * - If `arr[i] > arr[j]`, then all elements from `i` to `mid` are also greater than `arr[j]`.
 * - Add `(mid - i + 1)` to the inversion count and increment `j`.
 * - Time Complexity: O(N log N)
 * - Space Complexity: O(N) for the temp array used in merging.
 */
