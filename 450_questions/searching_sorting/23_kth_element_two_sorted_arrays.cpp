/*
    QUESTION    : K-th Element of Two Sorted Arrays
    Company Tags: Amazon, Microsoft, Google, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1221/1
    LeetCode    : https://leetcode.com/problems/median-of-two-sorted-arrays/
*/

#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(log(min(N, M))) - Binary search on partition cut in the smaller array
// S.C : O(1)              - Constant auxiliary space
class Solution {
public:
    int kthElement(int arr1[], int arr2[], int n, int m, int k) {
        // Ensure binary search is performed on the smaller array
        if (n > m) {
            return kthElement(arr2, arr1, m, n, k);
        }

        int low = max(0, k - m);
        int high = min(k, n);

        while (low <= high) {
            int cut1 = low + (high - low) / 2;
            int cut2 = k - cut1;

            int left1 = (cut1 == 0) ? INT_MIN : arr1[cut1 - 1];
            int left2 = (cut2 == 0) ? INT_MIN : arr2[cut2 - 1];

            int right1 = (cut1 == n) ? INT_MAX : arr1[cut1];
            int right2 = (cut2 == m) ? INT_MAX : arr2[cut2];

            if (left1 <= right2 && left2 <= right1) {
                // Valid partition found!
                return max(left1, left2);
            } else if (left1 > right2) {
                high = cut1 - 1; // Take fewer elements from arr1
            } else {
                low = cut1 + 1; // Take more elements from arr1
            }
        }

        return 1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Binary search partition `cut1` on smaller array with `cut2 = k - cut1`.
 * - Valid partition: `left1 <= right2 && left2 <= right1`.
 * - Return `max(left1, left2)`.
 * - Time: O(log(min(N, M))), Space: O(1).
 */
