# Prim’s Algorithm (Minimum Spanning Tree)

## 📌 Problem Link
- [Prim’s Algorithm - GFG](https://www.geeksforgeeks.org/problem...)

---

## 📖 Introduction
A **Minimum Spanning Tree (MST)** of a graph is a subset of edges that:  
1. Connects all vertices in the graph.  
2. Has no cycles.  
3. Has **minimum total weight** among all spanning trees.  

---

## 🌍 Real-World Applications
- Designing **network cables** to connect computers with minimum cost.  
- Road construction to connect cities optimally.  
- Electrical grid connections to minimize cost.  

---

## 🛠️ Prim’s Algorithm Idea
1. Start from any **vertex**.  
2. Select the **minimum weight edge** connecting the MST to a vertex **outside the MST**.  
3. Add the vertex and edge to MST.  
4. Repeat until all vertices are included.  

- Use **priority queue** for efficient selection of the minimum weight edge.  

---

## 💡 Steps with Example
- Begin with vertex `0`.  
- Pick the edge with **minimum weight** from `0` to other vertices.  
- Add that vertex to MST.  
- Continue choosing minimum edges connecting **MST to non-MST vertices**.  
- Repeat until all vertices are included.  

---

## 💻 C++ Code Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

int primMST(vector<vector<pair<int,int>>>& adj, int V) {
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    key[0] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, 0}); // {weight, vertex}

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (auto [v, w] : adj[u]) {
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    int mst_weight = 0;
    for (int i = 0; i < V; i++) mst_weight += key[i];
    return mst_weight;
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

    cout << "Weight of Minimum Spanning Tree: " << primMST(adj, V) << endl;
    return 0;
}

⏱️ Time & Space Complexity

Time Complexity: O(E log V) using priority queue

Space Complexity: O(V + E) for adjacency list + O(V) for key & parent arrays

📌 Last Note

Prim’s Algorithm grows the MST vertex by vertex, always choosing the minimum weight edge connecting MST to non-MST vertices.

Works for connected, undirected, weighted graphs.

For dense graphs, Prim’s is more efficient with adjacency matrix representation.

