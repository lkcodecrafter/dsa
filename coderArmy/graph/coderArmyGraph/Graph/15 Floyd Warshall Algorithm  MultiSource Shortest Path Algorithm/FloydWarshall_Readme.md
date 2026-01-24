# Floyd Warshall Algorithm

## 📌 Introduction
In this lecture, we explore the **Floyd-Warshall Algorithm**, a dynamic programming approach to solve the **All-Pairs Shortest Path (APSP)** problem.  
It works on both **directed and undirected graphs** and can handle **negative edge weights** (but not negative weight cycles).

---

## 🎯 Problem Statement
**Problem Link:** [Floyd Warshall Algorithm](https://www.geeksforgeeks.org/problem...)  

Given a weighted graph, find the shortest path distance between every pair of vertices.

---

## 🛠️ Approach (Floyd-Warshall)

1. Represent the graph using an **adjacency matrix** `dist[][]`.  
   - `dist[i][j] = weight(i, j)` if edge exists.  
   - `dist[i][i] = 0`.  
   - `dist[i][j] = INF` if no direct edge.

2. Use **Dynamic Programming Transition**:  

for k = 0 to V-1:
for i = 0 to V-1:
for j = 0 to V-1:
if dist[i][k] + dist[k][j] < dist[i][j]:
dist[i][j] = dist[i][k] + dist[k][j]


3. After the process, `dist[i][j]` contains the shortest path distance from vertex `i` to `j`.

---

## 💻 C++ Code Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

void floydWarshall(vector<vector<int>>& dist, int V) {
 for (int k = 0; k < V; k++) {
     for (int i = 0; i < V; i++) {
         for (int j = 0; j < V; j++) {
             if (dist[i][k] < INF && dist[k][j] < INF)
                 dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
         }
     }
 }
}

int main() {
 int V, E;
 cin >> V >> E;

 vector<vector<int>> dist(V, vector<int>(V, INF));

 for (int i = 0; i < V; i++)
     dist[i][i] = 0;

 for (int i = 0; i < E; i++) {
     int u, v, w;
     cin >> u >> v >> w;
     dist[u][v] = w;
 }

 floydWarshall(dist, V);

 cout << "All Pairs Shortest Paths:\n";
 for (int i = 0; i < V; i++) {
     for (int j = 0; j < V; j++) {
         if (dist[i][j] == INF)
             cout << "INF ";
         else
             cout << dist[i][j] << " ";
     }
     cout << endl;
 }

 return 0;
}

⏱️ Time & Space Complexity

Time Complexity: O(V^3)

Space Complexity: O(V^2)

⚖️ When to Use

✅ Dijkstra: Best when source is single and graph has no negative weights.

✅ Floyd-Warshall: Best when we need all-pairs shortest paths.

❌ Bellman-Ford: Handles negative edges but slower (O(V*E)).

🚨 Why Not Bellman-Ford?

Bellman-Ford is good for single-source shortest path with negative edges.

But for all-pairs shortest path, it is too slow.

Floyd-Warshall is much more efficient for APSP.

📝 Homework

Practice Floyd-Warshall on different test cases.

Modify it to also detect negative cycles:

If dist[i][i] < 0 after running the algorithm → Negative cycle exists.

🌍 Real-World Applications

Routing protocols

Traffic navigation systems

Network optimization problems

📌 Last Note

Use Floyd-Warshall for dense graphs and APSP.

Use Dijkstra for sparse graphs with non-negative weights.

Always check for negative cycles before using the result.