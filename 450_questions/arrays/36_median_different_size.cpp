/*
 * QUESTION: Median of 2 sorted arrays of different size
 * Link: https://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/
 * 
 * Input: A[] = {900}, B[] = {5, 8, 10, 20}
 * Output: Median = 10.0
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// Returns the median of two sorted vectors of possibly different sizes.
double getMedianDifferentSize(const std::vector<int>& A, const std::vector<int>& B) {
    // We always perform binary search on the smaller array to ensure O(log(min(N, M)))
    if (A.size() > B.size()) {
        return getMedianDifferentSize(B, A);
    }
    
    int n = A.size();
    int m = B.size();
    
    int low = 0;
    int high = n;
    
    while (low <= high) {
        int i = low + (high - low) / 2;     // Partition index in array A
        int j = (n + m + 1) / 2 - i;        // Partition index in array B
        
        // Find boundary values around partition
        int l1 = (i == 0) ? INT_MIN : A[i - 1];
        int r1 = (i == n) ? INT_MAX : A[i];
        
        int l2 = (j == 0) ? INT_MIN : B[j - 1];
        int r2 = (j == m) ? INT_MAX : B[j];
        
        if (l1 <= r2 && l2 <= r1) {
            // If total size is odd, the median is the maximum of the left elements
            if ((n + m) % 2 != 0) {
                return std::max(l1, l2);
            }
            // If total size is even, the median is the average of max(left) and min(right)
            return (std::max(l1, l2) + std::min(r1, r2)) / 2.0;
        }
        else if (l1 > r2) {
            high = i - 1; // Partition A is too far right
        } else {
            low = i + 1;  // Partition A is too far left
        }
    }
    
    return 0.0;
}

/*
 * DRY RUN (A = {900}, B = {5, 8, 10, 20}): n = 1, m = 4, low = 0, high = 1
 * since A.size() (1) < B.size() (4), we search on A.
 * 
 * | Step | low | high | i (partition A) | j (partition B) | l1 (A[i-1]) | r1 (A[i]) | l2 (B[j-1]) | r2 (B[j]) | Condition (l1 <= r2 && l2 <= r1) | Update                |
 * | :--- | :-- | :--- | :-------------- | :-------------- | :---------- | :-------- | :---------- | :-------- | :------------------------------- | :-------------------- |
 * | 1    | 0   | 1    | 0               | (1+4+1)/2 - 0 = 3| INT_MIN    | A[0]=900  | B[2] = 10   | B[3] = 20 | INT_MIN<=20 && 10<=900 -> True   | Found correct split!  |
 * 
 * Total size is 5 (odd), so median is max(l1, l2) = max(INT_MIN, 10) = 10.0
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine merging two queues of people of unequal sizes into a left half and a right half. 
 * To save time, always adjust the divider in the shorter queue (`A`). 
 * The divider in the longer queue (`B`) adjusts automatically to keep the left side exactly half of the total. 
 * Cross-check the boundary elements. If they align, retrieve the median based on whether the total size is odd or even.
 * 
 * 1-MINUTE QUICK REVISION:
 * - If `A.size() > B.size()`, swap arguments to ensure we binary search on the smaller array.
 * - Initialize `low = 0`, `high = n`.
 * - While `low <= high`:
 *   - Set `i = (low + high) / 2` and `j = (n + m + 1) / 2 - i`.
 *   - Read boundary values: `l1 = A[i-1]`, `r1 = A[i]`, `l2 = B[j-1]`, `r2 = B[j]` (handle indices).
 *   - If `l1 <= r2 && l2 <= r1`:
 *     - If `(n + m) % 2 != 0`, return `max(l1, l2)`.
 *     - Else, return `(max(l1, l2) + min(r1, r2)) / 2.0`.
 *   - If `l1 > r2`, decrement `high = i - 1`.
 *   - Otherwise, increment `low = i + 1`.
 * - Time Complexity: O(log(min(N, M)))
 * - Space Complexity: O(1)
 */
