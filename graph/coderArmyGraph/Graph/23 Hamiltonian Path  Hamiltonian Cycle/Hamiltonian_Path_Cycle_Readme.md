# Hamiltonian Path | Hamiltonian Cycle

## 📌 Problem Link
- [Hamiltonian Path - GFG](https://www.geeksforgeeks.org/problem...)

---

## 📖 Problem Statement
- **Hamiltonian Path:** A path in a graph that visits **each vertex exactly once**.  
- **Hamiltonian Cycle:** A Hamiltonian Path that is a **cycle**, i.e., starts and ends at the same vertex.

**Goal:** Determine if a Hamiltonian Path or Cycle exists in a given graph.

---

## 🧠 Key Concepts
- **Hamiltonian Problems** are NP-Complete.  
- No simple formula exists; generally solved using **Backtracking**.  
- **Approach:**
  1. Start at any vertex.  
  2. Recursively explore unvisited neighbors.  
  3. If all vertices are visited:
     - For Path → success.  
     - For Cycle → also check if last vertex connects to the first.  
  4. Backtrack if path fails.

---

## 💻 C++ Code Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

    bool hamUtil(int pos, vector<int>& path, vector<bool>& visited) {
        if(pos == V) {
            // Check for cycle
            if(find(adj[path[pos-1]].begin(), adj[path[pos-1]].end(), path[0]) != adj[path[pos-1]].end())
                return true; // Hamiltonian Cycle
            else
                return true; // Hamiltonian Path exists
        }

        for(int v : adj[path[pos-1]]) {
            if(!visited[v]) {
                path[pos] = v;
                visited[v] = true;
                if(hamUtil(pos+1, path, visited))
                    return true;
                visited[v] = false; // Backtrack
            }
        }
        return false;
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    bool isHamiltonianPath() {
        vector<int> path(V, -1);
        vector<bool> visited(V, false);

        for(int start = 0; start < V; start++) {
            path[0] = start;
            visited[start] = true;
            if(hamUtil(1, path, visited))
                return true;
            visited[start] = false;
        }
        return false;
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

    if(g.isHamiltonianPath())
        cout << "Hamiltonian Path/Cycle exists\n";
    else
        cout << "No Hamiltonian Path/Cycle\n";
}

⏱️ Time & Space Complexity

Time Complexity: O(V!) → Explore all permutations of vertices (exponential).

Space Complexity: O(V + E) → adjacency list + recursion stack + path array.

🌍 Real-Life Applications

Traveling Salesman Problem (TSP) in logistics.

Circuit design and scheduling problems.

DNA sequencing (Hamiltonian path in graph of fragments).

📌 Last Note

Hamiltonian problems are NP-Complete, so backtracking works for small graphs.

Always check:

All vertices visited → Path exists.

Last vertex connects to start → Cycle exists.

No greedy method guarantees solution for general graphs.