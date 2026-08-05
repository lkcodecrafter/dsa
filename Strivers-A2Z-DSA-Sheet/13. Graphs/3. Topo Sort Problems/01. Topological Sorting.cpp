/*
QUESTION:
Given a DAG (directed acyclic graph), print the Topological sorting of a given
graph.

APPROACH:
- Topological sorting is a linear ordering of vertices in a directed acyclic
graph (DAG) such that for every directed edge u -> v, vertex u comes before v in
the ordering.
- To find the topological sorting, we can use Depth-First Search (DFS) with
backtracking.
- We perform DFS starting from each unvisited node, and as we finish exploring a
node and backtrack, we add it to the front of the topological sorting order.

COMPLEXITY ANALYSIS:
- Time Complexity: O(V + E), where V is the number of vertices (nodes) and E is
the number of edges in the graph. We visit each node and each edge exactly once
during the DFS.
- Space Complexity: O(V), where V is the number of vertices (nodes) in the
graph. We use additional space to store the visited status of the nodes and the
topological sorting order.

DRY RUN:
Graph:
Nodes: 6 (0 to 5)
Edges: 5->0, 5->2, 4->0, 4->1, 2->3, 3->1

Adjacency List (adj):
0: []
1: []
2: [3]
3: [1]
4: [0, 1]
5: [0, 2]

Initial State:
vis = [false, false, false, false, false, false]
ans = []

Execution Steps:
- i = 0: vis[0] is false -> call dfs(0)
  - dfs(0): vis[0] = true. adj[0] is empty. Push 0 to ans. ans = [0]. Return.
- i = 1: vis[1] is false -> call dfs(1)
  - dfs(1): vis[1] = true. adj[1] is empty. Push 1 to ans. ans = [0, 1]. Return.
- i = 2: vis[2] is false -> call dfs(2)
  - dfs(2): vis[2] = true. adj[2] has 3. vis[3] is false -> call dfs(3)
    - dfs(3): vis[3] = true. adj[3] has 1. vis[1] is true (skip). Push 3 to ans.
ans = [0, 1, 3]. Return.
  - Push 2 to ans. ans = [0, 1, 3, 2]. Return.
- i = 3: vis[3] is true -> skip.
- i = 4: vis[4] is false -> call dfs(4)
  - dfs(4): vis[4] = true. Neighbors 0 and 1 are already visited. Push 4 to ans.
ans = [0, 1, 3, 2, 4]. Return.
- i = 5: vis[5] is false -> call dfs(5)
  - dfs(5): vis[5] = true. Neighbors 0 and 2 are already visited. Push 5 to ans.
ans = [0, 1, 3, 2, 4, 5]. Return.

After Loop:
ans = [0, 1, 3, 2, 4, 5]
Reverse ans -> [5, 4, 2, 3, 1, 0] (Valid Topological Sort)
*/

void dfs(int node, vector<vector<int>> &adj, vector<bool> &vis,
         vector<int> &ans) {
  vis[node] = true;
  for (auto v : adj[node]) {
    if (!vis[v]) {
      dfs(v, adj, vis, ans);
    }
  }
  // After all neighbors are visited, push the current node to the ans vector
  ans.push_back(node);
}

vector<int> topologicalSort(vector<vector<int>> &graph, int edges, int nodes) {
  // Build adjacency list using vector of vectors
  vector<vector<int>> adj(nodes);
  for (auto it : graph) {
    adj[it[0]].push_back(it[1]);
  }

  vector<bool> vis(nodes, false);
  vector<int> ans;

  // Perform DFS for each unvisited node to cover disconnected components
  for (int i = 0; i < nodes; i++) {
    if (!vis[i]) {
      dfs(i, adj, vis, ans);
    }
  }

  // Reversing the answer gives the topological sort order
  reverse(ans.begin(), ans.end());

  return ans;
}
