#include <queue>
#include <vector>

using namespace std;

/*
QUESTION:
Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges,
check whether it contains any cycle or not.

APPROACHES:

1. DFS (using 3-State Coloring):
   - We use a state/vis array with 3 states:
     * 0 (White): Unvisited node.
     * 1 (Gray): Node is currently in the recursion stack (being visited).
     * 2 (Black): Node has been fully processed (backtracked).
   - If we encounter a neighbor with state 1 (visiting) during traversal, a
back-edge is found, indicating a cycle.

2. BFS (using Kahn's Algorithm / Topological Sort):
   - We compute the in-degree of all vertices.
   - Insert all vertices with in-degree 0 into a queue.
   - Pop nodes from the queue, increment a count, and decrement the in-degree of
their neighbors.
   - If a neighbor's in-degree becomes 0, push it to the queue.
   - If the count of visited nodes != V, it means there is a cycle (since
vertices in a cycle will never have their in-degrees reduced to 0).

COMPLEXITY ANALYSIS:
- Time Complexity: O(V + E) for both BFS and DFS.
- Space Complexity: O(V) for both BFS (queue, in-degree array) and DFS (state
array, recursion stack).
*/

/*
================================================================================
DFS DRY RUN:
Graph: 0 -> 1 -> 2 -> 0 (Cycle)
V = 3, E = 3
vis = [0, 0, 0] (0: unvisited, 1: visiting, 2: visited)

1. Start loop at i = 0. Since vis[0] == 0, call dfs(0).
   - Set vis[0] = 1 (visiting). [vis = {1, 0, 0}]
   - Neighbor of 0 is 1. Since vis[1] == 0, call dfs(1).
     - Set vis[1] = 1. [vis = {1, 1, 0}]
     - Neighbor of 1 is 2. Since vis[2] == 0, call dfs(2).
       - Set vis[2] = 1. [vis = {1, 1, 1}]
       - Neighbor of 2 is 0. Since vis[0] == 1 (already visiting in current
path), a cycle is detected! Return true.
       - dfs(2) returns true.
     - dfs(1) returns true.
   - dfs(0) returns true.
2. isCyclic returns true.
================================================================================
*/

// DFS helper function using 3-state coloring
bool dfs(int node, vector<vector<int>> &adj, vector<int> &vis) {
  vis[node] = 1; // Mark as visiting (in recursion stack)

  for (auto neighbor : adj[node]) {
    if (vis[neighbor] == 0) { // If neighbor is unvisited
      if (dfs(neighbor, adj, vis)) {
        return true;
      }
    } else if (vis[neighbor] ==
               1) { // If neighbor is currently visiting in the same path
      return true;  // Cycle detected
    }
  }

  vis[node] = 2; // Mark as fully processed
  return false;
}

/*
================================================================================
BFS (Kahn's Algorithm) DRY RUN:
Graph: 0 -> 1 -> 2 -> 0 (Cycle)
V = 3, E = 3

1. Compute indegrees:
   - 0 is pointed by 2 -> indegree[0] = 1
   - 1 is pointed by 0 -> indegree[1] = 1
   - 2 is pointed by 1 -> indegree[2] = 1
   indegree = [1, 1, 1]

2. Push all nodes with indegree 0 into queue:
   - Queue is empty! (q = [])

3. While loop:
   - Since queue is empty, loop doesn't run.
   - count of visited nodes = 0.

4. Check if count < V:
   - count (0) < V (3) is true.
   - Return true (cycle exists).
================================================================================
*/

// BFS cycle detection using Kahn's Algorithm
bool isCyclicBFS(int v, vector<vector<int>> &adj) {
  vector<int> indegree(v, 0);
  for (int i = 0; i < v; i++) {
    for (auto neighbor : adj[i]) {
      indegree[neighbor]++;
    }
  }

  queue<int> q;
  for (int i = 0; i < v; i++) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }

  int count = 0;
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    count++;

    for (auto neighbor : adj[node]) {
      indegree[neighbor]--;
      if (indegree[neighbor] == 0) {
        q.push(neighbor);
      }
    }
  }

  // If we could not visit all nodes, there is a cycle
  return count < v;
}

// Entry function to check if the graph is cyclic
bool isCyclic(vector<vector<int>> &edges, int v, int e) {
  vector<vector<int>> adj(v);
  for (auto it : edges) {
    adj[it[0]].push_back(it[1]);
  }

  // Option 1: DFS (3-State Coloring)
  vector<int> vis(v, 0); // 0: unvisited, 1: visiting, 2: visited
  for (int i = 0; i < v; i++) {
    if (vis[i] == 0) {
      if (dfs(i, adj, vis)) {
        return true;
      }
    }
  }
  return false;

  // Option 2: BFS (Kahn's Algorithm)
  // return isCyclicBFS(v, adj);
}
