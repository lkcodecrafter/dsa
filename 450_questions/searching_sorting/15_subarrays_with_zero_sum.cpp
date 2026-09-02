/*
    QUESTION    : Zero Sum Subarrays (Count total subarrays with sum 0)
    Company Tags: Amazon, Microsoft, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/zero-sum-subarrays1825/1
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Prefix sum with hash map frequency count
// S.C : O(N) - Hash map storing prefix sums
class Solution {
public:
    long long int findSubarray(vector<long long int> &arr, int n) {
        unordered_map<long long, int> prefixSumFreq;
        prefixSumFreq[0] = 1; // Base case

        long long currentSum = 0;
        long long totalCount = 0;

        for (int i = 0; i < n; i++) {
            currentSum += arr[i];

            // If prefix sum seen previously, add its frequency
            if (prefixSumFreq.find(currentSum) != prefixSumFreq.end()) {
                totalCount += prefixSumFreq[currentSum];
            }

            prefixSumFreq[currentSum]++;
        }

        return totalCount;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `prefixSumFreq[0] = 1`.
 * - `currentSum += arr[i]`.
 * - `totalCount += prefixSumFreq[currentSum]`.
 * - `prefixSumFreq[currentSum]++`.
 * - Time: O(N), Space: O(N).
 */
