/*
QUESTION:
There is a directed graph of n nodes with each node labeled from 0 to n - 1. The
graph is represented by a 0-indexed 2D integer array graph where graph[i] is an
integer array of nodes adjacent to node i, meaning there is an edge from node i
to each node in graph[i].

A node is a terminal node if there are no outgoing edges. A node is a safe node
if every possible path starting from that node leads to a terminal node (or
another safe node).

APPROACH:
- A terminal node has an outdegree of 0.
- Any node that only leads to terminal nodes (or other safe nodes) is also safe.
- By reversing the direction of all edges:
  1. Terminal nodes (outdegree 0) become starting points.
  2. Edges point from dependencies (destination nodes) back to the nodes that
depend on them.
- We track the outdegree of each node in the original graph.
- We initialize a queue with all nodes that have an outdegree of 0 (terminal
nodes).
- In a BFS-like traversal:
  - We dequeue a safe node and add it to our list of safe nodes.
  - We traverse its neighbors in the reversed graph (i.e., nodes that had
directed edges to the current safe node).
  - We decrement their outdegree since they can now safely reach a terminal/safe
node through the current node.
  - If a node's outdegree drops to 0, it means all its outgoing paths lead to
safe nodes. We then push it to the queue.
- Finally, we sort the safe nodes list to return them in ascending order.

COMPLEXITY ANALYSIS:
- Time Complexity: O(N + E), where N is the number of nodes and E is the number
  of edges in the graph. We traverse all nodes and edges during graph creation
and BFS.
- Space Complexity: O(N + E), to store the reversed adjacency list, outdegree
array, and the BFS queue.

DRY RUN:

Scenario 1: Graph with safe nodes and terminal nodes
Input: graph = [[1, 2], [2, 3], [5], [0], [5], [], []]
Graph representation:
- 0 -> 1, 2
- 1 -> 2, 3
- 2 -> 5
- 3 -> 0
- 4 -> 5
- 5 -> (terminal)
- 6 -> (terminal)

1. Initialization:
   - n = 7
   - outdegree = [0, 0, 0, 0, 0, 0, 0] (Size 7)
   - reverseAdj = [[], [], [], [], [], [], []] (Size 7)

2. Build Reverse Adjacency List & Outdegrees:
   - Node 0: graph[0] = [1, 2]. outdegree[0] = 2. reverseAdj[1] = [0],
reverseAdj[2] = [0]
   - Node 1: graph[1] = [2, 3]. outdegree[1] = 2. reverseAdj[2] = [0, 1],
reverseAdj[3] = [1]
   - Node 2: graph[2] = [5].    outdegree[2] = 1. reverseAdj[5] = [2]
   - Node 3: graph[3] = [0].    outdegree[3] = 1. reverseAdj[0] = [3]
   - Node 4: graph[4] = [5].    outdegree[4] = 1. reverseAdj[5] = [2, 4]
   - Node 5: graph[5] = [].     outdegree[5] = 0.
   - Node 6: graph[6] = [].     outdegree[6] = 0.

   Final outdegree array: [2, 2, 1, 1, 1, 0, 0]
   Final reverseAdj list:
     0: [3]
     1: [0]
     2: [0, 1]
     3: [1]
     4: []
     5: [2, 4]
     6: []

3. Populate Queue with 0-outdegree nodes:
   - outdegree[5] == 0 -> Push 5. Queue q = [5]
   - outdegree[6] == 0 -> Push 6. Queue q = [5, 6]

4. BFS Process:
   - Pop 5:
     - Add 5 to safeNodes. safeNodes = [5]
     - Neighbors of 5 in reverseAdj: [2, 4]
     - For neighbor 2: outdegree[2] decrements from 1 to 0. Since it becomes 0,
push 2. q = [6, 2]
     - For neighbor 4: outdegree[4] decrements from 1 to 0. Since it becomes 0,
push 4. q = [6, 2, 4]
   - Pop 6:
     - Add 6 to safeNodes. safeNodes = [5, 6]
     - Neighbors of 6 in reverseAdj: None.
   - Pop 2:
     - Add 2 to safeNodes. safeNodes = [5, 6, 2]
     - Neighbors of 2 in reverseAdj: [0, 1]
     - For neighbor 0: outdegree[0] decrements from 2 to 1. (Does not push)
     - For neighbor 1: outdegree[1] decrements from 2 to 1. (Does not push)
   - Pop 4:
     - Add 4 to safeNodes. safeNodes = [5, 6, 2, 4]
     - Neighbors of 4 in reverseAdj: None.
   - Queue is now empty.

5. Sort & Return:
   - Sort safeNodes: [2, 4, 5, 6]
   - Return [2, 4, 5, 6] (Nodes 0, 1, and 3 are in a cycle: 0 -> 1 -> 3 -> 0, so
they are not safe)


Scenario 2: Graph with a direct cycle and isolated components
Input: graph = [[1], [0], [3], []]
Graph representation:
- 0 -> 1 (Cycle)
- 1 -> 0 (Cycle)
- 2 -> 3
- 3 -> (terminal)

1. Initialization:
   - outdegree = [1, 1, 1, 0]
   - reverseAdj:
     0: [1]
     1: [0]
     2: []
     3: [2]

2. Queue setup:
   - outdegree[3] == 0 -> Push 3. Queue q = [3]

3. BFS:
   - Pop 3:
     - Add 3 to safeNodes. safeNodes = [3]
     - Neighbors of 3 in reverseAdj: [2]
     - For neighbor 2: outdegree[2] decrements from 1 to 0. Push 2. q = [2]
   - Pop 2:
     - Add 2 to safeNodes. safeNodes = [3, 2]
     - Neighbors of 2 in reverseAdj: None.
   - Queue is now empty.

4. Sort & Return:
   - Sort safeNodes: [2, 3]
   - Return [2, 3]
*/

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
  int n = graph.size();

  // Create a reverse adjacency list and an outdegree tracker for each node
  vector<vector<int>> reverseAdj(n);
  vector<int> outdegree(n, 0);

  for (int u = 0; u < n; u++) {
    for (auto v : graph[u]) {
      // Create a reversed edge from v to u (v -> u)
      reverseAdj[v].push_back(u);
      outdegree[u]++; // Increment outdegree for each outgoing edge from u
    }
  }

  // Queue to process nodes that have an outdegree of 0 (safely lead to terminal
  // nodes)
  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (outdegree[i] == 0) {
      q.push(i);
    }
  }

  vector<int> safeNodes;

  // Process nodes from the queue
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    safeNodes.push_back(curr);

    // Decrement the outdegree of nodes that have a directed edge to curr
    for (auto neighbor : reverseAdj[curr]) {
      outdegree[neighbor]--;

      // If all outgoing edges of neighbor lead to safe nodes, it is also safe
      if (outdegree[neighbor] == 0) {
        q.push(neighbor);
      }
    }
  }

  // The problem requires returning safe node labels in sorted ascending order
  sort(safeNodes.begin(), safeNodes.end());

  return safeNodes;
}
