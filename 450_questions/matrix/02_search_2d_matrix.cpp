/*
    QUESTION    : Search an element in a matrix
    Company Tags: Amazon, Microsoft, Paytm, MakeMyTrip
    GfG Link    : https://practice.geeksforgeeks.org/problems/search-in-a-matrix-1587115621/1
    LeetCode    : https://leetcode.com/problems/search-a-2d-matrix/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(log(R * C)) - Binary search treating the 2D grid as a flattened sorted 1D array
// S.C : O(1)          - Constant auxiliary space
class Solution {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;

        int rows = matrix.size();
        int cols = matrix[0].size();

        int low = 0;
        int high = rows * cols - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            // Map 1D index `mid` to 2D coordinates `(mid / cols, mid % cols)`
            int r = mid / cols;
            int c = mid % cols;

            if (matrix[r][c] == target) {
                return true;
            } else if (matrix[r][c] < target) {
                low = mid + 1; // Target lies in the right half
            } else {
                high = mid - 1; // Target lies in the left half
            }
        }

        return false;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF VIRTUAL 1D TO 2D INDEX MAPPING
 * ============================================================================
 *
 * 2D Matrix (3 rows x 4 cols):
 * Row 0: [ 1,   3,  5,  7 ] -> 1D Indices:  0,  1,  2,  3
 * Row 1: [ 10, 11, 16, 20 ] -> 1D Indices:  4,  5,  6,  7
 * Row 2: [ 23, 30, 34, 60 ] -> 1D Indices:  8,  9, 10, 11
 *
 * Index Formula:
 * - 1D index `idx` -> Row = `idx / cols`, Col = `idx % cols`
 * - Example: idx = 6 -> Row = 6 / 4 = 1, Col = 6 % 4 = 2 -> matrix[1][2] = 16.
 *
 * ============================================================================
 * DRY RUN (Matrix 3x4, target = 3)
 * ============================================================================
 * | Step | low | high | mid | 2D Cell (mid/4, mid%4) | Cell Value | Comparison (Val vs Target) | Action        |
 * | :--- | :-- | :--- | :-- | :--------------------- | :--------- | :------------------------- | :------------ |
 * | 1    | 0   | 11   | 5   | (1, 1)                 | 11         | 11 > 3                     | high = 5 - 1 = 4 |
 * | 2    | 0   | 4    | 2   | (0, 2)                 | 5          | 5 > 3                      | high = 2 - 1 = 1 |
 * | 3    | 0   | 1    | 0   | (0, 0)                 | 1          | 1 < 3                      | low = 0 + 1 = 1  |
 * | 4    | 1   | 1    | 1   | (0, 1)                 | 3          | 3 == 3                     | Found! Return true |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "Reading a Book by Page and Line"
 * If a book has `C` lines per page, the `mid`-th overall line in the book is
 * on page `mid / C` at line number `mid % C`.
 * Since all text is sorted in order, do standard binary search across total lines!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Since each row is sorted and the first integer of each row is greater than
 *   the last integer of the previous row, the entire matrix forms a continuous sorted 1D array.
 * - Total elements = `R * C`. Binary search range: `low = 0`, `high = R * C - 1`.
 * - Convert `mid` to matrix coordinate: `r = mid / C`, `c = mid % C`.
 * - Time Complexity: O(log(R * C)).
 * - Space Complexity: O(1).
 */
