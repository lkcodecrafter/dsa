# Dijkstra's Algorithm

## 📌 Introduction
Dijkstra’s Algorithm is a **single-source shortest path algorithm** used to find the minimum distance from a source node to all other nodes in a **weighted graph with non-negative weights**.

---

## 🚀 Method 1 - Simple Implementation (O(V²))

### Approach
1. Use a distance array initialized with infinity, except `dist[src] = 0`.
2. Pick the **unvisited node with the smallest distance**.
3. Relax all its adjacent edges.
4. Repeat until all nodes are processed.

### C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<pair<int,int>>> adj(V);
    
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // undirected
    }
    
    int src; 
    cin >> src;

    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);
    dist[src] = 0;

    for (int count = 0; count < V-1; count++) {
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        visited[u] = true;
        for (auto it : adj[u]) {
            int v = it.first, w = it.second;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    cout << "Shortest distances from source " << src << ":
";
    for (int i = 0; i < V; i++) {
        cout << i << " -> " << dist[i] << endl;
    }
    return 0;
}
```

### Complexity
- Time: **O(V²)**
- Space: **O(V + E)**

---

## 🚀 Method 2 - Using Min-Heap (Priority Queue) (O(E log V))

### Approach
1. Use a **priority queue (min-heap)** to always pick the smallest distance node.
2. Relax its adjacent edges.
3. Push updated distances into the heap.

### C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

void dijkstra(int V, vector<pair<int,int>> adj[], int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto it : adj[u]) {
            int v = it.first, w = it.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest distances from source " << src << ":
";
    for (int i = 0; i < V; i++) {
        cout << i << " -> " << dist[i] << endl;
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<pair<int,int>> adj[V];

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // undirected
    }

    int src;
    cin >> src;
    dijkstra(V, adj, src);
    return 0;
}
```

### Complexity
- Time: **O(E log V)**
- Space: **O(V + E)**

---

## 📌 Key Notes
- Works only for **non-negative weights**.
- Faster with priority queue compared to naive implementation.
- Very useful in **network routing, maps, and GPS systems**.

---

## 🏡 Homework
- Solve **LeetCode 743: Network Delay Time**
- Solve **GFG: Dijkstra’s Algorithm problem**
