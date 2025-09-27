# Kruskal’s Algorithm (Minimum Spanning Tree)

## 📌 Problem Link
- [Kruskal’s Algorithm - GFG](https://www.geeksforgeeks.org/problem...)

---

## 📖 Introduction
**Kruskal’s Algorithm** is a **greedy algorithm** to find the **Minimum Spanning Tree (MST)** of a graph.  
It works by picking edges in increasing order of weight and ensuring **no cycles** are formed.

---

## 🧠 Key Idea
1. Sort all edges in **non-decreasing order** of weight.  
2. Initialize **disjoint sets** for all vertices.  
3. Pick the smallest edge.  
   - If it connects **different sets**, include it in MST.  
   - Otherwise, skip (would form a cycle).  
4. Repeat until MST contains **V-1 edges**.  

---

## 🔹 Understanding Disjoint Set
- **Operations used in Kruskal:**
  1. **Find Parent:** Determine which set a vertex belongs to.  
  2. **Union by Rank:** Merge two sets efficiently.  
  3. **Path Compression:** Flatten tree structure during find to optimize.  

- **Why merge smaller set with bigger set?**
  - To minimize the **height of the tree** for efficient future finds.  

---

## 💻 C++ Code Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}

class DisjointSet {
    vector<int> parent, rank;
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if(px == py) return;

        if(rank[px] < rank[py]) parent[px] = py;
        else if(rank[px] > rank[py]) parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

int kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), cmp);
    DisjointSet ds(V);
    int mst_weight = 0;

    for(auto e : edges) {
        if(ds.find(e.u) != ds.find(e.v)) {
            mst_weight += e.w;
            ds.unite(e.u, e.v);
        }
    }
    return mst_weight;
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<Edge> edges(E);

    for(int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    cout << "Weight of Minimum Spanning Tree: " << kruskalMST(V, edges) << endl;
    return 0;
}

⏱️ Time & Space Complexity

Time Complexity: O(E log E) for sorting edges + O(E α(V)) for union-find operations

Space Complexity: O(V + E)

🌍 Real-Life Applications

Network design (telecommunication, electricity grids).

Road and railway planning.

Clustering problems in machine learning.

📌 Last Note

Kruskal’s Algorithm is edge-based and works best for sparse graphs.

Always use disjoint set with path compression for efficiency.

Compare with Prim’s Algorithm:

Kruskal → better for sparse graphs.

Prim → better for dense graphs.