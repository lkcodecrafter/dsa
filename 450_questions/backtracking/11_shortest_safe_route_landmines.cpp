/*
 * QUESTION: Find shortest safe route in a path with landmines
 * Link: https://www.geeksforgeeks.org/find-shortest-safe-route-in-a-path-with-landmines/
 * 
 * Input: R x C grid where 1 = safe, 0 = landmine. Cells adjacent to landmines are also unsafe.
 * Output: Shortest path length from any cell in column 0 to any cell in column C-1.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

// Checks if coordinates (r, c) are within grid boundaries
bool isValid(int r, int c, int R, int C) {
    return (r >= 0 && r < R && c >= 0 && c < C);
}

// Finds the shortest safe route using BFS with simplified distance/visited tracking
int findShortestSafePath(const std::vector<std::vector<int>>& grid) {
    if (grid.empty()) return -1;
    
    int R = grid.size();
    int C = grid[0].size();
    
    // Step 1: Mark all landmines and their adjacent cells as unsafe
    std::vector<std::vector<bool>> is_safe(R, std::vector<bool>(C, true));
    
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == 0) {
                is_safe[r][c] = false; // Landmine itself is unsafe
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (isValid(nr, nc, R, C)) {
                        is_safe[nr][nc] = false; // Neighbor of landmine is unsafe
                    }
                }
            }
        }
    }
    
    // Queue stores coordinates: pair<row, col>
    std::queue<std::pair<int, int>> q;
    
    // SIMPLIFIED visited/distance tracking:
    // dist[r][c] = -1 means unvisited.
    // Positive values represent the distance from column 0.
    std::vector<std::vector<int>> dist(R, std::vector<int>(C, -1));
    
    // Step 2: Initialize queue with all safe cells in the first column (c = 0)
    for (int r = 0; r < R; r++) {
        if (is_safe[r][0]) {
            q.push({r, 0});
            dist[r][0] = 0; // Distance to start is 0
        }
    }
    
    // Step 3: Run BFS
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        // Since it's BFS, the first time we pop a cell in the last column,
        // it is guaranteed to have the minimum path length.
        if (c == C - 1) {
            return dist[r][c];
        }
        
        // Explore all 4 adjacent directions
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            // If the adjacent cell is valid, safe, and unvisited (dist == -1)
            if (isValid(nr, nc, R, C) && is_safe[nr][nc] && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1; // Update distance directly
                q.push({nr, nc});
            }
        }
    }
    
    return -1; // Unreachable
}

/*
 * DRY RUN (on a 3x3 grid):
 * grid = {{1, 1, 1},
 *         {1, 0, 1},
 *         {1, 1, 1}}
 * 
 * Step 1: Mark safety (landmine at 1,1 makes neighbors unsafe):
 * is_safe = {{F, F, F},
 *            {F, F, F},
 *            {F, F, F}}
 * All cells unsafe (since landmine at (1,1) blocks adjacent cells (0,1), (2,1), (1,0), (1,2)).
 * Queue will not be filled. Returns -1.
 * 
 * Let's dry run on grid = {{1, 1, 1},
 *                          {1, 1, 1},
 *                          {1, 0, 1}} (mine at 2,1 blocks 2,0, 1,1, 2,2):
 * is_safe = {{T, T, T},
 *            {T, F, T},
 *            {F, F, F}}
 * 
 * | Step | Queue State | Pop Cell | dist[Pop] | Checked Neighbors | Valid & Safe & Unvisited? | Queue Push | dist Update |
 * | :--- | :---------- | :------- | :-------- | :---------------- | :------------------------ | :--------- | :---------- |
 * | Init | {(0,0)}     | -        | -         | -                 | -                         | -          | dist[0][0]=0|
 * | 1    | {}          | (0,0)    | 0         | (1,0)             | Yes (dist[1][0] == -1)    | {(1,0)}    | dist[1][0]=1|
 * |      |             |          |           | (0,1)             | Yes (dist[0][1] == -1)    | {(1,0),(0,1)}| dist[0][1]=1|
 * | 2    | {(0,1)}     | (1,0)    | 1         | -                 | No new safe unvisited     | {(0,1)}    |             |
 * | 3    | {}          | (0,1)    | 1         | (0,2)             | Yes (dist[0][2] == -1)    | {(0,2)}    | dist[0][2]=2|
 * | 4    | {}          | (0,2)    | 2         | -                 | -                         | -          | -           |
 * 
 * Pop (0,2) has c == 2 (C-1) -> returns dist[0][2] = 2.
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine navigating a minefield. 
 * First, paint red marks around all landmines. 
 * Start a group of walkers in the first column. 
 * They step step-by-step into clean spaces (dist matrix), 
 * writing their step count on the floor. 
 * The moment a walker steps onto the last column, they shout out their step count.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Mark all landmines and their adjacent cells as `is_safe = false`.
 * - Use a `dist` array initialized to `-1` to store shortest distance (acts as visited matrix).
 * - Push all safe cells of first column `(r, 0)` into the queue and set `dist[r][0] = 0`.
 * - Run BFS:
 *   - Pop `(r, c)`. If `c == C - 1`, return `dist[r][c]`.
 *   - For valid neighbors: if `is_safe` and `dist[nr][nc] == -1`, set `dist[nr][nc] = dist[r][c] + 1` and push to queue.
 * - Return `-1` if queue becomes empty without reaching column `C-1`.
 * - Time Complexity: O(R * C)
 * - Space Complexity: O(R * C)
 */
