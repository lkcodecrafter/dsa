#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
 * Problem: Rotting Oranges (LeetCode 994)
 * Determine the minimum number of minutes that must elapse until no cell has a fresh orange.
 * If this is impossible, return -1.
 *
 * Pattern: Multi-source BFS / Grid / Queue
 *
 * Complexity:
 * - Time Complexity: O(M * N) where M is the number of rows and N is columns in the grid.
 *   We scan the grid to initialize the queue and visit each cell at most once.
 * - Space Complexity: O(M * N) for the BFS queue containing rotten orange nodes.
 *
 * BFS Simplification:
 * - We avoid nested level-by-level loops (such as while(size--)) by storing the current time
 *   directly alongside the orange coordinates in the queue using a simple struct.
 * - This provides a clean, single-loop traversal.
 *
 * Visualizations:
 * Orange grid states over time:
 * (2 = rotten, 1 = fresh, 0 = empty)
 *
 * Minute 0:            Minute 1:            Minute 2:
 *   [2, 1, 0]            [2, 2, 0]            [2, 2, 0]
 *   [1, 1, 0]    --->    [2, 1, 0]    --->    [2, 2, 0]
 *   [0, 1, 1]            [0, 1, 1]            [0, 2, 2]
 *
 * Memorization Hook:
 * "Push all rotten oranges onto a queue with time = 0 and count fresh oranges.
 * Pop each rotten orange, update max_time, rot its fresh neighbors, decrement fresh count,
 * and push them with time + 1. If fresh count is 0, return max_time, else -1."
 *
 * 1-Minute Quick Revision:
 * 1. Define a struct `Orange { int r, c, t; }` to hold coordinates and current time.
 * 2. Count all fresh oranges and push all initial rotten oranges into a `queue<Orange> q` with time 0.
 * 3. Loop while `q` is not empty:
 *    - Pop the front orange `curr`.
 *    - Update `max_time = max(max_time, curr.t)`.
 *    - Visit 4 neighbors: if bounds match and cell is 1 (fresh), set grid to 2 (rotten), decrement `fresh`, and push `{nr, nc, curr.t + 1}`.
 * 4. After BFS, return `fresh == 0 ? max_time : -1`.
 *
 * Dry Run:
 * grid = [
 *   [2, 1, 1],
 *   [1, 1, 0],
 *   [0, 1, 1]
 * ]
 * Initial state: fresh = 6, rotten oranges pushed to queue: [{0, 0, 0}]
 *
 * | Pop Orange | Neighbors (r, c) | Fresh -> Rotten | fresh count update | Queue Pushes                 | max_time update |
 * |------------|------------------|-----------------|--------------------|------------------------------|-----------------|
 * | {0, 0, 0}  | (1,0), (0,1)     | Yes             | 6 - 2 = 4          | {1,0,1}, {0,1,1}             | max(0, 0) = 0   |
 * | {1, 0, 1}  | (1,1)            | Yes             | 4 - 1 = 3          | {1,1,2}                      | max(0, 1) = 1   |
 * | {0, 1, 1}  | (0,2)            | Yes             | 3 - 1 = 2          | {0,2,2}                      | max(1, 1) = 1   |
 * | {1, 1, 2}  | -                | -               | 2                  | -                            | max(1, 2) = 2   |
 * | {0, 2, 2}  | (1,2) [water]    | -               | 2                  | -                            | max(2, 2) = 2   |
 * | -          | -                | -               | -                  | Queue empty, fresh = 2 (> 0) | Returns -1      |
 */
class Solution {
private:
    struct Orange {
        int r;
        int c;
        int t; // Minutes elapsed when this orange rotted
    };

public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<Orange> q;
        int fresh = 0;
        
        // Scan the grid to count fresh oranges and queue initial rotten oranges
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fresh++;
                } else if (grid[i][j] == 2) {
                    q.push({i, j, 0});
                }
            }
        }
        
        // 4 directions of movement (Down, Up, Right, Left)
        vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int max_time = 0;
        
        // Single flat loop structure without nested level loops
        while (!q.empty()) {
            Orange curr = q.front();
            q.pop();
            
            // Record maximum time taken
            max_time = max(max_time, curr.t);
            
            for (auto d : dir) {
                int ni = curr.r + d.first;
                int nj = curr.c + d.second;
                
                // If the neighbor is within boundaries and contains a fresh orange
                if (ni >= 0 && nj >= 0 && ni < m && nj < n && grid[ni][nj] == 1) {
                    grid[ni][nj] = 2; // Rot the fresh orange
                    fresh--;
                    q.push({ni, nj, curr.t + 1}); // Queue it with incremented time
                }
            }
        }
        
        // If there are still fresh oranges left, it's impossible to rot all of them
        return fresh == 0 ? max_time : -1;
    }
};
