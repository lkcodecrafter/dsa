/*
QUESTION:
Given an n x n binary matrix grid, return the length of the shortest clear path
in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0))
to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
1. All the visited cells of the path are 0.
2. All the adjacent cells of the path are 8-directionally connected (i.e., they
are different and they share an edge or a corner).
3. The length of a clear path is the number of visited cells of this path.

Example:
Input: grid = [[0,1],[1,0]]
Output: 2

APPROACH:
- BFS is ideal for finding the shortest path in an unweighted grid.
- To simplify and optimize, we avoid a separate visited array and level-by-level
queue loops.
- Instead, we use a single 2D distance matrix `dist` initialized to infinity
(1e9).
- `dist[x][y]` stores the shortest distance to cell (x, y). If `dist[x][y] <
1e9`, it also indicates the cell has been visited.
- We relax edges using the check: `dist[x][y] + 1 < dist[nx][ny]`.

VISUALIZATION:
Consider a 3x3 binary grid:
  (0,0) [0] ─── (0,1) [1] ─── (0,2) [0]
    │  ╲         │  ╲         │  ╱
    │    ╲       │    ╲       │ /
  (1,0) [1] ─── (1,1) [0] ─── (1,2) [0]
    │  ╱         │  ╱         │  ╲
    │    ╱       │    ╱       │    ╲
  (2,0) [0] ─── (2,1) [0] ─── (2,2) [0]

Here, values in [ ] denote grid[i][j]:
- 0: Open / Clear Cell
- 1: Blocked Cell

Valid 8-directional paths are diagonals and adjacent cells.
Shortest path from (0,0) to (2,2):
(0,0) -> (1,1) -> (2,2)
Path length (number of cells) = 3.

DRY RUN:
Input Grid:
[
  [0, 1, 0],
  [1, 0, 0],
  [0, 0, 0]
]
Start cell: (0,0), Target cell: (2,2)

1. Initialization:
   - dist array initialized to 1e9 (infinity) for all cells.
   - Set dist[0][0] = 1.
   - q = {(0, 0)}

2. BFS Loop:
   - Pop (0, 0) from q. dist[0][0] = 1.
     - Neighbors of (0,0):
       - (0,1): grid is 1 (blocked). Skip.
       - (1,0): grid is 1 (blocked). Skip.
       - (1,1): grid is 0. dist[0][0] + 1 < dist[1][1] => 1 + 1 < 1e9.
                Update dist[1][1] = 2. Push (1, 1) to q.
       - Other neighbors out of bounds.

   - q = {(1, 1)}
   - Pop (1, 1) from q. dist[1][1] = 2.
     - Neighbors of (1,1):
       - (0,0): dist[1][1] + 1 < dist[0][0] => 2 + 1 < 1 is false. Skip.
       - (0,1): grid is 1. Skip.
       - (0,2): grid is 0. dist[1][1] + 1 < dist[0][2] => 2 + 1 < 1e9.
                Update dist[0][2] = 3. Push (0, 2) to q.
       - (1,0): grid is 1. Skip.
       - (1,2): grid is 0. dist[1][1] + 1 < dist[1][2] => 2 + 1 < 1e9.
                Update dist[1][2] = 3. Push (1, 2) to q.
       - (2,0): grid is 0. dist[1][1] + 1 < dist[2][0] => 2 + 1 < 1e9.
                Update dist[2][0] = 3. Push (2, 0) to q.
       - (2,1): grid is 0. dist[1][1] + 1 < dist[2][1] => 2 + 1 < 1e9.
                Update dist[2][1] = 3. Push (2, 1) to q.
       - (2,2): grid is 0. dist[1][1] + 1 < dist[2][2] => 2 + 1 < 1e9.
                Update dist[2][2] = 3. Push (2, 2) to q.

   - q = {(0, 2), (1, 2), (2, 0), (2, 1), (2, 2)}
   - Pop (0, 2) from q. Not destination.
   - Pop (1, 2) from q. Not destination.
   - Pop (2, 0) from q. Not destination.
   - Pop (2, 1) from q. Not destination.
   - Pop (2, 2) from q. Target reached! Return dist[2][2] = 3.

Output: 3

MEMORIZATION / RECALL SCENARIO:
- "The King's Diagonal Escape" Analogy:
  - Imagine a chess King placed at the top-left (0,0) of a grid.
  - The King must escape to the bottom-right (n-1, n-1).
  - Since the King can move 1 step in any of the 8 directions, we use BFS
(Breadth-First Search) to simulate the King's steps.
  - Obstacles (1s) block the King. Open cells (0s) are safe paths.
  - To find the shortest path, the King marks each safe cell with the minimum
steps taken to reach it.
  - If a cell already has a smaller step count, the King ignores it.

COMPLEXITY ANALYSIS:
- Time Complexity: O(N^2) where N is the grid dimension. Each cell is processed
at most once, and its 8 neighbors are checked in O(1) time.
- Space Complexity: O(N^2) for the 2D distance grid and the BFS queue.

1-MINUTE QUICK REVISION:
- Core Concept: BFS on unweighted grid with 8-directional moves.
- Key Rule: Do not use separate visited array or level-by-level q.size() loops.
Use distance comparison `dist[x][y] + 1 < dist[nx][ny]` to track visited state
and path length.
- Template Flow:
  1. Base Case: If grid[0][0] != 0 or grid[n-1][n-1] != 0, return -1.
  2. Init `dist[N][N]` to `1e9`. Set `dist[0][0] = 1`.
  3. Push `{0, 0}` to BFS queue `q`.
  4. While `q` is not empty:
     - Pop `{x, y}`.
     - If `{x, y}` is target `{n-1, n-1}`, return `dist[x][y]`.
     - For all 8-directional neighbors `{nx, ny}`:
       - If valid, open cell, and `dist[x][y] + 1 < dist[nx][ny]`:
         - Update `dist[nx][ny] = dist[x][y] + 1` and push `{nx, ny}` to `q`.
  5. Return -1.

⏱️ 1-Minute Quick Review:
- Goal: Shortest 8-directional path in binary grid from top-left (0,0) to
bottom-right (n-1, n-1).
- Queue-based BFS: Processes cells level-by-level outwards to guarantee shortest
paths.
- Distance array relaxation check:
  - If dist[x][y] = 2, and neighbor is open: 2 + 1 < 1e9 (or existing dist) ->
update to 3 and push to queue.
- Complexity: O(N^2) Time & O(N^2) Space.
*/

#include <queue>
#include <vector>
using namespace std;

int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
  int n = grid.size();

  // Base Case: Path is impossible if start or end is blocked.
  if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0) {
    return -1;
  }

  // Distance array initialized to 1e9 (infinity).
  // Serves as both shortest distance tracker and visited matrix.
  vector<vector<int>> dist(n, vector<int>(n, 1e9));
  queue<pair<int, int>> q;

  // Start with path length of 1 at source (0,0)
  dist[0][0] = 1;
  q.push({0, 0});

  // 8-directional arrays for neighboring moves (horizontal, vertical, diagonal)
  int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    // If target cell (n-1, n-1) is reached, return its distance
    if (x == n - 1 && y == n - 1) {
      return dist[x][y];
    }

    // Explore all 8 adjacent cells
    for (int i = 0; i < 8; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      // Check boundary limits and verify if the cell is traversable (0)
      if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
        // BFS Relaxation check:
        // Example (Update): If dist[x][y] = 2, dist[nx][ny] = 1e9 -> 2 + 1 <
        // 1e9 updates dist[nx][ny] to 3. Example (No Update): If dist[x][y] =
        // 3, dist[nx][ny] = 2 -> 3 + 1 < 2 is false.
        if (dist[x][y] + 1 < dist[nx][ny]) {
          dist[nx][ny] = dist[x][y] + 1;
          q.push({nx, ny});
        }
      }
    }
  }

  // No path found
  return -1;
}
