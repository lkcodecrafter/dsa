/*
    QUESTION    : Minimum removals from array to make max - min <= k
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-removals-from-array-to-make-max-min-k/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting + Two-pointer sliding window to maximize retained window
// S.C : O(1)       - Constant auxiliary space
class Solution {
public:
    int removals(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());

        int maxWindow = 1;
        int i = 0, j = 0;

        while (j < n) {
            if (arr[j] - arr[i] <= k) {
                maxWindow = max(maxWindow, j - i + 1);
                j++;
            } else {
                i++;
            }
        }

        return n - maxWindow;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(arr)`. Two pointers `i = 0, j = 0`.
 * - While `arr[j] - arr[i] <= k`: `maxWindow = max(maxWindow, j - i + 1); j++;` else `i++`.
 * - Return `n - maxWindow`.
 * - Time: O(N log N), Space: O(1).
 */
