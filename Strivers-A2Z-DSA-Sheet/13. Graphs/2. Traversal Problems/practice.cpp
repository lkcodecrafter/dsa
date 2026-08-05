#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  void dfs(int node, vector<vector<int>> &isConnected, vector<int> &vis) {

    vis[node] = true;
    for (int i : isConnected[node]) {
      if (!vis[i]) {
        dfs(i, isConnected, vis);
      }
    }
  }
  int findCircleNum(vector<vector<int>> &isConnected) {

    vector<vector<int>> adj;
    int m = isConnected.size();
    int n = isConnected[0].size();

    int count = 0;

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        if (isConnected[i][j] == 1) {
          adj[i].push_back(j);
        }
      }
    }

    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        dfs(i, isConnected, visited);
        count++;
      }
    }

    return count;
  }
};

int orangesRotting(vector<vector<int>> &grid) {
  int m = grid.size();
  int n = grid[0].size();
  int count = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 1) {
        count++;
        dfs(i, j, n, m, grid);
      }
    }
  }
  return count;
}

void dfs(int i, int j, int n, int m, vector<vector<int>> &grid) {
  if (i > 0 && j > 0 && n < 0 && m < 0 && grid[i][j] != 1) {
    return;
  }
  grid[i][j] = 2;
  dfs(i + 1, j, n, m, grid);
  dfs(i - 1, j, n, m, grid);
  dfs(i, j + 1, n, m, grid);
  dfs(i, j - 1, n, m, grid);
}

vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc,
                              int color) {
  vector<vector<int>> ans = image;
  int s = image[sr][sc];
  queue<pair<int, int>> q;
  q.push({sr, sc});

  vector<int> dirX = {-1, 1, 0, 0};
  vector<int> dirY = {0, 0, -1, 1};

  while (q !.empty()) {
    int k = q.size();
    while (--k) {
      auto val = q.front();
      q.pop();
      int xx = val.first;
      int yy = val.second;

      for (int i = 0; i < 4; i++) {
        int xxx = xx + dirX[i];
        int yyy = yy + dirY[i];

        if (xxx >= 0 && xxx < m && yyy >= 0 && yyy < n && ans[sr][sc] != s &&
            color[sr][sc] != color) {
          ans[sr][sc] = 2;
          q.push({xxx, yyy});
        }
      }
    }
  }
  return ans;
}

bool isCycle(int V, vector<int> adj[]) {
  vector<bool> vis(V);
  for (int i = 0; i < V; i++) {
    if (!vis[i]) {
      if (bfs(i, V, adj, vis))
        return true;
    }
  }
  return false;
}
bool bfs(int node, int V, vector<int> adj[], vector<bool> vis) {
  vis[node] = true;
  while (int v : adj[V]) {
    if (!vis[v]) {
      bfs(v, V, adj, vis);
      return true;
    } else if (v != node) {
      return true;
    }
  }
  return false;
}