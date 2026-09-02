#include<iostream>
#include<vector>
using namespace std;

/*
 * Problem: Number of Islands (LeetCode 200)
 * Given an m x n 2D binary grid which represents a map of '1's (land) and '0's (water), return the number of islands.
 *
 * Pattern: Graph DFS / Grid Connected Components
 *
 * Complexity:
 * - Time Complexity: O(M * N) where M is the number of rows and N is the number of columns.
 *   Each cell is visited at most constant times during the grid traversal and subsequent DFS calls.
 * - Space Complexity: O(M * N) in the worst case (where the grid is filled with land) for the recursive call stack.
 *
 * Visualizations:
 * Grid flood-fill via DFS recursion (sinking land):
 *
 * Initial Grid:       BFS/DFS Discovery:     After DFS Sinks Island:
 *   [1, 1, 0]           [(1), (1), 0]          [0, 0, 0]
 *   [1, 0, 0]    --->   [(1),  0 , 0]   --->   [0, 0, 0]
 *   [0, 0, 1]           [ 0 ,  0 , 1]          [0, 0, 1] (island count incremented)
 *
 * Memorization Hook:
 * "Traverse the grid. When you hit land '1', increment the island count and start a DFS 
 * to sink all connected land cells by turning them into '0'. Repeat."
 *
 * 1-Minute Quick Revision:
 * 1. Loop through all cells in the grid.
 * 2. If `grid[i][j] == '1'`:
 *    - Increment `count`.
 *    - Trigger `dfs(grid, i, j, m, n)` to flood-fill and sink the island.
 * 3. Inside `dfs(i, j)`:
 *    - If `i` or `j` are out of bounds or `grid[i][j] == '0'`, return.
 *    - Sink current cell: `grid[i][j] = '0'`.
 *    - Recurse in all four cardinal directions (Up, Down, Left, Right).
 * 4. Return `count`.
 *
 * Dry Run:
 * grid = [
 *   ["1", "1", "0"],
 *   ["1", "0", "0"],
 *   ["0", "0", "1"]
 * ]
 *
 * | Row i | Col j | grid[i][j] | Action Taken / DFS Spawned                | Cells Sunk ('1' -> '0') in DFS Run | Island Count Updated |
 * |-------|-------|------------|-------------------------------------------|-------------------------------------|----------------------|
 * | 0     | 0     | '1'        | Increment count, spawn DFS from (0, 0)     | (0,0) -> (1,0) -> (0,1)             | count = 1            |
 * | 0     | 1     | '0' (sunk) | Skip                                      | -                                   | 1                    |
 * | 0     | 2     | '0'        | Skip                                      | -                                   | 1                    |
 * | 1     | 0     | '0' (sunk) | Skip                                      | -                                   | 1                    |
 * | 1     | 1     | '0'        | Skip                                      | -                                   | 1                    |
 * | 1     | 2     | '0'        | Skip                                      | -                                   | 1                    |
 * | 2     | 0     | '0'        | Skip                                      | -                                   | 1                    |
 * | 2     | 1     | '0'        | Skip                                      | -                                   | 1                    |
 * | 2     | 2     | '1'        | Increment count, spawn DFS from (2, 2)     | (2,2)                               | count = 2            |
 */
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // If a cell with land '1' is found, it represents a new island
                if (grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j, m, n); // Sink all connected land elements
                }
            }
        }

        return count;
    }

private:
    void dfs(vector<vector<char>>& grid, int i, int j, int m, int n) {
        // Base case: Boundary checking and water cell ('0') or already visited/sunk cell check
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == '0') {
            return;
        }
        
        // Sink the current cell to prevent infinite recursion and cycles
        grid[i][j] = '0';
        
        // Visit all 4 cardinal adjacent directions
        dfs(grid, i + 1, j, m, n); // Down
        dfs(grid, i - 1, j, m, n); // Up
        dfs(grid, i, j + 1, m, n); // Right
        dfs(grid, i, j - 1, m, n); // Left
    }
};