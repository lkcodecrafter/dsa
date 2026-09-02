/*
 * QUESTION: Longest Possible Route in a Matrix with Hurdles
 * Link: https://www.geeksforgeeks.org/longest-possible-route-in-a-matrix-with-hurdles/
 * 
 * Input: Matrix with 1s (safe) and 0s (hurdles), start (xs, ys), destination (xd, yd)
 * Output: Longest path length.
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Helper check function
bool isMatrixCellValid(int r, int c, int R, int C, const std::vector<std::vector<int>>& grid) {
    return (r >= 0 && r < R && c >= 0 && c < C && grid[r][c] == 1);
}

// Backtracking helper to explore all simple paths to find the longest one
void findLongestRoute(int r, int c, int xd, int yd, std::vector<std::vector<int>>& grid,
                      int current_len, int& max_len) {
    int R = grid.size();
    int C = grid[0].size();
    
    // Base Case: Reached the destination
    if (r == xd && c == yd) {
        max_len = std::max(max_len, current_len);
        return;
    }
    
    // In-place Visited Marking: Block the current cell by setting it to 0
    grid[r][c] = 0;
    
    // Define moves (Down, Up, Right, Left)
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        if (isMatrixCellValid(nr, nc, R, C, grid)) {
            findLongestRoute(nr, nc, xd, yd, grid, current_len + 1, max_len);
        }
    }
    
    // Backtrack: Restore the cell to 1
    grid[r][c] = 1;
}

// Wrapper function to find the longest path
int longestRoute(std::vector<std::vector<int>>& grid, int xs, int ys, int xd, int yd) {
    // If start or destination is blocked, no path can exist
    if (grid.empty() || grid[xs][ys] == 0 || grid[xd][yd] == 0) {
        return -1;
    }
    
    int max_len = -1;
    findLongestRoute(xs, ys, xd, yd, grid, 0, max_len);
    return max_len;
}

/*
 * DRY RUN (on a 2x3 grid, start = (0,0), dest = (1,2)):
 * grid = {{1, 1, 1},
 *         {1, 0, 1}}
 * 
 * | Step | Cell (r, c) | current_len | Grid State Modification | Action / Next Recursion Cell            | max_len Updated |
 * | :--- | :---------- | :---------- | :---------------------- | :-------------------------------------- | :-------------- |
 * | Init | (0, 0)      | 0           | grid[0][0] = 0          | Right -> (0,1) is valid. Recurse.       | -1              |
 * | 1    | (0, 1)      | 1           | grid[0][1] = 0          | Right -> (0,2) is valid. Recurse.       | -1              |
 * | 2    | (0, 2)      | 2           | grid[0][2] = 0          | Down -> (1,2) is valid. Recurse.        | -1              |
 * | 3    | (1, 2)      | 3           | Reached Dest            | Base Case: update max_len = max(-1, 3)  | 3               |
 * | 4    | Backtrack   | -           | grid[0][2] = 1          | Level 2: Try Down (1,1) is blocked.      | 3               |
 * | 5    | Backtrack   | -           | grid[0][1] = 1          | Level 1: Try Down (1,1) is blocked.      | 3               |
 * | 6    | (0, 0)      | 0           | grid[0][0] = 0          | Down -> (1,0) is valid. Recurse.        | 3               |
 * | 7    | (1, 0)      | 1           | grid[1][0] = 0          | (No neighbor is valid. grid[1][1] is 0) | 3               |
 * 
 * Final Longest Route Length: 3
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine wandering in a labyrinth trying to draw the longest sight-seeing path. 
 * You lock doors behind you as you walk (`grid[r][c] = 0`) to prevent walking in circles. 
 * Once you reach the exit, you note down your step count. 
 * As you walk backward to try other corridors, you unlock the doors (`grid[r][c] = 1`).
 * 
 * 1-MINUTE QUICK REVISION:
 * - Start recursion from start cell `(xs, ys)`.
 * - If `r == xd && c == yd`, update `max_len = max(max_len, current_len)` and return.
 * - Mark current cell as visited in-place: `grid[r][c] = 0`.
 * - For each of the 4 neighbors: if `grid[nr][nc] == 1`, recurse with `current_len + 1`.
 * - Backtrack: set `grid[r][c] = 1`.
 * - Time Complexity: O(4^(R * C))
 * - Space Complexity: O(R * C) recursion stack depth.
 */
