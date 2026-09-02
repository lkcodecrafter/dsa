/*
    QUESTION    : Smallest sum contiguous subarray (Inverted Kadane's Algorithm)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/smallest-sum-contiguous-subarray/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Inverted Kadane's Algorithm
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int smallestSumSubarray(vector<int>& a) {
        int minSoFar = a[0];
        int minEndingHere = a[0];

        for (int i = 1; i < a.size(); i++) {
            minEndingHere = min(a[i], minEndingHere + a[i]);
            minSoFar = min(minSoFar, minEndingHere);
        }

        return minSoFar;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `minEnding = min(a[i], minEnding + a[i])`.
 * - `minSoFar = min(minSoFar, minEnding)`.
 * - Time: O(N), Space: O(1).
 */
