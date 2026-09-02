/*
    QUESTION    : Maximum path sum in matrix (Falling Path Sum)
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/path-in-matrix3805/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * N) - Row-by-row DP from bottom to top
// S.C : O(N)     - 1D DP row
class Solution {
public:
    int maximumPath(int N, vector<vector<int>> Matrix) {
        vector<int> prev = Matrix[0];

        for (int i = 1; i < N; i++) {
            vector<int> curr(N, 0);

            for (int j = 0; j < N; j++) {
                int up = prev[j];
                int upLeft = (j > 0) ? prev[j - 1] : 0;
                int upRight = (j < N - 1) ? prev[j + 1] : 0;

                curr[j] = Matrix[i][j] + max({up, upLeft, upRight});
            }

            prev = curr;
        }

        return *max_element(prev.begin(), prev.end());
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `curr[j] = Matrix[i][j] + max({prev[j], prev[j-1], prev[j+1]})`.
 * - Return `max_element` in final row.
 * - Time: O(N^2), Space: O(N).
 */
