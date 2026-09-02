/*
    QUESTION    : Maximum sum of increasing triplet in an array of n integers
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/maximum-sum-increasing-triplet-array-n-integers/
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Suffix max array + Self-balancing BST (std::set) for strictly smaller left element
// S.C : O(N)       - Suffix array and set
class Solution {
public:
    int maxTripletSum(int arr[], int n) {
        // Step 1: Precompute maximum element to the right of each element
        vector<int> suffixMax(n);
        suffixMax[n - 1] = arr[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            suffixMax[i] = max(suffixMax[i + 1], arr[i]);
        }

        set<int> leftSet;
        leftSet.insert(arr[0]);

        int maxTotalSum = 0;

        // Step 2: Iterate treating arr[i] as the middle element of the triplet
        for (int i = 1; i < n - 1; i++) {
            // Find largest element in leftSet strictly smaller than arr[i]
            auto it = leftSet.lower_bound(arr[i]);

            if (it != leftSet.begin() && suffixMax[i + 1] > arr[i]) {
                it--; // Largest element < arr[i]
                int leftVal = *it;
                int rightVal = suffixMax[i + 1];

                maxTotalSum = max(maxTotalSum, leftVal + arr[i] + rightVal);
            }

            leftSet.insert(arr[i]);
        }

        return maxTotalSum;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `suffixMax[i]` gives max element on right.
 * - `set::lower_bound` gives largest element on left strictly smaller than `arr[i]`.
 * - Time: O(N log N), Space: O(N).
 */
