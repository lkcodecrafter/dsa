/*
    QUESTION    : Chocolate Distribution Problem
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/chocolate-distribution-problem3825/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting + sliding window of size M to minimize (max - min)
// S.C : O(1)       - Constant auxiliary space
class Solution {
public:
    long long findMinDiff(vector<long long> a, long long n, long long m) {
        if (m == 0 || n == 0 || m > n) return 0;

        sort(a.begin(), a.end());

        long long minDiff = LLONG_MAX;

        // Slide window of size m across sorted array
        for (long long i = 0; i + m - 1 < n; i++) {
            long long diff = a[i + m - 1] - a[i];
            minDiff = min(minDiff, diff);
        }

        return minDiff;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(a)`.
 * - Window of size `m`: `minDiff = min(minDiff, a[i + m - 1] - a[i])`.
 * - Time: O(N log N), Space: O(1).
 */
