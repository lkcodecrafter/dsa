/*
QUESTION:
Given a Directed Acyclic Graph of N vertices from 0 to N-1 and a 2D Integer
array (or vector) edges[][] of length M, where there is a directed edge from
edges[i][0] to edges[i][1] with a distance of edges[i][2] for all i.

Find the shortest path from the source (vertex 0) to all other vertices, and if
it is impossible to reach any vertex, then return -1 for that vertex.

APPROACH:
- To find the shortest path from the source vertex in a Directed Acyclic Graph
(DAG), we use Topological Sorting.
- By processing vertices in topological order, we ensure that we calculate the
shortest path to a vertex only after we have finalized the shortest paths to all
of its possible predecessor vertices.
- First, perform DFS topological sorting of the entire DAG.
- Second, initialize a distance array `dis` with `1e9` (infinity) and set
`dis[0] = 0`.
- Third, iterate through the topological order. For each node `u` that is
reachable (i.e., `dis[u] != 1e9`), update the distance of its neighbors: `dis[v]
= min(dis[v], dis[u] + weight)`.
- Finally, convert any unreachable nodes still at `1e9` to `-1`.

VISUALIZATION:
A Directed Acyclic Graph (DAG) with weights:

      (0)
     /   \
  2 /     \ 1
   v       v
  (1)----->(2)
      3

Topological Order: 0 -> 1 -> 2
Shortest distances from source (0):
- Node 0: 0
- Node 1: 2
- Node 2: min(0+1, 2+3) = 1

DRY RUN:
Input: N = 3, edges = {{0, 1, 2},
                       {0, 2, 1},
                       {1, 2, 3}}

Adjacency List:
0 -> {(1, 2), (2, 1)}  // (1,2) means {node, weight}
1 -> {(2, 3)}
2 -> {}

1. DFS for Topological Sort:
   - Call dfs(0):
     - vis[0] = true
     - For neighbor (1, 2): dfs(1) is called:
       - vis[1] = true
       - For neighbor (2, 3): dfs(2) is called:
         - vis[2] = true
         - Node 2 has no neighbors. topo.push_back(2). Return.
       - topo.push_back(1). Return.
     - For neighbor (2, 1): neighbor 2 is already visited. Skip.
     - topo.push_back(0). Return.
   Result topo (reversed): [0, 1, 2]

2. Initialize distances:
   dis = [0, 1e9, 1e9]

3. Relax edges in topological order:
   - For u = 0 (dis[0] = 0):
     - Neighbor (1, 2): dis[1] = min(1e9, dis[0] + 2) = 2
     - Neighbor (2, 1): dis[2] = min(1e9, dis[0] + 1) = 1
     Current dis = [0, 2, 1]
   - For u = 1 (dis[1] = 2):
     - Neighbor (2, 3): dis[2] = min(1, dis[1] + 3) = min(1, 5) = 1
     Current dis = [0, 2, 1]
   - For u = 2 (dis[2] = 1):
     - No neighbors.

4. Replace remaining 1e9 with -1.
   Return dis = [0, 2, 1]

MEMORIZATION / RECALL SCENARIO:
- "The Assembly Line" analogy:
  - Think of nodes as stations on a dependency assembly line (DAG).
  - To find the minimum cost to complete each station, you must work from left
to right (Topological Order).
  - Because there are no cycles, once you finish processing a station, all
possible ways to reach it have been evaluated. You can then confidently compute
costs for downstream stations.

COMPLEXITY ANALYSIS:
- Time Complexity: O(N + M), where N is the number of vertices and M is the
number of edges. Topological sort takes O(N + M) and relaxation of edges takes
O(N + M).
- Space Complexity: O(N + M) for adjacency list and O(N) for visited array,
topological order list, and distance array.

1-MINUTE QUICK REVISION:
- Core Concept: Shortest path in a DAG is solved in O(N + M) using Topological
Sort. No Dijkstra is needed because there are no cycles!
- Why it works: Processing nodes in topological order guarantees that we
evaluate all incoming paths to node `u` before relaxing its outgoing edges.
- Template Flow:
  1. Build adjacency list of pairs `{v, weight}`.
  2. Compute Topological Sort of the entire graph via DFS.
  3. Init `dis` array of size `N` with `1e9`. Set `dis[0] = 0`.
  4. Iterate through `topo`:
     - If `dis[u] != 1e9` (reachable):
       - Relax all neighbors: `dis[v] = min(dis[v], dis[u] + weight)`.
  5. Replace remaining `1e9` with `-1` and return `dis`.
*/

#include <algorithm>
#include <vector>
using namespace std;

// DFS helper to get Topological Sort
void dfs(int node, vector<pair<int, int>> adj[], vector<bool> &vis,
         vector<int> &topo) {
  vis[node] = true;
  for (auto &v : adj[node]) {
    if (!vis[v.first]) {
      dfs(v.first, adj, vis, topo);
    }
  }
  topo.push_back(node);
}

vector<int> shortestPath(int N, int M, vector<vector<int>> &edges) {
  // Step 1: Build adjacency list
  vector<pair<int, int>> adj[N];
  for (auto &e : edges) {
    adj[e[0]].push_back({e[1], e[2]});
  }

  // Step 2: Perform topological sorting
  vector<bool> vis(N, false);
  vector<int> topo;
  for (int i = 0; i < N; i++) {
    if (!vis[i]) {
      dfs(i, adj, vis, topo);
    }
  }
  reverse(topo.begin(), topo.end());

  // Step 3: Initialize distance array
  vector<int> dis(N, 1e9);
  dis[0] = 0; // Source is always vertex 0

  // Step 4: Relax edges in topological order
  for (auto u : topo) {
    if (dis[u] != 1e9) { // Only process reachable nodes
      for (auto &p : adj[u]) {
        int v = p.first;
        int d = p.second;
        // Edge Relaxation (Through Node u):
        // Example (Update): If dis[u] = 2, d = 3, and dis[v] = 7 (or 1e9),
        // then 2 + 3 < 7 (or 1e9) is true -> dis[v] becomes 5.
        // Example (No Update): If dis[u] = 2, d = 3, and dis[v] = 4, then 2 +
        // 3 < 4 is false -> no update.
        if (dis[u] + d < dis[v]) {
          dis[v] = dis[u] + d;
        }
      }
    }
  }

  // Step 5: Convert unreachable nodes from 1e9 to -1
  for (int i = 0; i < N; i++) {
    if (dis[i] == 1e9) {
      dis[i] = -1;
    }
  }

  return dis;
}

/*
Initial Setup (Before Loop starts)
Topological Order (topo): [0, 1, 2]
Distance Array (dis): [0, 1e9, 1e9] (where dis[0] = 0 and others are set to
infinity 1e9).
Adjacency List (adj): 0 -> {(1, 2), (2, 1)} 1 -> {(2, 3)} 2 -> {}

Step-by-Step Execution
Iteration 1: u = 0 Reachability Check: dis[0] != 1e9
-> 0 != 1e9 is true (we process node 0). Neighbor 1: p = {1, 2}
-> v = 1, d = 2 (edge 0 -> 1 with weight 2) Check: dis[0] + d < dis[1]
-> 0 + 2 < 1e9 -> 2 < 1e9 (is true). Update: dis[1] = 0 + 2 = 2.
Current dis: [0, 2, 1e9] Neighbor 2: p = {2, 1} -> v = 2, d = 1 (edge 0 -> 2
with weight 1) Check: dis[0] + d < dis[2] -> 0 + 1 < 1e9 -> 1 < 1e9 (is true).
Update: dis[2] = 0 + 1 = 1. Current dis: [0, 2, 1]

Iteration 2: u = 1 Reachability Check: dis[1] != 1e9
-> 2 != 1e9 is true (we process node 1). Neighbor 1: p = {2, 3}
-> v = 2, d = 3 (edge 1 -> 2 with weight 3) Check: dis[1] + d < dis[2]
-> 2 + 3 < 1 -> 5 < 1 (is false). No Update: The current path to
node 2 (cost 1) is shorter than the new path via node 1 (cost 5). Current dis:
[0, 2, 1]

Iteration 3: u = 2 Reachability Check: dis[2] != 1e9
-> 1 != 1e9
is true (we process node 2). Neighbors: Node 2 has no outgoing edges.
Current dis: [0, 2, 1]
Final Output
The loop terminates, and dis array is returned as: [0, 2, 1].

⏱️ 1-Minute Quick Review
First Iteration (u=0): Relaxes edges to 1 and 2, updating dis[1] = 2 and dis[2]
= 1. Second Iteration (u=1): Tries to relax edge to 2, check fails because $2 +
3 < 1$ is false. No change is made. Third Iteration (u=2): Node has no outgoing
neighbors, loop ends.


*/