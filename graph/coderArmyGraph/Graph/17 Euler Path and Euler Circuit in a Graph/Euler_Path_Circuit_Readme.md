# Euler Path and Euler Circuit

## 📌 Introduction
In this lecture, we study **Euler Paths** and **Euler Circuits** in graphs.  
These concepts are based on traversing **all edges of a graph exactly once**.

---

## 🧩 Problem Link
- [Euler Path](https://www.geeksforgeeks.org/problem...)

---

## 📖 Concepts

### 🔹 Euler Path
- A path that visits **every edge exactly once**.  
- **Vertices can repeat**, but **edges cannot**.  
- **Condition:** Graph has **0 or 2 vertices of odd degree**.

### 🔹 Euler Circuit
- A cycle that visits **every edge exactly once** and starts and ends at the **same vertex**.  
- **Condition:** Graph has **0 vertices of odd degree**.  
- Also, the graph must be **connected**.

---

## ✅ Conditions for Existence

1. **Euler Path Exists if:**  
   - Graph is connected, and  
   - Exactly **0 or 2 vertices** have odd degree.  

2. **Euler Circuit Exists if:**  
   - Graph is connected, and  
   - **All vertices have even degree**.  

---

## 💻 C++ Code Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // Function to check degree of vertices
    void isEulerian() {
        int odd = 0;
        for (int i = 0; i < V; i++) {
            if (adj[i].size() % 2 != 0)
                odd++;
        }

        if (odd == 0) {
            cout << "Graph has an Euler Circuit" << endl;
        } else if (odd == 2) {
            cout << "Graph has an Euler Path" << endl;
        } else {
            cout << "Graph is not Eulerian" << endl;
        }
    }
};

int main() {
    int V, E;
    cin >> V >> E;
    Graph g(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.isEulerian();
    return 0;
}

⏱️ Time & Space Complexity

Time Complexity: O(V + E)

Space Complexity: O(V + E)

🌍 Real-Life Applications

Postman Route Problem (traversing all streets without repeating edges).

DNA Sequencing in computational biology.

Network Routing problems.

📌 Last Note

Euler Path → uses every edge once but may start and end at different vertices.

Euler Circuit → uses every edge once and must start and end at the same vertex.

Always check vertex degrees to quickly determine existence.