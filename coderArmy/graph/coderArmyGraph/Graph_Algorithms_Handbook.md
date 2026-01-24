# Graph Algorithms Handbook

This handbook covers the most important graph algorithms with their
**concepts, purposes, and C++ implementations**.\
Each algorithm is explained with its intuition, use cases, and
complexity.

------------------------------------------------------------------------

## 1. Breadth First Search (BFS)

**What is BFS?**\
Breadth First Search is a traversal technique where we explore all
neighbors of a node before moving deeper.\
It works level by level.

**What it does?**\
- Finds shortest path in **unweighted graphs**.\
- Useful in problems like shortest path in grid, checking connectivity,
bipartite graph check.

**Time Complexity:** `O(V + E)`\
**Space Complexity:** `O(V)`

``` cpp
void bfs(int start, vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for (auto nei : adj[node]) {
            if (!visited[nei]) {
                visited[nei] = true;
                q.push(nei);
            }
        }
    }
}
```

------------------------------------------------------------------------

## 2. Depth First Search (DFS)

**What is DFS?**\
Depth First Search explores as far as possible along one branch before
backtracking.

**What it does?**\
- Used in cycle detection, connected components, topological sort, SCCs.

**Time Complexity:** `O(V + E)`\
**Space Complexity:** `O(V)` (recursion stack)

``` cpp
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";
    for (auto nei : adj[node]) {
        if (!visited[nei]) {
            dfs(nei, adj, visited);
        }
    }
}
```

------------------------------------------------------------------------

## 3. Topological Sort

**What is Topological Sort?**\
Ordering of nodes in a Directed Acyclic Graph (DAG) such that for every
directed edge `u → v`, `u` comes before `v`.

**What it does?**\
- Used in scheduling tasks, build systems, course prerequisite problems.

**Time Complexity:** `O(V + E)`\
**Space Complexity:** `O(V)`

``` cpp
void topoDFS(int node, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[node] = true;
    for (auto nei : adj[node]) {
        if (!visited[nei]) topoDFS(nei, adj, visited, st);
    }
    st.push(node);
}

vector<int> topologicalSort(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) topoDFS(i, adj, visited, st);
    }
    vector<int> res;
    while (!st.empty()) {
        res.push_back(st.top());
        st.pop();
    }
    return res;
}
```

------------------------------------------------------------------------

## 4. Minimum Spanning Tree (MST)

### 4.1 Kruskal's Algorithm

**What is Kruskal's Algorithm?**\
Kruskal's algorithm builds an MST by sorting edges by weight and picking
them if they don't form a cycle (using Disjoint Set Union).

**What it does?**\
- Finds MST with minimum cost.\
- Greedy algorithm.\
- Uses DSU (Union-Find).

**Time Complexity:** `O(E log E)`\
**Space Complexity:** `O(V)`

``` cpp
struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (rank[x] < rank[y]) swap(x, y);
            parent[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
};

int kruskal(int n, vector<vector<int>>& edges) {
    sort(edges.begin(), edges.end(), [](auto &a, auto &b) { return a[2] < b[2]; });
    DSU dsu(n);
    int mst = 0;
    for (auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            mst += w;
        }
    }
    return mst;
}
```

------------------------------------------------------------------------

### 4.2 Prim's Algorithm

**What is Prim's Algorithm?**\
Prim's algorithm grows the MST from a starting node by always picking
the smallest edge connecting to the tree.

**What it does?**\
- Also finds MST with minimum cost.\
- Greedy approach using Priority Queue (Min Heap).

**Time Complexity:** `O(E log V)`\
**Space Complexity:** `O(V)`

``` cpp
int prims(int n, vector<vector<pair<int,int>>>& adj) {
    vector<bool> inMST(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, 0});
    int mst = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;
        mst += w;
        for (auto [v, wt] : adj[u]) {
            if (!inMST[v]) pq.push({wt, v});
        }
    }
    return mst;
}
```

------------------------------------------------------------------------

## 5. Shortest Path Algorithms

### 5.1 Dijkstra's Algorithm

**What is Dijkstra's Algorithm?**\
Finds shortest path from a source to all nodes in a weighted graph with
**non-negative edges**.

**Time Complexity:** `O(E log V)`\
**Space Complexity:** `O(V)`

``` cpp
vector<int> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int src) {
    vector<int> dist(n, 1e9);
    dist[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

------------------------------------------------------------------------

### 5.2 Bellman-Ford Algorithm

**What is Bellman-Ford Algorithm?**\
Computes shortest path even with **negative edges**, but not with
negative cycles.

**Time Complexity:** `O(V * E)`\
**Space Complexity:** `O(V)`

``` cpp
vector<int> bellmanFord(int n, vector<vector<int>>& edges, int src) {
    vector<int> dist(n, 1e9);
    dist[src] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != 1e9 && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
    return dist;
}
```

------------------------------------------------------------------------

### 5.3 Floyd-Warshall Algorithm

**What is Floyd-Warshall Algorithm?**\
Dynamic Programming algorithm to find shortest paths between **all pairs
of vertices**. Works with negative edges but no negative cycles.

**Time Complexity:** `O(V^3)`\
**Space Complexity:** `O(V^2)`

``` cpp
void floydWarshall(int n, vector<vector<int>>& dist) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != 1e9 && dist[k][j] != 1e9)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
```

------------------------------------------------------------------------

## 6. Max Flow (Ford-Fulkerson)

**What is Ford-Fulkerson Algorithm?**\
Computes maximum flow in a network using augmenting paths.

**What it does?**\
- Solves problems like network flow, bipartite matching.

**Time Complexity:** `O(E * maxFlow)`\
**Space Complexity:** `O(V)`

``` cpp
bool bfsFF(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    int V = rGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[t];
}

int fordFulkerson(vector<vector<int>>& graph, int s, int t) {
    int V = graph.size();
    vector<vector<int>> rGraph = graph;
    vector<int> parent(V);
    int max_flow = 0;

    while (bfsFF(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}
```

------------------------------------------------------------------------

# ✅ Conclusion

-   **BFS, DFS** → Traversals and basic graph exploration.\
-   **Topological Sort** → Ordering tasks in DAGs.\
-   **Kruskal & Prim** → Build MST.\
-   **Dijkstra, Bellman-Ford, Floyd-Warshall** → Shortest paths.\
-   **Ford-Fulkerson** → Maximum flow in networks.

This README is your **quick reference + codebook** for interview prep
and problem solving.
