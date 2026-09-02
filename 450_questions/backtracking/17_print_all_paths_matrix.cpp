/*
 * QUESTION: Print all possible paths from top left to bottom right of a mXn matrix
 * Link: https://www.geeksforgeeks.org/print-all-possible-paths-from-top-left-to-bottom-right-of-a-mxn-matrix/
 * 
 * Input: 2x3 matrix: {{1, 2, 3}, {4, 5, 6}}
 * Output: { {1, 2, 3, 6}, {1, 2, 5, 6}, {1, 4, 5, 6} }
 */

#include <iostream>
#include <vector>

// Helper backtracking function to traverse and find all paths from (r, c) to (m-1, n-1)
void solveAllPathsMatrix(int r, int c, const std::vector<std::vector<int>>& grid,
                         std::vector<int>& current_path, std::vector<std::vector<int>>& result) {
    int m = grid.size();
    int n = grid[0].size();
    
    // Base Case: Reached the bottom-right corner cell
    if (r == m - 1 && c == n - 1) {
        current_path.push_back(grid[r][c]);
        result.push_back(current_path);
        current_path.pop_back(); // Backtrack
        return;
    }
    
    // Include current cell in path
    current_path.push_back(grid[r][c]);
    
    // Choice 1: Move Down
    if (r + 1 < m) {
        solveAllPathsMatrix(r + 1, c, grid, current_path, result);
    }
    
    // Choice 2: Move Right
    if (c + 1 < n) {
        solveAllPathsMatrix(r, c + 1, grid, current_path, result);
    }
    
    // Backtrack: Remove current cell from path
    current_path.pop_back();
}

// Wrapper function to return all paths
std::vector<std::vector<int>> printAllPaths(const std::vector<std::vector<int>>& grid) {
    std::vector<std::vector<int>> result;
    std::vector<int> current_path;
    
    if (!grid.empty()) {
        solveAllPathsMatrix(0, 0, grid, current_path, result);
    }
    
    return result;
}

/*
 * DRY RUN (on a 2x2 grid):
 * grid = {{1, 2},
 *         {3, 4}}
 * 
 * | Step | Cell (r, c) | Value | Path State   | Action / Next Step                      | result State          |
 * | :--- | :---------- | :---- | :----------- | :-------------------------------------- | :-------------------- |
 * | Init | (0, 0)      | 1     | {1}          | Try Down -> (1, 0)                      | {}                    |
 * | 1    | (1, 0)      | 3     | {1, 3}       | Try Right -> (1, 1) is Destination      | {}                    |
 * | 2    | (1, 1)      | 4     | {1, 3, 4}    | Base Case -> Save path. Pop 4. Return.  | { {1, 3, 4} }         |
 * | 3    | Backtrack   | -     | {1}          | Pop 3. Try Right from (0,0) -> (0, 1)   | { {1, 3, 4} }         |
 * | 4    | (0, 1)      | 2     | {1, 2}       | Try Down -> (1, 1) is Destination       | { {1, 3, 4} }         |
 * | 5    | (1, 1)      | 4     | {1, 2, 4}    | Base Case -> Save path. Pop 4. Return.  | { {1,3,4}, {1,2,4} }  |
 * 
 * Result paths: { {1, 3, 4}, {1, 2, 4} }
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine navigating a street grid where you can only travel South (Down) or East (Right). 
 * Because you never double back North or West, you don't need a map of where you've been (no visited matrix). 
 * You just record your steps as you go. 
 * When you arrive at the target intersection, you snapshot your route, then take a step back and try the other direction.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Call recursive helper `solveAllPathsMatrix(r, c, grid, current_path, result)`.
 * - Base Case: If `r == m - 1 && c == n - 1`, push `grid[r][c]` to `current_path`, add to `result`, pop, and return.
 * - Push current cell value: `current_path.push_back(grid[r][c])`.
 * - If `r + 1 < m`, recurse `(r + 1, c)`.
 * - If `c + 1 < n`, recurse `(r, c + 1)`.
 * - Pop current cell value from `current_path`.
 * - Time Complexity: O(2^(M + N))
 * - Space Complexity: O(M + N) recursion stack.
 */
