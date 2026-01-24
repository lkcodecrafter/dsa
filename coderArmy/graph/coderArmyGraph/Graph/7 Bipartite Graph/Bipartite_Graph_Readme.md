# Bipartite Graph

## 📌 Introduction
A **Bipartite Graph** is a graph whose vertices can be divided into two disjoint sets **U** and **V** such that every edge connects a vertex in U to a vertex in V.  
In simpler terms, no two vertices within the same set are adjacent.

---

## 🔹 Method 1 - BFS Approach

We use **Breadth First Search (BFS)** to check if the graph can be colored using two colors (say 0 and 1) without any two adjacent nodes having the same color.

### Algorithm Steps:
1. Assign a color (0/1) to the starting node.
2. Traverse using BFS.
3. For each adjacent node:
   - If not colored → assign opposite color of parent.
   - If already colored → check if it matches parent’s color. If yes → Not Bipartite.

### C++ Code (BFS)
```cpp
#include <bits/stdc++.h>
using namespace std;

bool isBipartiteBFS(int V, vector<int> adj[]) {
    vector<int> color(V, -1);
    
    for(int start = 0; start < V; start++) {
        if(color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;
            
            while(!q.empty()) {
                int node = q.front();
                q.pop();
                
                for(auto neigh : adj[node]) {
                    if(color[neigh] == -1) {
                        color[neigh] = 1 - color[node];
                        q.push(neigh);
                    } else if(color[neigh] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<int> adj[V];
    
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    if(isBipartiteBFS(V, adj)) cout << "Graph is Bipartite\n";
    else cout << "Graph is NOT Bipartite\n";
}
```

⏱ **Time Complexity:** O(V + E)  
💾 **Space Complexity:** O(V)

---

## 🔹 Method 2 - DFS Approach

We can also check bipartiteness using **Depth First Search (DFS)** by trying to assign colors recursively.

### C++ Code (DFS)
```cpp
#include <bits/stdc++.h>
using namespace std;

bool dfs(int node, int col, vector<int> &color, vector<int> adj[]) {
    color[node] = col;
    
    for(auto neigh : adj[node]) {
        if(color[neigh] == -1) {
            if(!dfs(neigh, 1 - col, color, adj))
                return false;
        } else if(color[neigh] == col) {
            return false;
        }
    }
    return true;
}

bool isBipartiteDFS(int V, vector<int> adj[]) {
    vector<int> color(V, -1);
    
    for(int i = 0; i < V; i++) {
        if(color[i] == -1) {
            if(!dfs(i, 0, color, adj))
                return false;
        }
    }
    return true;
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<int> adj[V];
    
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    if(isBipartiteDFS(V, adj)) cout << "Graph is Bipartite\n";
    else cout << "Graph is NOT Bipartite\n";
}
```

⏱ **Time Complexity:** O(V + E)  
💾 **Space Complexity:** O(V) + O(Depth of recursion)

---

## 🎯 Real Life Applications of Bipartite Graphs

1. **Job Assignment Problem** → Workers and Jobs.
2. **Network Flow Problems** → Matching students to colleges.
3. **Social Networks** → Connecting users to interests/groups.
4. **Scheduling Problems**.

---

## 📝 Last Note
- A graph is **Bipartite if and only if it has no odd-length cycle**.
- BFS and DFS both can be used, depending on the situation.
