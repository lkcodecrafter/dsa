/*
    QUESTION    : Search in Rotated Sorted Array
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/search-in-a-rotated-array4618/1
    LeetCode    : https://leetcode.com/problems/search-in-rotated-sorted-array/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(log N) - Binary search leveraging the property that at least one half is always sorted
// S.C : O(1)     - Constant auxiliary space
class Solution {
public:
    int search(int A[], int l, int h, int key) {
        while (l <= h) {
            int mid = l + (h - l) / 2;

            if (A[mid] == key) return mid;

            // Check if left half [l...mid] is sorted
            if (A[l] <= A[mid]) {
                if (key >= A[l] && key < A[mid]) {
                    h = mid - 1; // Key lies in sorted left half
                } else {
                    l = mid + 1; // Key lies in right half
                }
            }
            // Otherwise, right half [mid...h] MUST be sorted
            else {
                if (key > A[mid] && key <= A[h]) {
                    l = mid + 1; // Key lies in sorted right half
                } else {
                    h = mid - 1; // Key lies in left half
                }
            }
        }

        return -1; // Element not found
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - In rotated sorted array: one half is ALWAYS strictly sorted.
 * - If `A[l] <= A[mid]`: left half sorted $\rightarrow$ if `key >= A[l] && key < A[mid]`, `h = mid - 1`; else `l = mid + 1`.
 * - Else: right half sorted $\rightarrow$ if `key > A[mid] && key <= A[h]`, `l = mid + 1`; else `h = mid - 1`.
 * - Time: O(log N), Space: O(1).
 */
