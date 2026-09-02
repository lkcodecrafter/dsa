/*
 * QUESTION: Sudoku Solver
 * Link: https://practice.geeksforgeeks.org/problems/solve-the-sudoku/0
 * 
 * Input: 9x9 board with some cells filled (1-9) and others 0.
 * Output: Solved 9x9 board.
 */

#include <iostream>
#include <vector>

// Checks if it is safe to assign digit to grid[row][col]
bool isSudokuSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check Row and Column safety
    for (int x = 0; x < 9; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }
    
    // Check 3x3 Subgrid safety
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + start_row][j + start_col] == num) {
                // Number already exists in subgrid
                return false;
            }
        }
    }
    
    return true;
}

// Helper backtracking function to solve the Sudoku grid
bool solveSudokuHelper(std::vector<std::vector<int>>& grid) {
    int row = -1;
    int col = -1;
    bool is_empty = false;
    
    // Step 1: Find the first unassigned (value 0) cell
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                is_empty = true;
                break;
            }
        }
        if (is_empty) break;
    }
    
    // Base Case: No empty cells left, Sudoku is solved!
    if (!is_empty) {
        return true;
    }
    
    // Step 2: Try placing numbers 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (isSudokuSafe(grid, row, col, num)) {
            grid[row][col] = num; // Assign number
            
            if (solveSudokuHelper(grid)) {
                return true; // Propagation of success
            }
            
            grid[row][col] = 0; // Backtrack: undo assignment
        }
    }
    
    return false; // Triggers backtracking of previous cells
}

// Wrapper function to solve Sudoku
bool SolveSudoku(std::vector<std::vector<int>>& grid) {
    return solveSudokuHelper(grid);
}

// Prints the solved Sudoku grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }
}

/*
 * DRY RUN (Partial dry run on empty cell (0, 2) in grid):
 * Grid starts with empty cell at (0, 2).
 * 
 * | Cell | Tried num | Row Check | Col Check | Grid Check | Safe? | Action                                    |
 * | :--- | :-------- | :-------- | :-------- | :--------- | :---- | :---------------------------------------- |
 * | (0,2)| 1         | Fails     | -         | -          | No    | Try next                                  |
 * | (0,2)| 2         | Passes    | Fails     | -          | No    | Try next                                  |
 * | (0,2)| 3         | Passes    | Passes    | Passes     | Yes   | Assign grid[0][2]=3; call solve recursive |
 * | Next | (0,3) empty| -        | -         | -          | -     | If child calls fail, backtrack grid[0][2]=0|
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine filling out a spreadsheet grid. 
 * You find the first empty slot. 
 * You pencil in a number (1-9) that doesn't conflict with its row, column, or local box. 
 * If you get stuck later down the line, you erase your pencil mark (backtrack) and try a different number.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Locate the first empty cell `grid[i][j] == 0`. If none, return `true`.
 * - Loop `num` from `1` to `9`:
 *   - Check constraints using `isSudokuSafe` (row, column, and `3x3` box).
 *   - If safe: set `grid[i][j] = num`, recurse.
 *   - If recursion returns `true`, propagate `true`.
 *   - Otherwise: backtrack `grid[i][j] = 0`.
 * - Return `false` if no number fits.
 * - Time Complexity: O(9^(N)) where N is the number of empty cells (O(9^81) worst case, but heavily pruned).
 * - Space Complexity: O(81) recursion depth.
 */
