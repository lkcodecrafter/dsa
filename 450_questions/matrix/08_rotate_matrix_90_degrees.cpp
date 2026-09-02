/*
    QUESTION    : Rotate matrix by 90 degrees clockwise (in-place)
    Company Tags: Amazon, Microsoft, Samsung, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/rotate-by-90-degree-1587115621/1
    LeetCode    : https://leetcode.com/problems/rotate-image/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Transpose matrix (N^2 / 2 swaps) + Reverse each row (N * (N / 2) swaps)
// S.C : O(1)   - Done completely in-place without auxiliary matrix
class Solution {
public:
    void rotate(vector<vector<int>> &matrix) {
        int n = matrix.size();

        // Step 1: Transpose the matrix (Swap matrix[i][j] with matrix[j][i])
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: Reverse each row
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 90-DEGREE ROTATION
 * ============================================================================
 *
 * Original:            Step 1: Transpose:         Step 2: Reverse Rows (Final):
 * [ 1, 2, 3 ]          [ 1, 4, 7 ]                [ 7, 4, 1 ]
 * [ 4, 5, 6 ]   --->   [ 2, 5, 8 ]         --->   [ 8, 5, 2 ]
 * [ 7, 8, 9 ]          [ 3, 6, 9 ]                [ 9, 6, 3 ]
 *
 * Notice:
 * 1st row [1, 2, 3] becomes 3rd col (Top to Bottom).
 *
 * ============================================================================
 * DRY RUN (3x3 Matrix)
 * ============================================================================
 * | Step | Operation             | Matrix State                                      |
 * | :--- | :-------------------- | :------------------------------------------------ |
 * | Init | Input                 | {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}                 |
 * | 1    | Transpose (i=0, j=1)  | Swap (0,1) with (1,0) -> {{1, 4, 3}, {2, 5, 6}...}|
 * | 2    | Transpose (i=0, j=2)  | Swap (0,2) with (2,0) -> {{1, 4, 7}, ... {3, 8, 9}}|
 * | 3    | Transpose (i=1, j=2)  | Swap (1,2) with (2,1) -> Transposed complete      |
 * | 4    | Reverse Row 0         | {1, 4, 7} -> {7, 4, 1}                            |
 * | 5    | Reverse Row 1         | {2, 5, 8} -> {8, 5, 2}                            |
 * | 6    | Reverse Row 2         | {3, 6, 9} -> {9, 6, 3}                            |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Mirror and Flip Dance"
 * To rotate an image 90° clockwise:
 * 1. Mirror it across the main diagonal (Transpose rows to columns).
 * 2. Flip it horizontally (Reverse each row left-to-right).
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - In-place 90° Clockwise Rotation:
 *     1. Transpose: `swap(matrix[i][j], matrix[j][i])` for all `j > i`.
 *     2. Reverse Rows: `reverse(matrix[i].begin(), matrix[i].end())` for each row.
 * - Note for 90° Anti-Clockwise:
 *     1. Transpose first.
 *     2. Reverse columns (or reverse each column top-to-bottom).
 * - Time Complexity: O(N^2), Space Complexity: O(1).
 */
