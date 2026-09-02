/*
    QUESTION    : Maximum sum Rectangle (2D Kadane's Algorithm)
    Company Tags: Amazon, Microsoft, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximum-sum-rectangle2948/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(C^2 * R) - 2D Column compression + 1D Kadane's Algorithm
// S.C : O(R)       - Running row sums
class Solution {
private:
    int kadane(const vector<int>& arr, int n) {
        int maxSoFar = arr[0];
        int maxEndingHere = arr[0];

        for (int i = 1; i < n; i++) {
            maxEndingHere = max(arr[i], maxEndingHere + arr[i]);
            maxSoFar = max(maxSoFar, maxEndingHere);
        }

        return maxSoFar;
    }

public:
    int maximumRectangle(int R, int C, vector<vector<int>> M) {
        int maxSum = INT_MIN;

        for (int c1 = 0; c1 < C; c1++) {
            vector<int> rowSum(R, 0);

            for (int c2 = c1; c2 < C; c2++) {
                for (int i = 0; i < R; i++) {
                    rowSum[i] += M[i][c2];
                }

                maxSum = max(maxSum, kadane(rowSum, R));
            }
        }

        return maxSum;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Fix column pairs `(c1, c2)`, compress rows into `rowSum`, run Kadane's Algorithm.
 * - Time: O(C^2 * R), Space: O(R).
 */
