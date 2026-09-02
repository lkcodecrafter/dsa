/*
    QUESTION    : Spirally traversing a matrix
    Company Tags: Amazon, Microsoft, Payu, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/spirally-traversing-a-matrix-1587115621/1
    LeetCode    : https://leetcode.com/problems/spiral-matrix/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(R * C) - Visits every element in the matrix exactly once
// S.C : O(1)     - Auxiliary space (excluding result vector)
class Solution {
public:
    vector<int> spirallyTraverse(vector<vector<int>> &matrix) {
        vector<int> result;
        if (matrix.empty()) return result;

        int top = 0;
        int bottom = matrix.size() - 1;
        int left = 0;
        int right = matrix[0].size() - 1;

        while (top <= bottom && left <= right) {
            // 1. Move Left to Right along the top boundary
            for (int col = left; col <= right; col++) {
                result.push_back(matrix[top][col]);
            }
            top++; // Shrink top boundary

            // 2. Move Top to Bottom along the right boundary
            for (int row = top; row <= bottom; row++) {
                result.push_back(matrix[row][right]);
            }
            right--; // Shrink right boundary

            // 3. Move Right to Left along the bottom boundary (if rows remain)
            if (top <= bottom) {
                for (int col = right; col >= left; col--) {
                    result.push_back(matrix[bottom][col]);
                }
                bottom--; // Shrink bottom boundary
            }

            // 4. Move Bottom to Top along the left boundary (if cols remain)
            if (left <= right) {
                for (int row = bottom; row >= top; row--) {
                    result.push_back(matrix[row][left]);
                }
                left++; // Shrink left boundary
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF SPIRAL TRAVERSAL
 * ============================================================================
 *
 *    left                         right
 * top  -->  1   2   3   4  -->
 *           5   6   7   8    |
 *           9  10  11  12    v
 * bot <--  13  14  15  16  <--
 *
 * Order of boundaries:
 * 1. Top row (Left -> Right)    : [1, 2, 3, 4]
 * 2. Right col (Top -> Bottom)  : [8, 12, 16]
 * 3. Bottom row (Right -> Left) : [15, 14, 13]
 * 4. Left col (Bottom -> Top)   : [9, 5]
 * Next inner ring: [6, 7], [11], [10]
 * Result: [1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10]
 *
 * ============================================================================
 * DRY RUN (3x3 Matrix)
 * Matrix: {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
 * ============================================================================
 * | Step | Boundaries (top, bot, left, right) | Direction Traversed        | Elements Appended | Result State               |
 * | :--- | :---------------------------------- | :------------------------- | :---------------- | :------------------------- |
 * | 1    | top=0, bot=2, left=0, right=2       | Top Row: (0,0) -> (0,2)    | 1, 2, 3           | {1, 2, 3}                  |
 * | 2    | top=1, bot=2, left=0, right=2       | Right Col: (1,2) -> (2,2)  | 6, 9              | {1, 2, 3, 6, 9}            |
 * | 3    | top=1, bot=2, left=0, right=1       | Bottom Row: (2,1) -> (2,0) | 8, 7              | {1, 2, 3, 6, 9, 8, 7}      |
 * | 4    | top=1, bot=1, left=0, right=1       | Left Col: (1,0) -> (1,0)   | 4                 | {1, 2, 3, 6, 9, 8, 7, 4}   |
 * | 5    | top=1, bot=1, left=1, right=1       | Top Row: (1,1) -> (1,1)    | 5                 | {1, 2, 3, 6, 9, 8, 7, 4, 5}|
 * | End  | top=2, bot=1 (top > bot)            | Loop Terminates            | -                 | Finished!                  |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "Peeling an Onion in Rings"
 * Picture walking along the perimeter of a garden fence:
 * Walk across North fence, South along East fence, West along South fence,
 * and North along West fence. Once a fence is walked, step 1 unit inward
 * (`top++`, `right--`, `bottom--`, `left++`) until you reach the center.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Maintain 4 boundary pointers: `top = 0`, `bottom = R - 1`, `left = 0`, `right = C - 1`.
 * - While `top <= bottom && left <= right`:
 *     1. Traverse `left` to `right` along `top`, then `top++`.
 *     2. Traverse `top` to `bottom` along `right`, then `right--`.
 *     3. Check `top <= bottom`, traverse `right` to `left` along `bottom`, then `bottom--`.
 *     4. Check `left <= right`, traverse `bottom` to `top` along `left`, then `left++`.
 * - Guard clauses (`if (top <= bottom)` and `if (left <= right)`) prevent duplicate traversals on single row/col grids.
 * - Time: O(R * C), Space: O(1).
 */
