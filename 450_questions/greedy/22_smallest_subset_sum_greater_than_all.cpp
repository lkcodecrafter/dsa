/*
    QUESTION    : Smallest subset with sum greater than all other elements
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/smallest-subset-with-greater-sum/1
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting descending + greedy largest element accumulation
// S.C : O(1)       - Constant auxiliary space
class Solution {
public:
    int minSubset(vector<int> &Arr, int N) {
        sort(Arr.rbegin(), Arr.rend()); // Sort descending

        long long totalSum = 0;
        for (int x : Arr) totalSum += x;

        long long currentSubsetSum = 0;
        int count = 0;

        for (int i = 0; i < N; i++) {
            currentSubsetSum += Arr[i];
            totalSum -= Arr[i];
            count++;

            // Check if current subset sum is strictly greater than sum of remaining elements
            if (currentSubsetSum > totalSum) {
                return count;
            }
        }

        return count;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(Arr.rbegin(), Arr.rend())`.
 * - Greedily take largest elements until `currentSubsetSum > remainingSum`.
 * - Time: O(N log N), Space: O(1).
 */
