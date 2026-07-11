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

std::vector<int> dijkstra(int V, const std::vector<std::vector<std::pair<int, int>>>& adj, int src) {
    std::vector<int> dist(V, INT_MAX);
    // min-heap storing {distance, node}
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    
    dist[src] = 0;
    pq.push({0, src});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
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

// 2. Floyd-Warshall (All Pairs Shortest Path)
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
                matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
}
```
*   **Complexity:**
    *   Bellman-Ford: Time $O(V \cdot E)$, Space $O(V)$.
    *   Floyd-Warshall: Time $O(V^3)$, Space $O(1)$ auxiliary (modifies input matrix).

---

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
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
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
