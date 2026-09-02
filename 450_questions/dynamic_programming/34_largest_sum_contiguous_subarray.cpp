/*
    QUESTION    : Kadane's Algorithm (Largest Sum Contiguous Subarray)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/kadanes-algorithm-1587115620/1
    LeetCode    : https://leetcode.com/problems/maximum-subarray/
*/

#include <iostream>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Kadane's Algorithm
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    long long maxSubarraySum(int arr[], int n) {
        long long maxSoFar = arr[0];
        long long maxEndingHere = arr[0];

        for (int i = 1; i < n; i++) {
            maxEndingHere = max((long long)arr[i], maxEndingHere + arr[i]);
            maxSoFar = max(maxSoFar, maxEndingHere);
        }

        return maxSoFar;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `maxEnding = max(arr[i], maxEnding + arr[i])`.
 * - `maxSoFar = max(maxSoFar, maxEnding)`.
 * - Time: O(N), Space: O(1).
 */
