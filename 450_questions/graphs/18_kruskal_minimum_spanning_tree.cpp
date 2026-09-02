/*
    QUESTION    : Minimum Spanning Tree (Kruskal's Algorithm using Disjoint Set Union / DSU)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-spanning-tree/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Disjoint Set Union by Rank and Path Compression
class DSU {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    bool unite(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);

        if (rootI != rootJ) {
            if (rank[rootI] < rank[rootJ]) {
                parent[rootI] = rootJ;
            } else if (rank[rootI] > rank[rootJ]) {
                parent[rootJ] = rootI;
            } else {
                parent[rootJ] = rootI;
                rank[rootI]++;
            }
            return true; // Successfully united
        }

        return false; // Already in same component (Adding edge would create cycle!)
    }
};

/************************************************************ C++ ************************************************************/
// T.C : O(E log E) - Sorting edges + DSU union operations in O(alpha(V))
// S.C : O(V + E)   - DSU arrays and edge list
class Solution {
public:
    int spanningTree(int V, vector<vector<int>> adj[]) {
        vector<vector<int>> edges;

        for (int u = 0; u < V; u++) {
            for (auto& neighbor : adj[u]) {
                int v = neighbor[0];
                int weight = neighbor[1];
                if (u < v) { // Avoid duplicate undirected edges
                    edges.push_back({weight, u, v});
                }
            }
        }

        // Sort edges ascending by weight
        sort(edges.begin(), edges.end());

        DSU dsu(V);
        int mstWeight = 0;
        int edgesCount = 0;

        for (auto& edge : edges) {
            int w = edge[0];
            int u = edge[1];
            int v = edge[2];

            if (dsu.unite(u, v)) {
                mstWeight += w;
                edgesCount++;
                if (edgesCount == V - 1) break; // MST complete
            }
        }

        return mstWeight;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Sort edges ascending by weight.
 * - For each edge `{w, u, v}`: if `dsu.unite(u, v)` succeeds $\rightarrow$ `mstWeight += w`.
 * - Stop when $V - 1$ edges are added.
 * - Time: O(E log E), Space: O(V).
 */
