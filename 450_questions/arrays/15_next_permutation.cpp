/*
 * QUESTION: Next Permutation
 * Link: https://leetcode.com/problems/next-permutation/
 * 
 * Input: arr[] = {1, 2, 3}
 * Output: arr[] = {1, 3, 2}
 * 
 * Input: arr[] = {3, 2, 1}
 * Output: arr[] = {1, 2, 3}
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Rearranges the array into the lexicographically next greater permutation.
void nextPermutation(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;
    
    // Step 1: Find the pivot index (first element from right that is smaller than its next element)
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }
    
    // If the entire array is sorted in descending order, the next permutation is the sorted ascending order
    if (i >= 0) {
        // Step 2: Find the element from the right that is strictly greater than arr[i]
        int j = n - 1;
        while (arr[j] <= arr[i]) {
            j--;
        }
        // Swap them
        std::swap(arr[i], arr[j]);
    }
    
    // Step 3: Reverse the elements after the pivot index to get the smallest possible permutation
    std::reverse(arr.begin() + i + 1, arr.end());
}

/*
 * DRY RUN (arr = {1, 3, 5, 4, 2}):
 * 
 * | Step | Variable States / Actions                                                                 | Array State     |
 * | :--- | :---------------------------------------------------------------------------------------- | :-------------- |
 * | Init | n = 5                                                                                     | {1, 3, 5, 4, 2} |
 * | 1    | Find i: scan right-to-left. 2 < 4 (no), 4 < 5 (no), 5 < 3 (no, 3 < 5! Yes). i = 1 (val 3) | {1, 3, 5, 4, 2} |
 * | 2    | Find j: scan right-to-left. Is 2 > 3 (no), 4 > 3 (Yes!). j = 3 (val 4).                    | {1, 3, 5, 4, 2} |
 * | 3    | Swap arr[i] (3) and arr[j] (4).                                                           | {1, 4, 5, 3, 2} |
 * | 4    | Reverse subarray from index i + 1 (2) to end: reverse {5, 3, 2} -> {2, 3, 5}.             | {1, 4, 2, 3, 5} |
 * 
 * Next Permutation: {1, 4, 2, 3, 5}
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine finding the next larger number using the same digits. 
 * Scan from right to left until you find a digit that drops (`arr[i] < arr[i+1]`). That's your inflection point. 
 * Find the smallest digit to its right that is larger than the inflection digit. Swap them. 
 * Now sort (or reverse, since it's descending) everything to the right to make it as small as possible.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Scan from right to left to find the first index `i` where `arr[i] < arr[i + 1]`.
 * - If `i < 0`, reverse the entire array and return.
 * - Else, scan from right to left to find the first index `j` where `arr[j] > arr[i]`.
 * - Swap `arr[i]` and `arr[j]`.
 * - Reverse the subarray from `i + 1` to `end()`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1) in-place.
 */
