# Module 9: Graph Theory (Lectures 118–141)

## 📋 Syllabus
*   **Basics:** Matrix/List Representations, BFS, DFS.
*   **Topological Sorting:** Kahn's Algorithm (BFS), DFS Topo Sort, Cycle Detection (Directed/Undirected).
*   **Shortest Paths:** Dijkstra (Weighted), Bellman-Ford (Negative Weights), Floyd-Warshall (All-Pairs).
*   **Spanning Trees & Disjoint Set:** Prim's, Kruskal's, Disjoint Set Union (DSU) by Rank/Size.
*   **Advanced:** Kosaraju's Algorithm (SCC), Tarjan's (Bridge/Articulation Points), Euler/Hamiltonian Paths.

---

## 🟢 Section 1: Traversals & Topological Sorting

### 🎯 Solution 9.1: BFS, DFS & Graph Representations
*   **C++ Code:**
```cpp
#include <vector>
#include <queue>
#include <iostream>

// Adjacency List BFS
void bfs(int start, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        std::cout << node << " ";
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// Adjacency List DFS
void dfs(int node, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
    visited[node] = true;
    std::cout << node << " ";
    
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}
```
*   **Complexity:** Time: $O(V + E)$, Space: $O(V)$ for visited array and recursion/queue storage.

### 🎯 Solution 9.2: Topological Sort (Kahn's BFS Algorithm)
*   **Problem:** Find the linear ordering of vertices in a Directed Acyclic Graph (DAG).
*   **C++ Code:**
```cpp
#include <vector>
#include <queue>

std::vector<int> topoSortKahn(int V, const std::vector<std::vector<int>>& adj) {
    std::vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }
    
    std::queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    
    std::vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
        }
    }
    return topo;
}
```
*   **Complexity:** Time: $O(V + E)$, Space: $O(V)$.

---

## 🟢 Section 2: Shortest Paths

### 🎯 Solution 9.3: Dijkstra's Algorithm
*   **Problem:** Find shortest path from source vertex to all vertices in a weighted graph (no negative weights).
*   **C++ Code:**
```cpp
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

/*
 * ============================================================================
 * 🧠 DETAILED FUNCTOR & STL PRIORITY_QUEUE MECHANICS
 * ============================================================================
 * Container Type: std::priority_queue<Type, Container, Comparator>
 * Usage:          std::priority_queue<std::pair<int, int>, 
 *                                     std::vector<std::pair<int, int>>, 
 *                                     std::greater<std::pair<int, int>>> pq;
 *
 * 1. Functor & Comparator Internals:
 *    - `std::greater<T>` is a standard functor with an overloaded `operator()`:
 *        bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
 *            return a > b; // compares .first (distance), then .second (node ID)
 *        }
 *    - By default, std::priority_queue uses `std::less<T>`, creating a MAX-HEAP.
 *    - Passing `std::greater<T>` instructs the heap to compare parent and child.
 *
 * 2. Heap Reordering & Bubble-Down Invariant:
 *    - When the comparator `std::greater(parent, child)` evaluates to `true`, the
 *      parent is strictly greater than the child, violating the min-heap property.
 *    - STL performs a BUBBLE-DOWN operation to push the larger element deeper,
 *      guaranteeing that the smallest distance element always remains at `pq.top()`.
 *
 * 3. Lazy Deletion (`if (d > dist[u]) continue;`):
 *    - STL `priority_queue` does not offer an O(log V) `decrease_key` operation.
 *    - When a shorter path to vertex `u` is found, we push `{new_dist, u}` into `pq`.
 *    - Older, longer paths `{old_dist, u}` stay in the heap as "stale" entries.
 *    - When popped, if `d > dist[u]`, node `u` has already been relaxed with a shorter
 *      distance. Skipping it (`continue`) prevents redundant edge traversals and keeps
 *      the runtime strictly at O((V + E) log V).
 * ============================================================================
 */

// Function to compute single-source shortest path from `src` (0-indexed or 1-indexed)
std::vector<int> dijkstra(int V, const std::vector<std::vector<std::pair<int, int>>>& adj, int src) {
    // Distance array initialized to infinity (INT_MAX)
    std::vector<int> dist(V + 1, INT_MAX);
    
    // Min-heap storing pairs of {distance, node}
    std::priority_queue<std::pair<int, int>, 
                        std::vector<std::pair<int, int>>, 
                        std::greater<std::pair<int, int>>> pq;
    
    // Base case: distance to source itself is 0
    dist[src] = 0;
    pq.push({0, src});
    
    while (!pq.empty()) {
        int d = pq.top().first;   // Current shortest tentative distance to u
        int u = pq.top().second;  // Current vertex being explored
        pq.pop();
        
        // Skip stale entries: if current popped distance is greater than the recorded
        // optimal distance, a better path has already been processed for vertex u.
        if (d > dist[u]) continue;
        
        // Relax all outgoing edges from vertex u
        for (const auto& edge : adj[u]) {
            int v = edge.first;       // Neighbor vertex , but first is dist? no in adj first is neighbour
            int weight = edge.second; // Edge weight (u -> v)
            
            // Relaxation step: check if path through u is shorter than existing path to v
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v}); // Push updated optimal distance
            }
        }
    }
    return dist;
}

/*
 * ============================================================================
 * 📊 GRAPH TOPOLOGY VISUALIZATION (User Example)
 * ============================================================================
 *
 *           (wt: 5)
 *      [1] ----------> [2]
 *       |
 *       | (wt: 2)
 *       v
 *      [3] ----------> [4]
 *           (wt: 3)
 *
 *  - Vertices: {1, 2, 3, 4}
 *  - Source Node: 1
 *  - Directed Weighted Edges:
 *      1 -> 2 (weight: 5)
 *      1 -> 3 (weight: 2)
 *      3 -> 4 (weight: 3)
 * ============================================================================
 *
 * ============================================================================
 * 📋 STEP-BY-STEP DRY RUN TABLE
 * ============================================================================
 * +------+-----------+-------------+----------------------+--------------------+--------------------+---------------------------+
 * | Step | Pop (d,u) | d > dist[u] | Relaxation Condition | Action / Update    | dist[] Array       | Priority Queue (Min-Heap) |
 * +------+-----------+-------------+----------------------+--------------------+--------------------+---------------------------+
 * | Init | -         | -           | -                    | dist[1] = 0        | [0, ∞, ∞, ∞]       | {(0, 1)}                  |
 * | 1    | (0, 1)    | 0 > 0 (F)   | 0 + 5 < ∞ -> 5       | dist[2] = 5, push  | [0, 5, ∞, ∞]       | {(5, 2)}                  |
 * |      |           |             | 0 + 2 < ∞ -> 2       | dist[3] = 2, push  | [0, 5, 2, ∞]       | {(2, 3), (5, 2)}          |
 * | 2    | (2, 3)    | 2 > 2 (F)   | 2 + 3 < ∞ -> 5       | dist[4] = 5, push  | [0, 5, 2, 5]       | {(5, 2), (5, 4)}          |
 * | 3    | (5, 2)    | 5 > 5 (F)   | No outgoing edges    | Node 2 processed   | [0, 5, 2, 5]       | {(5, 4)}                  |
 * | 4    | (5, 4)    | 5 > 5 (F)   | No outgoing edges    | Node 4 processed   | [0, 5, 2, 5]       | {}                        |
 * +------+-----------+-------------+----------------------+--------------------+--------------------+---------------------------+
 *
 * ============================================================================
 * 🔍 LINE-BY-LINE EXECUTION TRACE
 * ============================================================================
 * [Initialization]:
 *   - dist = [dist[1]=0, dist[2]=INF, dist[3]=INF, dist[4]=INF]
 *   - pq.push({0, 1}) -> Min-Heap: {(0, 1)}
 *
 * [Step 1: Pop (0, 1)]:
 *   - d = 0, u = 1. Condition (0 > dist[1]) -> 0 > 0 is FALSE.
 *   - Neighbor 2: dist[1] + 5 = 0 + 5 = 5 < dist[2] (INF) -> dist[2] = 5. Push ({5, 2}).
 *   - Neighbor 3: dist[1] + 2 = 0 + 2 = 2 < dist[3] (INF) -> dist[3] = 2. Push ({2, 3}).
 *   - Min-heap re-orders to: {(2, 3), (5, 2)}
 *
 * [Step 2: Pop (2, 3)]:
 *   - d = 2, u = 3. Condition (2 > dist[3]) -> 2 > 2 is FALSE.
 *   - Neighbor 4: dist[3] + 3 = 2 + 3 = 5 < dist[4] (INF) -> dist[4] = 5. Push ({5, 4}).
 *   - Min-heap re-orders to: {(5, 2), (5, 4)}
 *
 * [Step 3: Pop (5, 2)]:
 *   - d = 5, u = 2. Condition (5 > dist[2]) -> 5 > 5 is FALSE.
 *   - Node 2 has no outgoing edges -> Nothing to push.
 *   - Min-heap contains: {(5, 4)}
 *
 * [Step 4: Pop (5, 4)]:
 *   - d = 5, u = 4. Condition (5 > dist[4]) -> 5 > 5 is FALSE.
 *   - Node 4 has no outgoing edges -> Nothing to push.
 *   - Min-heap is now EMPTY [].
 *
 * [Final Result from Source 1]:
 *   - dist[1] = 0 (1 -> 1)
 *   - dist[2] = 5 (1 -> 2)
 *   - dist[3] = 2 (1 -> 3)
 *   - dist[4] = 5 (1 -> 3 -> 4)
 * ============================================================================
 *
 * ============================================================================
 * 💡 MEMORIZATION & RECALL SCENARIO (GPS Fast-Toll Analogy)
 * ============================================================================
 *  Think of Dijkstra like a GPS navigation app finding the cheapest toll route:
 *  1. Priority Queue = "Upcoming Nearest Checkpoints". Always process the cheapest
 *     accessible booth next (Greedy approach).
 *  2. Relaxation (`dist[u] + wt < dist[v]`) = "Shortcut Discovery". If taking
 *     a road via checkpoint `u` reaches `v` cheaper than previous estimates,
 *     update the GPS route to `v`.
 *  3. `d > dist[u]` check = "Outdated Alert Filter". If you already reached `u`
 *     via a faster path earlier, ignore old, slower route notifications in the queue.
 * ============================================================================
 *
 * ============================================================================
 * ⏱️ 1-MINUTE QUICK REVISION
 * ============================================================================
 *  - Goal: Single-Source Shortest Path (SSSP) on Non-Negative Weighted Graphs.
 *  - Key Data Structures: Min-Heap (`std::priority_queue` with `std::greater`) + `dist[]` array.
 *  - Initialization: `dist[src] = 0`, all other `dist[i] = INT_MAX`, push `{0, src}`.
 *  - Process Loop: Pop smallest `(d, u)`. If `d > dist[u]`, skip (stale entry).
 *  - Edge Relaxation: For every outgoing edge `u -> v` with weight `wt`:
 *      if `dist[u] + wt < dist[v]`:
 *          `dist[v] = dist[u] + wt`
 *          `pq.push({dist[v], v})`
 *  - Time Complexity: $O((V + E) \log V)$ | Space Complexity: $O(V + E)$
 *  - Constraint: Cannot handle negative edge weights (use Bellman-Ford).
 * ============================================================================
 */
```
*   **Complexity:** Time: $O((V + E) \log V)$, Space: $O(V + E)$ adjacency structure.

### 🎯 Solution 9.4: Bellman-Ford & Floyd-Warshall Shortest Paths
*   **C++ Code:**
```cpp
#include <vector>
#include <climits>

// 1. Bellman-Ford (For negative weight cycles detection & shortest path)
std::vector<int> bellmanFord(int V, const std::vector<std::vector<int>>& edges, int src, bool& hasNegCycle) {
    std::vector<int> dist(V, 1e8); // Using 1e8 to prevent overflow
    dist[src] = 0;
    
    for (int i = 0; i < V - 1; i++) {
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], wt = edge[2];
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }
    
    // N-th relaxation to check negative cycle
    hasNegCycle = false;
    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
            hasNegCycle = true;
            break;
        }
    }
    return dist;
}

// 2. Floyd-Warshall (All Pairs Shortest Path) - Using for APSP problem (All pairs shortest path) means try to find shortest path between all pairs of vertices
void floydWarshall(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == -1) matrix[i][j] = 1e9;
            if (i == j) matrix[i][j] = 0;
        }
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]); // Path 1: Current best A → B, Path 2: Via new vertex k (A → k → B)
            }
        }
    }
}

/*
 * ============================================================================
 * 🧠 MEMORY RETRIEVAL: WHY FLOYD-WARSHALL WORKS
 * ============================================================================
 *  Think of the 3 nested loops as building a "Chain of Knowledge" for every pair of nodes.
 * 
 *  Outer Loop (k): The "Gatekeeper"
 *  - 'k' represents the *latest* vertex (highest index) allowed in the path.
 *  - When k=0, we only allow paths using node 0.
 *  - When k=1, we allow paths using nodes {0, 1}.
 *  - When k=N-1, we allow paths using ALL nodes.
 * 
 *  Inner Loops (i, j): The "Path Builders"
 *  - 'i' is the starting node.
 *  - 'j' is the destination node.
 * 
 *  The Logic: min(matrix[i][j], matrix[i][k] + matrix[k][j])
 *  ============================================================================
 *    Let's take the example: Find the shortest path from A (0) to D (3).
 * 
 *    We look at the "Gatekeeper" k.
 * 
 *  1. k = 0 (Gate: Node A only)
 *     - Check Path A -> D: matrix[0][0] + matrix[0][3]. 
 *     - If A->D was 99 initially, it remains 99 because A->A->D adds no value.
 *     - *Knowledge*: "Shortest path A->D using only {A} is 99."
 * 
 *  2. k = 1 (Gate: Nodes A, B)
 *     - Check Path A -> D: 
 *       - Option 1: Direct (Current Best) = 99
 *       - Option 2: Via B = matrix[0][1] + matrix[1][3]
 *     - Suppose matrix[0][1] = 5 and matrix[1][3] = 20.
 *     - New Path = 5 + 20 = 25.
 *     - *Decision*: 25 < 99. Update! matrix[0][3] = 25.
 *     - *Knowledge Update*: "Shortest path A->D using only {A, B} is 25."
 * 
 *  3. k = 2 (Gate: Nodes A, B, C)
 *     - Check Path A -> D:
 *       - Option 1: Via {A, B} = 25 (from previous step)
 *       - Option 2: Via C = matrix[0][2] + matrix[2][3]
 *     - Suppose matrix[0][2] = 10 and matrix[2][3] = 5.
 *     - New Path = 10 + 5 = 15.
 *     - *Decision*: 15 < 25. Update! matrix[0][3] = 15.
 *     - *Knowledge Update*: "Shortest path A->D using only {A, B, C} is 15."
 * 
 *  4. k = 3 (Gate: Nodes A, B, C, D)
 *     - Check Path A -> D:
 *       - Option 1: Via {A, B, C} = 15
 *       - Option 2: Via D = matrix[0][3] + matrix[3][3]
 *     - New Path = 15 + 0 = 15.
 *     - *Decision*: 15 is not greater than 15. No change.
 *     - *Final Knowledge*: "Shortest path A->D using {A,B,C,D} is 15."
 * 
 * ============================================================================
 * 🧲 THE CORE IDEA
 * ============================================================================
 *  The algorithm builds up the solution iteratively:
 *  - After iteration 0, you know all shortest paths that might use vertex 0.
 *  - After iteration 1, you know all shortest paths that might use vertex 0 OR 1.
 *  - After iteration N-1, you know all shortest paths using ANY vertex.
 * 
 *  Because you update the matrix in place, when you calculate for k, the values for 
 *  matrix[i][k] and matrix[k][j] already represent the shortest paths using only 
 *  vertices {0...k-1}. This overlap is why it works without needing a 3D array!
 * ============================================================================
 */

**Complexity:**
    *   Bellman-Ford: Time $O(V \cdot E)$, Space $O(V)$.
    *   Floyd-Warshall: Time $O(V^3)$, Space $O(1)$ auxiliary (modifies input matrix).

```

## 🟢 Section 3: Spanning Trees & Disjoint Set

### 🎯 Solution 9.5: Disjoint Set Union (DSU) & Kruskal's MST
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

class DSU {
    std::vector<int> parent;
    std::vector<int> rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }
    
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                std::swap(root_i, root_j);
            }
            parent[root_j] = root_i;
            if (rank[root_i] == rank[root_j]) rank[root_i]++;
        }
    }
};

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const { return weight < other.weight; }
};

int kruskalMST(int V, std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end());
    DSU dsu(V);
    int mstWeight = 0;
    
    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) { // means not in same set, so add edge to mst
            mstWeight += edge.weight;
            dsu.unite(edge.u, edge.v);
        }
    }
    return mstWeight;
}
```
*   **Complexity:** Time: $O(E \log E + E \cdot \alpha(V))$ (where $\alpha$ is Inverse Ackermann function), Space: $O(V)$.

---

## 🟢 Section 4: Advanced Algorithms

### 🎯 Solution 9.6: Kosaraju's Algorithm (SCC Detection)
*   **Problem:** Find all Strongly Connected Components (SCCs) in a directed graph.
*   **C++ Code:**
```cpp
#include <vector>
#include <stack>

void dfsFillOrder(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::stack<int>& st) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfsFillOrder(v, adj, visited, st);
    }
    st.push(u);
}

void dfsPrint(int u, const std::vector<std::vector<int>>& adjT, std::vector<bool>& visited) {
    visited[u] = true;
    for (int v : adjT[u]) {
        if (!visited[v]) dfsPrint(v, adjT, visited);
    }
}

int countSCCs(int V, const std::vector<std::vector<int>>& adj) {
    std::stack<int> st;
    std::vector<bool> visited(V, false);
    
    // Step 1: Push vertices into stack based on finishing time
    for (int i = 0; i < V; i++) {
        if (!visited[i]) dfsFillOrder(i, adj, visited, st);
    }
    
    // Step 2: Transpose the graph
    std::vector<std::vector<int>> adjT(V);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            adjT[v].push_back(u);
        }
    }
    
    // Step 3: Pop from stack and run DFS on transposed graph
    std::fill(visited.begin(), visited.end(), false);
    int sccCount = 0;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (!visited[u]) {
            sccCount++;
            dfsPrint(u, adjT, visited);
        }
    }
    return sccCount;
}
```
*   **Complexity:** Time: $O(V + E)$, Space: $O(V + E)$ for transposed structure.
