# Shortest Path in Directed Acyclic Graph (DAG)

## 📌 Introduction
The **Shortest Path in a Directed Acyclic Graph (DAG)** can be efficiently found using **Topological Sorting**.  
Since the graph is acyclic, we don’t need to worry about negative cycles. This is faster than Dijkstra’s when the graph is a DAG.

---

## 🚀 Approach
1. Perform **Topological Sort** of the DAG.
2. Initialize distance array `dist[]` with infinity, except the **source node = 0**.
3. Relax all adjacent edges of each node in **topological order**.
4. After processing, `dist[]` contains the shortest distances from the source.

---

## 🧩 Example
```
Vertices = 6, Edges = 7
Edges: 
0 -> 1 (2)
0 -> 4 (1)
1 -> 2 (3)
4 -> 2 (2)
4 -> 5 (4)
2 -> 3 (6)
5 -> 3 (1)

Source = 0
```
**Output:**  
Shortest distances from node `0`:  
```
Node 0 -> 0
Node 1 -> 2
Node 2 -> 3
Node 3 -> 6
Node 4 -> 1
Node 5 -> 5
```

---

## 📜 C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

void topoSort(int node, vector<pair<int,int>> adj[], vector<int> &vis, stack<int> &st) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        int v = it.first;
        if (!vis[v]) {
            topoSort(v, adj, vis, st);
        }
    }
    st.push(node);
}

void shortestPathDAG(int V, vector<pair<int,int>> adj[], int src) {
    vector<int> vis(V, 0);
    stack<int> st;

    // Step 1: Topological Sort
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            topoSort(i, adj, vis, st);
        }
    }

    // Step 2: Initialize distances
    vector<int> dist(V, 1e9);
    dist[src] = 0;

    // Step 3: Relax edges in topo order
    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (dist[node] != 1e9) {
            for (auto it : adj[node]) {
                int v = it.first;
                int wt = it.second;
                if (dist[node] + wt < dist[v]) {
                    dist[v] = dist[node] + wt;
                }
            }
        }
    }

    // Print result
    cout << "Shortest distances from source " << src << ":
";
    for (int i = 0; i < V; i++) {
        if (dist[i] == 1e9)
            cout << "INF ";
        else
            cout << dist[i] << " ";
    }
    cout << endl;
}

int main() {
    int V = 6;
    vector<pair<int,int>> adj[V];

    adj[0].push_back({1, 2});
    adj[0].push_back({4, 1});
    adj[1].push_back({2, 3});
    adj[4].push_back({2, 2});
    adj[4].push_back({5, 4});
    adj[2].push_back({3, 6});
    adj[5].push_back({3, 1});

    int src = 0;
    shortestPathDAG(V, adj, src);
    return 0;
}
```

---

## ⏳ Complexity Analysis
- **Topological Sort:** `O(V + E)`  
- **Relaxation of edges:** `O(V + E)`  
- **Total:** `O(V + E)`  
- **Space Complexity:** `O(V + E)` for adjacency list and recursion stack.

---

## 📌 Homework
- Try running the code with different graphs and sources.  
- Implement using **BFS-based Kahn’s Algorithm** instead of DFS-based topological sort.
