# Articulation Point in a Graph | Tarjan's Algorithm

## 📌 Problem Link
- [Articulation Point - GFG](https://www.geeksforgeeks.org/problem...)

---

## 📖 Problem Statement
An **articulation point** (or cut vertex) in a connected undirected graph is a vertex which, when removed along with its edges, **increases the number of connected components** of the graph.

- **Goal:** Find all articulation points in the given graph.

---

## 🧠 Key Concepts
- Uses **Tarjan's DFS Algorithm**.  
- Maintain for each vertex:
  1. `disc[u]` → Discovery time during DFS.  
  2. `low[u]` → Lowest discovery time reachable from vertex `u` including back edges.  

- **Articulation Point Rules:**
  1. Root of DFS tree is an articulation point if it has **two or more children**.  
  2. Any other vertex `u` is an articulation point if there exists a child `v` such that `low[v] >= disc[u]`.

---

## 💻 C++ Code Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

    void APUtil(int u, vector<bool>& visited, vector<int>& disc, vector<int>& low,
                vector<int>& parent, vector<bool>& isAP, int &time) {
        visited[u] = true;
        disc[u] = low[u] = ++time;
        int children = 0;

        for(int v : adj[u]) {
            if(!visited[v]) {
                children++;
                parent[v] = u;
                APUtil(v, visited, disc, low, parent, isAP, time);

                low[u] = min(low[u], low[v]);

                // Rule 1: u is root and has two or more children
                if(parent[u] == -1 && children > 1)
                    isAP[u] = true;

                // Rule 2: u is not root and low[v] >= disc[u]
                if(parent[u] != -1 && low[v] >= disc[u])
                    isAP[u] = true;
            }
            else if(v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void findArticulationPoints() {
        vector<bool> visited(V, false);
        vector<int> disc(V, -1), low(V, -1), parent(V, -1);
        vector<bool> isAP(V, false);
        int time = 0;

        for(int i = 0; i < V; i++) {
            if(!visited[i])
                APUtil(i, visited, disc, low, parent, isAP, time);
        }

        cout << "Articulation Points:\n";
        for(int i = 0; i < V; i++) {
            if(isAP[i]) cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
    int V, E;
    cin >> V >> E;
    Graph g(V);
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.findArticulationPoints();
    return 0;
}

⏱️ Time & Space Complexity

Time Complexity: O(V + E) → DFS visits all vertices and edges once.

Space Complexity: O(V + E) → adjacency list + recursion stack + auxiliary arrays.

🌍 Real-Life Applications

Network design: identifying critical nodes in a computer network.

Social networks: finding influential people whose removal disconnects communities.

Road/transport networks: detecting critical junctions.

📌 Last Note

Articulation points are vertices critical for connectivity.

Use Tarjan’s DFS for efficient linear-time detection.

Always track discovery time, low values, and DFS tree structure.
