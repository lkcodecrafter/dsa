#include <queue>
#include <vector>

using namespace std;

/*
QUESTION:
There is an undirected graph with n nodes, where each node is numbered between 0
and n - 1. You are given a 2D array graph, where graph[u] is an array of nodes
that node u is adjacent to. More formally, for each v in graph[u], there is an
undirected edge between node u and node v. The graph has the following
properties:
1. There are no self-edges (graph[u] does not contain u).
2. There are no parallel edges (graph[u] does not contain duplicate values).
3. If v is in graph[u], then u is in graph[v] (the graph is undirected).
The graph may not be connected, meaning there may be two nodes u and v such that
there is no path between them.

A graph is bipartite if the nodes can be partitioned into two independent sets A
and B such that every edge in the graph connects a node in set A and a node in
set B.

APPROACH:
- We can use Depth-First Search (DFS) or Breadth-First Search (BFS) to color the
  nodes in the graph using two colors (1 and -1).
- We start by coloring an uncolored node with color 1.
- During the DFS traversal, we visit each neighbor of the current node:
  1. If the neighbor is uncolored (color is 0), we recursively call DFS on it
with the opposite color (-color). If any recursive call returns false, we return
false.
  2. If the neighbor is already colored and has the same color as the current
node, then the graph cannot be bipartite (an edge exists between two nodes of
the same set), so we return false.
- If we successfully color the entire graph without any conflicts, we return
true.

COMPLEXITY ANALYSIS:
- Time Complexity: O(V + E), where V is the number of vertices and E is the
number of edges. We visit each vertex and edge once.
- Space Complexity: O(V), where V is the number of vertices. This is for the
color array and the recursive call stack space.
*/

// DFS helper function to color nodes recursively
bool dfs(int node, int color, vector<vector<int>> &adj, vector<int> &col) {
  col[node] = color;

  for (auto neighbor : adj[node]) {
    // If the neighbor is not colored yet, color it with the opposite color
    if (col[neighbor] == 0) {
      if (!dfs(neighbor, -color, adj, col)) {
        return false;
      }
    }
    // If the neighbor is already colored and has the same color, it's not
    // bipartite
    else if (col[neighbor] == col[node]) {
      return false;
    }
  }

  return true;
}

// BFS helper function to color nodes iteratively
bool bfs(int start, vector<vector<int>> &adj, vector<int> &col) {
  queue<int> q;
  q.push(start);
  col[start] = 1; // Start coloring the source node with color 1

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (auto neighbor : adj[node]) {
      // If the neighbor is not colored yet, color it with the opposite color
      // and push to queue
      if (col[neighbor] == 0) {
        col[neighbor] = -col[node]; // -col[node] = 1 if col[node] = -1, and
                                    // -col[node] = -1 if col[node] = 1
        q.push(neighbor);
      }
      // If the neighbor has the same color as the current node, it is not
      // bipartite
      else if (col[neighbor] == col[node]) {
        return false;
      }
    }
  }

  return true;
}

// Entry function using BFS
bool isBipartite(vector<vector<int>> &graph) {
  int n = graph.size();

  // 0 represents uncolored, 1 represents Group A (color 1), -1 represents Group
  // B (color -1)
  vector<int> col(n, 0);

  // The graph can be disconnected, so we check each component
  for (int i = 0; i < n; i++) {
    if (col[i] == 0) {
      if (!bfs(i, graph, col)) {
        return false;
      }
    }
  }

  return true;
}
