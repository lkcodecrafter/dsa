# Shortest Path in Weighted Undirected Graph

## 📌 Introduction
In this lecture, we discuss the **Shortest Path in a Weighted Undirected Graph** problem.  
We explore graph representation, apply **Dijkstra's Algorithm**, analyze **time and space complexity**, and solve the problem with C++ implementation.  

---

## 🎯 Problem Statement
**Problem Link:** [Shortest Path in Weighted Undirected Graph](https://www.geeksforgeeks.org/problem...)  

Given a weighted undirected graph and a source node, find the shortest path from the source to every other node.

---

## 🛠️ Approach

### Step 1: Represent the Graph
- Use an **adjacency list** to store `(neighbor, weight)` pairs for each node.

### Step 2: Apply Dijkstra’s Algorithm
- Initialize a **distance array** with infinity.
- Use a **min-heap (priority queue)** to always pick the node with the smallest current distance.
- Update distances of neighboring nodes if a shorter path is found.

### Step 3: Return Shortest Path Distances
- After processing all nodes, the distance array will contain the shortest paths.

---

## ⏱️ Time & Space Complexity

- **Time Complexity**:  
  - Using adjacency list and min-heap: **O((V + E) log V)**  
  - `V = number of vertices`, `E = number of edges`

- **Space Complexity**:  
  - **O(V + E)** (for adjacency list and distance array)

---

## 💻 C++ Code Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int src) {
    // Distance array
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Min-heap: {distance, node}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if (d > dist[node]) continue; // Skip outdated entry

        for (auto [nbr, wt] : adj[node]) {
            if (dist[node] + wt < dist[nbr]) {
                dist[nbr] = dist[node] + wt;
                pq.push({dist[nbr], nbr});
            }
        }
    }

    return dist;
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<pair<int,int>>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Undirected graph
    }

    int src;
    cin >> src;

    vector<int> result = dijkstra(V, adj, src);

    cout << "Shortest distances from source " << src << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "Node " << i << " -> " << result[i] << "\n";
    }

    return 0;
}

🌍 Real-World Example

Imagine a road network:

Cities as nodes

Roads as edges with weights (distances/time)

Dijkstra’s algorithm helps find the shortest travel path from one city to all others.

📝 Last Note

Always use priority queue (min-heap) for efficiency.

Works with positive edge weights only.

For graphs with negative weights, use Bellman-Ford Algorithm instead.