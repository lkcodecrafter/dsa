#include <vector>
#include <set>
#include <utility>

using namespace std;

/*
QUESTION:
Given a boolean 2D matrix grid of size n * m. You have to find the number of
distinct islands where a group of connected 1s (horizontally or vertically)
forms an island. Two islands are considered to be distinct if and only if one
island is not equal to another (not rotated or reflected).

APPROACH:
- We can model this problem as a graph where each group of connected 1s forms an
  island.
- We can use Depth-First Search (DFS) or Breadth-First Search (BFS) to traverse
  and identify each island.
- To check if two islands are distinct, we cannot simply count their size. Instead,
  we can represent each island by the relative coordinates of its cells with
  respect to its starting cell (the top-left-most cell of that island).
- For an island starting at (r0, c0), if we visit a cell (r, c), its relative
  coordinate is (r - r0, c - c0).
- Since we traverse in a fixed, deterministic order (e.g., Up, Down, Left, Right),
  identical island shapes will produce the exact same sequence of relative
  coordinates.
- We store the list of relative coordinates for each island in a vector, and insert
  it into a set.
- The set will automatically filter out duplicate island shapes, leaving only unique ones.
- Finally, the size of the set gives the number of distinct islands.

COMPLEXITY ANALYSIS:
- Time Complexity: O(n * m * log(n * m)), where n is the number of rows and m is
  the number of columns. We visit each cell at most once. Inserting into the set
  takes logarithmic time with respect to the number of islands.
- Space Complexity: O(n * m) to store the visited grid and the unique island patterns
  in the set.
*/

// DFS function to traverse the island and record relative coordinates
void dfs(int r, int c, vector<vector<int>> &grid, vector<vector<bool>> &vis,
         vector<pair<int, int>> &island, int r0, int c0) {
  vis[r][c] = true;
  
  // Store the coordinate relative to the starting cell (r0, c0)
  island.push_back({r - r0, c - c0});

  int n = grid.size();
  int m = grid[0].size();

  // Direction vectors for moving Up, Down, Left, Right
  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};

  for (int i = 0; i < 4; i++) {
    int nr = r + dr[i];
    int nc = c + dc[i];

    // Check boundary conditions and if the cell is land (1) and not visited
    if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1 && !vis[nr][nc]) {
      dfs(nr, nc, grid, vis, island, r0, c0);
    }
  }
}

int countDistinctIslands(vector<vector<int>> &grid) {
  int n = grid.size();
  if (n == 0) return 0;
  int m = grid[0].size();

  vector<vector<bool>> vis(n, vector<bool>(m, false));
  set<vector<pair<int, int>>> st;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      // If we find an unvisited part of an island, start DFS
      if (grid[i][j] == 1 && !vis[i][j]) {
        vector<pair<int, int>> island;
        // Pass the current (i, j) as the base/starting cell (r0, c0)
        dfs(i, j, grid, vis, island, i, j);
        st.insert(island);
      }
    }
  }

  return st.size();
}
