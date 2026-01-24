# Shortest Path in Undirected Graph

This README explains **Shortest Path in Undirected Graph** using **BFS** and **DFS** methods with C++ code, step-by-step approach, and complexity analysis.

---

## 📌 Problems
1. [Shortest Path in Undirected Graph - GFG](https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1)  
2. [Shortest Path in Undirected Graph - Naukri Code360](https://www.naukri.com/code360/problems/shortest-path-in-an-undirected-graph_8416383)  

---

## 🧑‍💻 Problem 1: BFS Method - Shortest Path

### 🌟 Intuition
- BFS explores nodes **level by level**.  
- In an **unweighted graph**, BFS guarantees shortest distance.  

### 📝 Steps
1. Use a queue for BFS traversal.  
2. Maintain `dist[]` array initialized to `INT_MAX`.  
3. Start BFS from the source node → `dist[src] = 0`.  
4. For each neighbor, update distance if `dist[u] + 1 < dist[v]`.  
5. Continue until all nodes are visited.  

### C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> shortestPathBFS(int V, vector<int> adj[], int src) {
    vector<int> dist(V, INT_MAX);
    queue<int> q;
    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main() {
    int V = 6;
    vector<int> adj[V];
    adj[0] = {1, 2};
    adj[1] = {0, 3};
    adj[2] = {0, 3, 4};
    adj[3] = {1, 2, 5};
    adj[4] = {2, 5};
    adj[5] = {3, 4};

    vector<int> dist = shortestPathBFS(V, adj, 0);
    for (int d : dist) cout << d << " ";
    return 0;
}
```

### ⏳ Complexity
- **Time**: `O(V + E)`  
- **Space**: `O(V + E)`  

---

## 🧑‍💻 Problem 2: DFS Method - Shortest Path

### 🌟 Intuition
- DFS explores one path fully before backtracking.  
- Not optimal like BFS, but can still find shortest path using recursion with backtracking.  

### 📝 Steps
1. Maintain `dist[]` initialized to `INT_MAX`.  
2. Use recursive DFS to explore neighbors.  
3. If a shorter path is found → update `dist[v]`.  
4. Backtrack to explore alternate paths.  

### C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

void dfs(int u, vector<int> adj[], vector<int>& dist) {
    for (int v : adj[u]) {
        if (dist[u] + 1 < dist[v]) {
            dist[v] = dist[u] + 1;
            dfs(v, adj, dist);
        }
    }
}

vector<int> shortestPathDFS(int V, vector<int> adj[], int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    dfs(src, adj, dist);
    return dist;
}

int main() {
    int V = 6;
    vector<int> adj[V];
    adj[0] = {1, 2};
    adj[1] = {0, 3};
    adj[2] = {0, 3, 4};
    adj[3] = {1, 2, 5};
    adj[4] = {2, 5};
    adj[5] = {3, 4};

    vector<int> dist = shortestPathDFS(V, adj, 0);
    for (int d : dist) cout << d << " ";
    return 0;
}
```

### ⏳ Complexity
- **Time**: `O(V + E)` (but slower in practice due to recursion/backtracking).  
- **Space**: `O(V + E)` (recursion stack).  

---

## 📝 Last Note
- **BFS** is the best method for shortest path in **unweighted graphs**.  
- **DFS** works but is less efficient.  
- Both methods build strong intuition for graph traversal.  

