/*
    QUESTION    : N-Queen Problem (Printing all solutions)
    Company Tags: Amazon, Microsoft, Adobe, Directi
    GfG Link    : https://www.geeksforgeeks.org/problems/n-queen-problem0315/1
    LeetCode    : https://leetcode.com/problems/n-queens/
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N!)       - Searching through permutations with aggressive pruning
// S.C : O(N)        - Recursion stack + boolean hashing vectors for O(1) safety checks
class Solution {
private:
    // Helper DFS Backtracking Function to place queens row by row
    void solve(int row, int n, vector<int> &current_sol,
               vector<bool> &cols, vector<bool> &diag1, vector<bool> &diag2,
               vector<vector<int>> &result) {
        
        // Base Case: Successfully placed queens in all rows (0 to n-1)
        if (row == n) {
            result.push_back(current_sol);
            return;
        }

        // Try placing a queen in every column of the current row
        for (int col = 0; col < n; col++) {
            // Diagonal index formulas:
            // Main diagonal (\ slope): (row - col + n - 1) ranges from 0 to 2*n - 2
            // Anti diagonal (/ slope): (row + col) ranges from 0 to 2*n - 2
            int d1 = row - col + (n - 1);
            int d2 = row + col;

            // O(1) Safety Check: ensure no queen exists in the same column or diagonals
            if (!cols[col] && !diag1[d1] && !diag2[d2]) {
                // 1. Choose: Place queen at (row, col)
                cols[col] = true;
                diag1[d1] = true;
                diag2[d2] = true;
                current_sol.push_back(col + 1); // 1-indexed column for GfG standard

                // 2. Explore: Move to the next row
                solve(row + 1, n, current_sol, cols, diag1, diag2, result);

                // 3. Backtrack / Unchoose: Remove queen and release guards
                current_sol.pop_back();
                diag2[d2] = false;
                diag1[d1] = false;
                cols[col] = false;
            }
        }
    }

public:
    vector<vector<int>> nQueen(int n) {
        vector<vector<int>> result;
        vector<int> current_sol;

        // Boolean arrays to track occupied columns and diagonals in O(1) time
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false); // Main diagonals (row - col + n - 1)
        vector<bool> diag2(2 * n - 1, false); // Anti-diagonals (row + col)

        solve(0, n, current_sol, cols, diag1, diag2, result);
        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 4-QUEENS SOLUTION [2, 4, 1, 3]
 * ============================================================================
 *
 *   Col:    1     2     3     4   (1-indexed for GFG)
 * Row 0: [ . ] [ Q ] [ . ] [ . ]  -> Queen at Col 2
 * Row 1: [ . ] [ . ] [ . ] [ Q ]  -> Queen at Col 4
 * Row 2: [ Q ] [ . ] [ . ] [ . ]  -> Queen at Col 1
 * Row 3: [ . ] [ . ] [ Q ] [ . ]  -> Queen at Col 3
 *
 * Diagonal Math:
 * 1. Main Diagonal (\):  Row - Col = Constant
 *    Offset by +(N-1) to make index positive: index = row - col + (n - 1).
 * 2. Anti-Diagonal (/):  Row + Col = Constant
 *    index = row + col.
 *
 * ============================================================================
 * LINE-BY-LINE EXECUTION TRACE (N = 4, First Valid Placement)
 * ============================================================================
 * Row 0: Try Col 0 -> Safe -> Place Q at Col 0 (path: [1]) -> Recurse Row 1
 *   Row 1: Col 0 (Col blocked), Col 1 (Diag2 blocked), Col 2 -> Safe -> Place Q at Col 2 (path: [1, 3]) -> Recurse Row 2
 *     Row 2: Col 0..3 all blocked! -> Backtrack Row 2 -> Pop 3 from path.
 *   Row 1: Col 3 -> Safe -> Place Q at Col 3 (path: [1, 4]) -> Recurse Row 2
 *     Row 2: Col 0 (Diag blocked), Col 1 -> Safe -> Place Q at Col 1 (path: [1, 4, 2]) -> Recurse Row 3
 *       Row 3: Col 0..3 all blocked! -> Backtrack -> Pop 2 from path -> Pop 4 from path.
 * Row 0: Try Col 1 -> Safe -> Place Q at Col 1 (path: [2]) -> Recurse Row 1
 *   Row 1: Col 3 -> Safe -> Place Q at Col 3 (path: [2, 4]) -> Recurse Row 2
 *     Row 2: Col 0 -> Safe -> Place Q at Col 0 (path: [2, 4, 1]) -> Recurse Row 3
 *       Row 3: Col 2 -> Safe -> Place Q at Col 2 (path: [2, 4, 1, 3]) -> Recurse Row 4
 *         Row 4 == 4 (Base Case) -> MATCH FOUND: [2, 4, 1, 3]!
 *
 * ============================================================================
 * DRY RUN TABLE (N = 4)
 * ============================================================================
 * | Step | Row | Tried Col | cols[c] | diag1 (r-c+3) | diag2 (r+c) | Safety Check | Action / Recursion Branch     | Current Path |
 * | :--- | :-- | :-------- | :------ | :------------ | :---------- | :----------- | :---------------------------- | :----------- |
 * | 1    | 0   | 0         | Free    | Free (3)      | Free (0)    | Safe         | Place Q at (0,0); recurse r=1 | {1}          |
 * | 2    | 1   | 0         | Occ     | -             | -           | Blocked      | Skip col 0                    | {1}          |
 * | 3    | 1   | 1         | Free    | Free (3)      | Occ (2)     | Blocked      | Skip col 1                    | {1}          |
 * | 4    | 1   | 2         | Free    | Free (2)      | Free (3)    | Safe         | Place Q at (1,2); recurse r=2 | {1, 3}       |
 * | 5    | 2   | 0,1,2,3   | -       | -             | -           | All Blocked  | Backtrack -> undo (1,2)       | {1}          |
 * | 6    | 1   | 3         | Free    | Free (1)      | Free (4)    | Safe         | Place Q at (1,3); recurse r=2 | {1, 4}       |
 * | 7    | 2   | 1         | Free    | Free (4)      | Free (3)    | Safe         | Place Q at (2,1); recurse r=3 | {1, 4, 2}    |
 * | 8    | 3   | 0,1,2,3   | -       | -             | -           | All Blocked  | Backtrack all the way to r=0  | {}           |
 * | 9    | 0   | 1         | Free    | Free (2)      | Free (1)    | Safe         | Place Q at (0,1); recurse r=1 | {2}          |
 * | 10   | 1   | 3         | Free    | Free (1)      | Free (4)    | Safe         | Place Q at (1,3); recurse r=2 | {2, 4}       |
 * | 11   | 2   | 0         | Free    | Free (5)      | Free (2)    | Safe         | Place Q at (2,0); recurse r=3 | {2, 4, 1}    |
 * | 12   | 3   | 2         | Free    | Free (4)      | Free (5)    | Safe         | Place Q at (3,2); recurse r=4 | {2, 4, 1, 3} |
 * | 13   | 4   | -         | -       | -             | -           | Target Reach | Base Case: Add [2, 4, 1, 3]!  | {2, 4, 1, 3} |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Laser Shield Sentinels"
 * Place a queen on a chessboard tile. She projects 3 laser shields:
 * 1. Straight down the column (`cols[col]`).
 * 2. Down-right diagonal (`diag1[row - col + n - 1]`).
 * 3. Down-left diagonal (`diag2[row + col]`).
 * To place a queen in the next row, find a tile with no active laser shields.
 * If all tiles are covered in lasers, retreat (backtrack) and reposition the
 * queen in the previous row.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Core Concept: Row-by-row backtracking with O(1) safety lookup.
 * - Why Row-by-Row? Guaranteeing one queen per row simplifies search to N choices per row.
 * - O(1) Safety Arrays:
 *     - `cols[col]` for column collisions.
 *     - `diag1[row - col + n - 1]` for main diagonals (\).
 *     - `diag2[row + col]` for anti-diagonals (/).
 * - Backtrack Pattern: Mark arrays `true` -> recurse on `row + 1` -> unmark arrays `false`.
 * - Base Case: When `row == n`, push the current combination to results.
 * - Time Complexity: O(N!) — search space pruned aggressively.
 * - Space Complexity: O(N) recursion stack and boolean tracking vectors.
 */
