
# Strongly Connected Components (SCC) | Kosaraju & Tarjan Algorithms

## 📌 Problem Links
1. [Kosaraju's Algorithm - GFG](https://www.geeksforgeeks.org/problem...)  
2. [Tarjan's Algorithm - GFG](https://www.geeksforgeeks.org/problem...)

---

## 📖 Problem Statement
A **Strongly Connected Component (SCC)** of a directed graph is a maximal set of vertices such that **every vertex is reachable from every other vertex** in the set.

**Goal:** Find all SCCs in a directed graph.

---

## 🧠 Key Concepts
- **Kosaraju’s Algorithm:** Uses **2 DFS passes**.
  1. First DFS → record **finish times** (stack).  
  2. Reverse all edges in the graph.  
  3. Second DFS using stack order → each DFS tree is an SCC.

- **Tarjan’s Algorithm:** Uses **DFS + Low-link values**.  
  1. Keep **discovery time** `disc[u]` and **low value** `low[u]`.  
  2. Maintain a **stack** of visited vertices.  
  3. When `low[u] == disc[u]` → vertices in stack up to `u` form an SCC.

---

## 💻 C++ Code Implementation

### Kosaraju’s Algorithm

```cpp
#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

    void dfs(int u, vector<bool>& visited, stack<int>& st) {
        visited[u] = true;
        for(int v : adj[u])
            if(!visited[v])
                dfs(v, visited, st);
        st.push(u);
    }

    void dfsUtil(int u, vector<bool>& visited, vector<int>& component) {
        visited[u] = true;
        component.push_back(u);
        for(int v : adj[u])
            if(!visited[v])
                dfsUtil(v, visited, component);
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    Graph getTranspose() {
        Graph gT(V);
        for(int u = 0; u < V; u++)
            for(int v : adj[u])
                gT.addEdge(v, u);
        return gT;
    }

    void printSCCs() {
        stack<int> st;
        vector<bool> visited(V, false);

        for(int i = 0; i < V; i++)
            if(!visited[i])
                dfs(i, visited, st);

        Graph gT = getTranspose();
        fill(visited.begin(), visited.end(), false);

        while(!st.empty()) {
            int u = st.top(); st.pop();
            if(!visited[u]) {
                vector<int> component;
                gT.dfsUtil(u, visited, component);
                cout << "SCC: ";
                for(int v : component) cout << v << " ";
                cout << endl;
            }
        }
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

    g.printSCCs();
    return 0;
}

Tarjan’s Algorithm
#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
    int V, time;
    vector<vector<int>> adj;
    vector<int> disc, low;
    stack<int> st;
    vector<bool> inStack;

    void dfs(int u) {
        disc[u] = low[u] = ++time;
        st.push(u); inStack[u] = true;

        for(int v : adj[u]) {
            if(disc[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if(inStack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        if(low[u] == disc[u]) {
            cout << "SCC: ";
            while(true) {
                int v = st.top(); st.pop(); inStack[v] = false;
                cout << v << " ";
                if(v == u) break;
            }
            cout << endl;
        }
    }

public:
    TarjanSCC(int V) {
        this->V = V;
        adj.resize(V);
        disc.assign(V, -1);
        low.assign(V, -1);
        inStack.assign(V, false);
        time = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void findSCCs() {
        for(int i = 0; i < V; i++)
            if(disc[i] == -1)
                dfs(i);
    }
};

int main() {
    int V, E;
    cin >> V >> E;
    TarjanSCC g(V);
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.findSCCs();
    return 0;
}

⏱️ Time & Space Complexity

Time Complexity: O(V + E) → Both Kosaraju and Tarjan use DFS.

Space Complexity: O(V + E) → adjacency list + recursion stack + auxiliary arrays.

🌍 Real-Life Applications

Detecting strongly connected components in social networks.

Web crawling: finding clusters of interconnected web pages.

Circuit analysis and dependency resolution.

📌 Last Note

Kosaraju: 2-pass DFS + graph transpose.

Tarjan: Single DFS using low-link values.

Tarjan is more efficient for online SCC detection.

SCC detection is fundamental in graph analysis and optimization.