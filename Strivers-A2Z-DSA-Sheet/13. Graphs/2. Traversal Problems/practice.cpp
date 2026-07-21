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

int main() { cout << "Hello"; }