/*
    QUESTION    : Find a specific pair in matrix (Find max value of mat[c][d] - mat[a][b] such that c > a and d > b)
    Company Tags: Amazon, Adobe
    GfG Link    : https://www.geeksforgeeks.org/find-a-specific-pair-in-matrix/
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Precomputes 2D suffix maximum matrix `maxArr` from bottom-right to top-left
// S.C : O(N^2) - Auxiliary space for suffix maximum DP matrix
class Solution {
public:
    int findMaxValue(vector<vector<int>> &mat, int N) {
        int maxValue = INT_MIN;

        // maxArr[i][j] stores the maximum element in submatrix from (i, j) to (N-1, N-1)
        vector<vector<int>> maxArr(N, vector<int>(N, 0));

        // 1. Initialize bottom-right corner
        maxArr[N - 1][N - 1] = mat[N - 1][N - 1];

        // 2. Preprocess last row
        int maxVal = mat[N - 1][N - 1];
        for (int j = N - 2; j >= 0; j--) {
            maxVal = max(maxVal, mat[N - 1][j]);
            maxArr[N - 1][j] = maxVal;
        }

        // 3. Preprocess last column
        maxVal = mat[N - 1][N - 1];
        for (int i = N - 2; i >= 0; i--) {
            maxVal = max(maxVal, mat[i][N - 1]);
            maxArr[i][N - 1] = maxVal;
        }

        // 4. Fill rest of the 2D DP suffix matrix from bottom-right towards top-left
        for (int i = N - 2; i >= 0; i--) {
            for (int j = N - 2; j >= 0; j--) {
                // Check if current pair (mat[i][j], maxArr[i+1][j+1]) yields a larger difference
                if (maxArr[i + 1][j + 1] - mat[i][j] > maxValue) {
                    maxValue = maxArr[i + 1][j + 1] - mat[i][j];
                }

                // Update maxArr[i][j] as the max of current, right, down, and diagonal
                maxArr[i][j] = max({mat[i][j], maxArr[i + 1][j], maxArr[i][j + 1]});
            }
        }

        return maxValue;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 2D SUFFIX MAXIMUM MATRIX
 * ============================================================================
 *
 * Input mat (5x5):
 * [ 1,  2, -1, -4, -20 ]
 * [-8, -3,  4,  2,   1 ]
 * [ 3,  8,  6,  1,   3 ]
 * [-4, -1,  1,  7,  -6 ]
 * [ 0, -4, 10, -5,   1 ]
 *
 * For cell (a, b) = (0, 0) with value 1:
 * The bottom-right submatrix starting at (1, 1) has max element = 10 (at 4, 2)
 * Difference = 10 - 1 = 9.
 *
 * Max difference overall = 18 (from mat[1][0] = -8 and max in submatrix = 10 -> 10 - (-8) = 18)!
 *
 * ============================================================================
 * DRY RUN (3x3 Matrix)
 * mat = {{ 1,  2, 3},
 *        { 4, -5, 6},
 *        { 7,  8, 9}}
 * ============================================================================
 * | (i, j) | mat[i][j] | maxArr[i+1][j+1] (Max in lower-right) | Diff (maxArr - mat) | maxValue Updated |
 * | :----- | :-------- | :------------------------------------ | :------------------ | :--------------- |
 * | (1, 1) | -5        | maxArr[2][2] = 9                      | 9 - (-5) = 14       | 14               |
 * | (1, 0) | 4         | maxArr[2][1] = 9                      | 9 - 4 = 5           | 14               |
 * | (0, 1) | 2         | maxArr[1][2] = 9                      | 9 - 2 = 7           | 14               |
 * | (0, 0) | 1         | maxArr[1][1] = 9                      | 9 - 1 = 8           | 14               |
 *
 * Answer = 14.
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Mountain Peak Panorama"
 * Stand at cell `(i, j)`. To find the biggest profit, look strictly southeast
 * at the tallest mountain peak (`maxArr[i+1][j+1]`).
 * Precalculate all southeastern highest peaks starting from the bottom-right corner.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - We need $\max(mat[c][d] - mat[a][b])$ with $c > a$ and $d > b$.
 * - Create a 2D DP array `maxArr` where `maxArr[i][j] = max` in submatrix $(i, j)$ to $(N-1, N-1)$.
 * - Iterate from $N-2$ down to $0$:
 *     - Evaluate $\text{candidate} = maxArr[i + 1][j + 1] - mat[i][j]$.
 *     - Update `maxArr[i][j] = max({mat[i][j], maxArr[i+1][j], maxArr[i][j+1]})`.
 * - Time: O(N^2), Space: O(N^2).
 */
