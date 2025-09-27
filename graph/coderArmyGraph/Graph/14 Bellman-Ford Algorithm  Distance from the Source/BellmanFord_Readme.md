// https://www.naukri.com/code360/library/bellman-ford-algorithm
# Distance from the Source (Bellman-Ford Algorithm)

## 📌 Introduction
In this lecture, we study the **Bellman-Ford Algorithm** for finding the shortest path in graphs that may contain **negative edge weights**.  
Unlike Dijkstra’s Algorithm, Bellman-Ford can handle negative weights and is useful for detecting **negative weight cycles**.

---

## 🎯 Problem Statement
**Problem Link:** [Distance from the Source](https://www.geeksforgeeks.org/problem...)  

Given a weighted graph (with possible negative edges) and a source node, find the shortest path distances from the source to all other nodes.

---

## 🛠️ Approach (Bellman-Ford)

1. **Initialization**  
   - Distance array with `∞` values, except source = 0.

2. **Relax All Edges (V-1 times)**  
   - For each edge `(u, v, w)`,  
     if `dist[u] + w < dist[v]`, update `dist[v]`.

3. **Check for Negative Weight Cycle**  
   - Run one more iteration over edges.  
   - If distance reduces further, **negative weight cycle exists**.

---

## ⏱️ Time & Space Complexity
- **Time Complexity:** `O(V * E)`  
  - V = number of vertices  
  - E = number of edges  

- **Space Complexity:** `O(V)` (for distance array)

---

## 💻 C++ Code Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

vector<int> bellmanFord(int V, int src, vector<Edge> &edges) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V-1; i++) {
        for (auto &edge : edges) {
            if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.w < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.w;
            }
        }
    }

    // Check for negative weight cycles
    for (auto &edge : edges) {
        if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.w < dist[edge.v]) {
            cout << "Graph contains negative weight cycle\n";
            return {};
        }
    }

    return dist;
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<Edge> edges(E);

    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int src;
    cin >> src;

    vector<int> result = bellmanFord(V, src, edges);

    if (!result.empty()) {
        cout << "Shortest distances from source " << src << ":\n";
        for (int i = 0; i < V; i++) {
            cout << "Node " << i << " -> " << result[i] << "\n";
        }
    }

    return 0;
}

⚖️ Bellman-Ford vs Dijkstra

✅ Works with negative weights.

❌ Slower than Dijkstra (O(VE) vs O((V+E) log V)).

🚨 Can detect negative weight cycles.

🌍 Real-World Example

Bellman-Ford is used in network routing protocols (e.g., RIP – Routing Information Protocol), where negative weights can model delays or penalties.

📝 Last Note

Use Bellman-Ford when the graph has negative weights.

If the graph has no negative weights, prefer Dijkstra’s Algorithm for efficiency.

Always check for negative weight cycles to avoid infinite shortest paths.