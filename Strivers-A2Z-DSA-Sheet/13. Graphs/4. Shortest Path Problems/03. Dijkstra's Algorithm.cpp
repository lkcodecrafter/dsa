/*
QUESTION:
Given a weighted, undirected, and connected graph of V vertices and an adjacency
list 'adj', where 'adj[i]' is a list of lists containing two integers where the
first integer of each list j denotes there is an edge between node i and node j,
and the second integer corresponds to the weight of that edge. You are also
given the source vertex S. You need to find the shortest distance of all
vertices from the source vertex S. You have to return a list of integers
denoting the shortest distance between each node and the source vertex S.

APPROACH:
- We use Dijkstra's algorithm to find the shortest distance from the source
  vertex to all other vertices in a weighted graph.
- The algorithm maintains a priority queue (min-heap) to store the vertices
  based on their tentative distances from the source vertex. We start with the
  source vertex and update the distances of its neighbors, pushing them into the
  priority queue.
- We continue this process until all reachable vertices are processed. The
priority queue ensures that we always pick the vertex with the minimum tentative
distance next.
- We initialize the distance array 'dis' with infinity (1e9) for all vertices,
  except the source vertex whose distance is set to 0.

VISUALIZATION:
A weighted undirected graph with weights:

       (0)
     1 / \ 4
      v   v
    (1)--->(2)
        2

Shortest distances from source (0):
- Node 0: 0
- Node 1: 1
- Node 2: min(0+4, 1+2) = 3

DRY RUN:
Input: V = 3, adj = {0: {{1, 1}, {2, 4}}, 1: {{2, 2}}, 2: {}}, S = 0
Adjacency List:
0 -> {(1, 1), (2, 4)}  // {node, weight}
1 -> {(2, 2)}
2 -> {}

1. Initialize distances:
   dis = [0, 1e9, 1e9]
   pq = {(0, 0)}  // format: {distance, node}

2. Process priority queue:
   - Pop top {0, 0} from pq. Node u = 0.
     - For neighbor {1, 1}: dis[0] + 1 < dis[1] => 0 + 1 < 1e9 => 1 < 1e9 is
true. Update dis[1] = 1. Push {1, 1} to pq.
     - For neighbor {2, 4}: dis[0] + 4 < dis[2] => 0 + 4 < 1e9 => 4 < 1e9 is
true. Update dis[2] = 4. Push {4, 2} to pq. Current dis = [0, 1, 4], pq = {(1,
1), (4, 2)}

   - Pop top {1, 1} from pq. Node u = 1.
     - For neighbor {2, 2}: dis[1] + 2 < dis[2] => 1 + 2 < 4 => 3 < 4 is true.
       Update dis[2] = 3. Push {3, 2} to pq.
     Current dis = [0, 1, 3], pq = {(3, 2), (4, 2)}

   - Pop top {3, 2} from pq. Node u = 2.
     - Node 2 has no outgoing neighbors.
     Current dis = [0, 1, 3], pq = {(4, 2)}

   - Pop top {4, 2} from pq. Node u = 2.
     - Node 2 has no outgoing neighbors.
     Current dis = [0, 1, 3], pq = {}

3. Return dis = [0, 1, 3]

MEMORIZATION / RECALL SCENARIO:
- "The Path Finder GPS" analogy:
  - Think of nodes as cities, and edges as roads with toll fees (weights).
  - Dijkstra is like a GPS that explores roads outward from the starting city.
  - The min-heap priority queue acts as the GPS's agenda: always explore the
city with the lowest cumulative toll first.
  - Once a city is processed, we have found the absolute cheapest path to it.

COMPLEXITY ANALYSIS:
- Time Complexity: O((V + E) * log(V)) where V is the number of vertices and E
is the number of edges. Each node and edge is processed and priority queue
operations take O(log V).
- Space Complexity: O(V) for the distance array and priority queue.

1-MINUTE QUICK REVISION:
- Core Concept: Single-source shortest path for weighted graphs. Use priority
queue (min-heap) to select the closest node.
- Key Rule: Do not use visited array if distance array comparison `dis[u] + wt <
dis[v]` is sufficient to avoid redundant updates.
- Template Flow:
  1. Init `dis` array of size `V` with `1e9`. Set `dis[s] = 0`.
  2. Push `{0, s}` into min-heap `pq`.
  3. While `pq` is not empty:
     - Pop `{dist, u}`.
     - For each neighbor `v` of `u` with weight `wt`:
       - If `dis[u] + wt < dis[v]`, update `dis[v] = dis[u] + wt` and push
`{dis[v], v}` to `pq`.
  4. Return `dis`.

SUMMARY OF UPDATES & QUICK REVIEW:
- Visualization & ASCII Graph: Added a visual topology showing an example
weighted undirected graph.
- Step-by-Step Dry Run: Traced the states of variables (dis, priority queue pq,
and current node u) for all iterations of the main Dijkstra loop.
- Analogy/Memorization Scenario: Added "The Path Finder GPS" analogy.
- Inline Relaxation Comments: Documented the edge relaxation check with
positive/negative numeric examples.
- 1-Minute Quick Revision Section: Inserted a quick revision header to easily
review Dijkstra's template flow.

⏱️ 1-Minute Quick Review:
- Dijkstra's Goal: Finds the single-source shortest paths in weighted graphs
(works for both directed and undirected, but no negative cycles).
- Priority Queue (Min-Heap): Ensures we always process the reachable vertex with
the smallest tentative distance next, optimizing paths outward from the source.
- Edge Relaxation: Check if going through u to v yields a smaller path weight:
  - Update Example: dis[u]=2, wt=3, dis[v]=7 => 2 + 3 < 7 => dis[v] becomes 5
and {5, v} is pushed to the priority queue.
  - No Update Example: dis[u]=2, wt=3, dis[v]=4 => 2 + 3 < 4 is false => no
changes are made.
- Complexity: Runs in O((V + E) log V) time and O(V) auxiliary space.
*/

vector<int> dijkstra(int n, vector<vector<int>> adj[], int s) {
  vector<int> dis(n, 1e9);
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;

  dis[s] = 0;
  pq.push({0, s});

  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    for (auto p : adj[u]) {
      int v = p[0], wt = p[1];
      // Edge Relaxation (Through Node u):
      // Example (Update): If dis[u] = 2, wt = 3, and dis[v] = 7 (or 1e9),
      // then 2 + 3 < 7 (or 1e9) is true -> dis[v] becomes 5 and is pushed to
      // pq. Example (No Update): If dis[u] = 2, wt = 3, and dis[v] = 4, then 2
      // + 3 < 4 is false -> no update.
      if (dis[u] + wt < dis[v]) {
        dis[v] = dis[u] + wt;
        pq.push({dis[v], v});
      }
    }
  }

  return dis;
}
