/*
    QUESTION    : Find row with maximum no. of 1's
    Company Tags: Amazon, Microsoft, Snapdeal
    GfG Link    : https://practice.geeksforgeeks.org/problems/row-with-max-1s0023/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(R + C) - Start at top-right corner; each step moves left (c--) or down (r++)
// S.C : O(1)     - Constant auxiliary space
class Solution {
public:
    int rowWithMax1s(vector<vector<int>> &arr, int n, int m) {
        int maxRowIdx = -1;
        int r = 0;
        int c = m - 1; // Start from top-right corner

        while (r < n && c >= 0) {
            // If current cell is 1, it could be a row with more 1s
            if (arr[r][c] == 1) {
                maxRowIdx = r; // Update best row
                c--;           // Move left to see if this row has even more 1s
            } else {
                r++;           // Cell is 0; current row cannot beat maxRowIdx, move down
            }
        }

        return maxRowIdx;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TOP-RIGHT STEPPING
 * ============================================================================
 *
 * Matrix:
 * Row 0: [ 0,  1,  1,  1 ]  <- Start at (0, 3): val=1 -> maxRow=0, col=2
 *                                                val=1 -> maxRow=0, col=1
 *                                                val=1 -> maxRow=0, col=0
 *                                                val=0 -> row=1
 * Row 1: [ 0,  0,  1,  1 ]  <- At (1, 0): val=0 -> row=2
 * Row 2: [ 1,  1,  1,  1 ]  <- At (2, 0): val=1 -> maxRow=2, col=-1 (Stop!)
 * Row 3: [ 0,  0,  0,  0 ]
 * Result: Row 2 has the most 1s!
 *
 * ============================================================================
 * DRY RUN (Matrix 3x3)
 * arr = {{0, 1, 1}, {0, 0, 1}, {1, 1, 1}}
 * ============================================================================
 * | Step | (r, c) | Value | Action Taken                    | maxRowIdx | Next Cell |
 * | :--- | :----- | :---- | :------------------------------ | :-------- | :-------- |
 * | 1    | (0, 2) | 1     | Found 1 -> maxRowIdx=0, col--   | 0         | (0, 1)    |
 * | 2    | (0, 1) | 1     | Found 1 -> maxRowIdx=0, col--   | 0         | (0, 0)    |
 * | 3    | (0, 0) | 0     | Found 0 -> move down (row++)    | 0         | (1, 0)    |
 * | 4    | (1, 0) | 0     | Found 0 -> move down (row++)    | 0         | (2, 0)    |
 * | 5    | (2, 0) | 1     | Found 1 -> maxRowIdx=2, col--   | 2         | (2, -1)   |
 * | End  | c < 0  | -     | Column out of bounds -> Return 2| 2         | -         |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Staircase Slide"
 * Start at the top-right corner of the staircase.
 * If you see a `1`, push the barrier left (`c--`) and record this row.
 * If you hit a `0`, step down a step (`r++`) to find a row that crosses
 * further to the left.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Start at `r = 0, c = m - 1` (top-right).
 * - If `arr[r][c] == 1`: update `maxRowIdx = r` and move left (`c--`).
 * - If `arr[r][c] == 0`: move down (`r++`).
 * - We only move left and down at most `R + C` times total.
 * - Time Complexity: O(R + C), Space Complexity: O(1).
 */
