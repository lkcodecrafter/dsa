/*
    QUESTION    : Find pivot element in a sorted rotated array (Minimum Element / Inflection Point)
    Company Tags: Amazon, Microsoft, Adobe
    Link        : http://theoryofprogramming.com/2017/12/16/find-pivot-element-sorted-rotated-array/
    LeetCode    : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(log N) - Binary Search for point of inflection
// S.C : O(1)     - Constant auxiliary space
class Solution {
public:
    int findMin(int arr[], int n) {
        int low = 0, high = n - 1;

        while (low < high) {
            // If already completely sorted in current window
            if (arr[low] < arr[high]) {
                return arr[low];
            }

            int mid = low + (high - low) / 2;

            // If mid is greater than high, pivot (minimum) MUST be in the right half
            if (arr[mid] > arr[high]) {
                low = mid + 1;
            }
            // Otherwise, pivot is in the left half (including mid)
            else {
                high = mid;
            }
        }

        return arr[low];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `while (low < high)`:
 *     - If `arr[mid] > arr[high]`: `low = mid + 1;`
 *     - Else: `high = mid;`
 * - Return `arr[low]`.
 * - Time: O(log N), Space: O(1).
 */
