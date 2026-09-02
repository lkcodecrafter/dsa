/*
 * QUESTION: Median of 2 sorted arrays of equal size
 * Link: https://practice.geeksforgeeks.org/problems/find-the-median0527/1
 * 
 * Input: A[] = {1, 12, 15, 26, 38}, B[] = {2, 13, 17, 30, 45}
 * Output: Median = 16.0
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// Returns the median of two sorted vectors of equal size.
double getMedianEqualSize(const std::vector<int>& A, const std::vector<int>& B) {
    int n = A.size();
    if (n == 0) return 0;
    
    int low = 0;
    int high = n;
    
    while (low <= high) {
        int i = low + (high - low) / 2; // Partition index in array A
        int j = n - i;                  // Partition index in array B (since i + j = n)
        
        // Find boundary values on both sides of partition
        int l1 = (i == 0) ? INT_MIN : A[i - 1];
        int r1 = (i == n) ? INT_MAX : A[i];
        
        int l2 = (j == 0) ? INT_MIN : B[j - 1];
        int r2 = (j == n) ? INT_MAX : B[j];
        
        // Check if we found the correct partition
        if (l1 <= r2 && l2 <= r1) {
            // Since total size is 2n (always even), median is average of max of left and min of right
            return (std::max(l1, l2) + std::min(r1, r2)) / 2.0;
        }
        // If left part of A is too large, move partition left in A
        else if (l1 > r2) {
            high = i - 1;
        }
        // If left part of B is too large, move partition right in A
        else {
            low = i + 1;
        }
    }
    
    return 0.0;
}

/*
 * DRY RUN (A = {1, 15, 26}, B = {2, 13, 17}): n = 3, low = 0, high = 3
 * 
 * | Step | low | high | i (partition A) | j (partition B) | l1 (A[i-1]) | r1 (A[i]) | l2 (B[j-1]) | r2 (B[j]) | Condition (l1 <= r2 && l2 <= r1) | Update                |
 * | :--- | :-- | :--- | :-------------- | :-------------- | :---------- | :-------- | :---------- | :-------- | :------------------------------- | :-------------------- |
 * | 1    | 0   | 3    | 1               | 2               | A[0] = 1    | A[1] = 15 | B[1] = 13   | B[2] = 17 | 1 <= 17 && 13 <= 15 -> True      | Found correct split!  |
 * 
 * Result: (max(1, 13) + min(15, 17)) / 2.0 = (13 + 15) / 2.0 = 14.0
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine splitting two card decks into two halves: Left and Right. 
 * You want all cards on the Left to be smaller than all cards on the Right. 
 * You binary-search the split point of the first deck. 
 * This automatically fixes the split point of the second deck. 
 * Compare the boundary cards (`l1, r1` and `l2, r2`). 
 * If they cross correctly (`l1 <= r2 && l2 <= r1`), you take the average of the largest on Left and smallest on Right.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Perform binary search on the partition index `i` of array A from `0` to `n`.
 * - Partition index of B is `j = n - i`.
 * - Read values: `l1 = A[i-1]`, `r1 = A[i]`, `l2 = B[j-1]`, `r2 = B[j]` (handle boundaries with `INT_MIN` / `INT_MAX`).
 * - If `l1 <= r2 && l2 <= r1`, return `(max(l1, l2) + min(r1, r2)) / 2.0`.
 * - Else if `l1 > r2`, search in left half (`high = i - 1`).
 * - Else, search in right half (`low = i + 1`).
 * - Time Complexity: O(log N)
 * - Space Complexity: O(1)
 */
