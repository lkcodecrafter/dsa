/*
    QUESTION    : Strongly Connected Components (Kosaraju's Algorithm)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Kosaraju's 3-step algorithm (Topo DFS + Graph Transpose + Reverse DFS)
// S.C : O(V + E) - Transposed adjacency list and visited array
class Solution {
private:
    void dfsTopo(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfsTopo(v, adj, visited, st);
            }
        }
        st.push(u); // Push node after visiting all reachable vertices
    }

    void dfsTranspose(int u, vector<vector<int>>& adjT, vector<bool>& visited) {
        visited[u] = true;
        for (int v : adjT[u]) {
            if (!visited[v]) {
                dfsTranspose(v, adjT, visited);
            }
        }
    }

public:
    int kosaraju(int V, vector<vector<int>>& adj) {
        stack<int> st;
        vector<bool> visited(V, false);

        // Step 1: Order vertices by decreasing finish time using DFS
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsTopo(i, adj, visited, st);
            }
        }

        // Step 2: Transpose the graph (reverse all directed edges)
        vector<vector<int>> adjT(V);
        for (int u = 0; u < V; u++) {
            visited[u] = false; // Reset visited array
            for (int v : adj[u]) {
                adjT[v].push_back(u);
            }
        }

        // Step 3: Pop vertices from stack and run DFS on transposed graph
        int sccCount = 0;
        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!visited[node]) {
                sccCount++;
                dfsTranspose(node, adjT, visited);
            }
        }

        return sccCount;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Step 1: Order nodes by finish time in `stack<int>`.
 * - Step 2: Build transpose graph `adjT`.
 * - Step 3: Pop from stack and run DFS on `adjT`. Each DFS call = 1 SCC.
 * - Time: O(V + E), Space: O(V + E).
 */
