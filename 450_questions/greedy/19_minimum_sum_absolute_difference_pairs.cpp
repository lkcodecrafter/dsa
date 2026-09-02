/*
    QUESTION    : Minimum sum of absolute difference of pairs of two arrays
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/minimum-sum-absolute-difference-pairs-two-arrays/
    LeetCode    : https://leetcode.com/problems/minimum-absolute-sum-difference/
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting both arrays minimizes sum of pair-wise differences
// S.C : O(1)       - Constant auxiliary space
class Solution {
public:
    long long findMinSum(vector<int> &A, vector<int> &B, int N) {
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        long long minSum = 0;

        for (int i = 0; i < N; i++) {
            minSum += abs(A[i] - B[i]);
        }

        return minSum;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(A)`, `sort(B)`.
 * - `sum += abs(A[i] - B[i])`.
 * - Time: O(N log N), Space: O(1).
 */
