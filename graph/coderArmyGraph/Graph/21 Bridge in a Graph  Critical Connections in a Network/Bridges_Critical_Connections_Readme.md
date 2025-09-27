# Bridge in a Graph | Critical Connections in a Network

## 📌 Problem Link
- [Critical Connections in a Network - LeetCode](https://leetcode.com/problems/critical-connections-in-a-network/)

---

## 📖 Problem Statement
Given a **connected network** of `n` servers labeled from `0` to `n-1` and a list of **connections**,  
find all **critical connections** (bridges) in the network.  
- A **critical connection** is an edge that, if removed, will **increase the number of connected components**.  

---

## 🧠 Key Concepts
- This problem is about finding **bridges in an undirected graph**.  
- A **bridge** is an edge `(u, v)` such that removing it **disconnects** the graph.  
- Use **Tarjan’s Algorithm** (DFS-based) to efficiently find all bridges.  

### 🔹 Tarjan’s Algorithm Idea
1. Use **DFS traversal** on the graph.  
2. Track:
   - `disc[u]` → Discovery time of vertex `u`.  
   - `low[u]` → Earliest visited vertex reachable from subtree rooted with `u`.  
3. For each edge `(u, v)`:
   - If `low[v] > disc[u]`, then `(u, v)` is a **bridge**.  
4. Maintain **parent** information to avoid considering the edge to parent as a back-edge.  

---

## 💻 C++ Code Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
    int time;
    void dfs(int u, int parent, vector<vector<int>>& adj, vector<int>& disc, vector<int>& low, vector<vector<int>>& bridges) {
        disc[u] = low[u] = ++time;
        for (int v : adj[u]) {
            if (v == parent) continue;
            if (disc[v] == -1) {
                dfs(v, u, adj, disc, low, bridges);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for (auto& edge : connections) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        vector<int> disc(n, -1), low(n, -1);
        vector<vector<int>> bridges;
        time = 0;

        for (int i = 0; i < n; i++) {
            if (disc[i] == -1)
                dfs(i, -1, adj, disc, low, bridges);
        }

        return bridges;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> connections(m, vector<int>(2));
    for(int i = 0; i < m; i++) cin >> connections[i][0] >> connections[i][1];

    Solution sol;
    vector<vector<int>> res = sol.criticalConnections(n, connections);

    cout << "Critical Connections (Bridges):\n";
    for(auto &e : res) cout << e[0] << " - " << e[1] << endl;
}

⏱️ Time & Space Complexity

Time Complexity: O(V + E) → DFS visits every vertex and edge once.

Space Complexity: O(V + E) → Adjacency list + recursion stack + arrays.

🌍 Real-Life Applications

Detecting critical links in computer networks.

Road or power grid resilience analysis.

Social network analysis for weak points.

📌 Last Note

Bridges are edges that are critical for connectivity.

Tarjan’s Algorithm helps find all such edges in linear time.

Always maintain discovery time and low values while performing DFS.