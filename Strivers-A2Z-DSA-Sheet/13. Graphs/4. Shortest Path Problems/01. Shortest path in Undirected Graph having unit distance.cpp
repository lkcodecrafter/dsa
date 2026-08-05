/*
QUESTION:
You are given an undirected graph with unit weight. Find the shortest path from
the source vertex to all other vertices, and if it is unreachable to reach any
vertex, then return -1 for that vertex.

APPROACH:
- Standard BFS traversal is used to find the shortest path in an undirected
graph with unit weights.
- Initialize a distance array `dis` of size `N` with `-1` (indicating
unvisited/unreachable nodes).
- Set `dis[src] = 0` and push `src` into a queue.
- While the queue is not empty:
  - Pop the front `node`.
  - Traverse all its neighbors `v`. If a neighbor has not been visited (`dis[v]
== -1`), update its distance as `dis[v] = dis[node] + 1` and push it to the
queue.
- This approach avoids the need for a separate boolean `visited` array and
level-by-level `lvl` variables.

VISUALIZATION:
Input Graph (N = 4, edges = {{0, 1}, {0, 2}, {1, 3}}, src = 0):

     (0) [dist = 0]
    /   \
   /     \
 (1)     (2) [dist = 1]
  | [dist = 1]
  |
 (3) [dist = 2]

DRY RUN:
Adjacency List:
0 -> {1, 2}
1 -> {0, 3}
2 -> {0}
3 -> {1}

Execution:
1. Initialize:
   dis = [-1, -1, -1, -1]
   q = []

2. Start with source (0):
   dis[0] = 0
   q.push(0) -> q = [0]
   dis = [0, -1, -1, -1]

3. While Loop:
   - Pop 0 from q: node = 0, q = []
     - Neighbor 1: dis[1] == -1 -> Set dis[1] = dis[0] + 1 = 1. q.push(1) -> q =
[1]
     - Neighbor 2: dis[2] == -1 -> Set dis[2] = dis[0] + 1 = 1. q.push(2) -> q =
[1, 2] Current dis = [0, 1, 1, -1]

   - Pop 1 from q: node = 1, q = [2]
     - Neighbor 0: dis[0] != -1 (already visited) -> Skip
     - Neighbor 3: dis[3] == -1 -> Set dis[3] = dis[1] + 1 = 2. q.push(3) -> q =
[2, 3] Current dis = [0, 1, 1, 2]

   - Pop 2 from q: node = 2, q = [3]
     - Neighbor 0: dis[0] != -1 (already visited) -> Skip
     Current dis = [0, 1, 1, 2]

   - Pop 3 from q: node = 3, q = []
     - Neighbor 1: dis[1] != -1 (already visited) -> Skip
     Current dis = [0, 1, 1, 2]

4. Queue is empty. Return dis = [0, 1, 1, 2].

MEMORIZATION / RECALL SCENARIO:
- "The Ripple in a Pond" analogy:
  - Source node is where you drop a stone.
  - The ripple spreads outward to neighbors at distance 1, then to their
neighbors at distance 2, and so on.
  - If a place is dry (distance is -1), the water reaches it and sets its
distance to: Current Node's distance + 1.
  - Since the water reaches a spot for the first time via the shortest path, we
lock in that distance and never update it again (if dis[v] != -1, skip it).

COMPLEXITY ANALYSIS:
- Time Complexity: O(N + M), where N is the number of vertices and M is the
number of edges. We visit each node and edge at most once.
- Space Complexity: O(N + M) for the adjacency list and O(N) for the distance
array and BFS queue.

1-MINUTE QUICK REVISION:
- Core Concept: BFS finds shortest paths in unweighted graphs level-by-level.
- Main Optimization: Avoid `vis` vector and `lvl` variable. Use `dis[v] == -1`
to check if visited, and update `dis[v] = dis[node] + 1` directly.
- Template Flow:
  1. Build adjacency list.
  2. Init `dis` array to `-1`, set `dis[src] = 0`.
  3. Push `src` to queue `q`.
  4. BFS Loop: While `q` not empty -> Pop `node` -> For neighbors `v` of `node`
-> If `dis[v] == -1` -> `dis[v] = dis[node] + 1`, `q.push(v)`.
  5. Return `dis`.
*/

#include <queue>
#include <vector>
using namespace std;

vector<int> shortestPath(vector<vector<int>> &edges, int N, int M, int src) {
  // Step 1: Build the undirected adjacency list
  vector<int> adj[N];
  for (auto &e : edges) {
    adj[e[0]].push_back(e[1]);
    adj[e[1]].push_back(e[0]);
  }

  // Step 2: Initialize distance array with -1 (meaning unvisited)
  vector<int> dis(N, -1);
  queue<int> q;

  // Step 3: Initialize source node distance to 0 and push to queue
  dis[src] = 0;
  q.push(src);

  // Step 4: BFS traversal
  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (auto v : adj[node]) {
      // If neighbor v is not visited, its distance is node's distance + 1
      if (dis[v] == -1) {
        dis[v] = dis[node] + 1;
        q.push(v);
      }
    }
  }

  return dis;
}
