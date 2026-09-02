/*
    QUESTION    : Critical Connections in a Network (Bridges in a Graph - Tarjan's Algorithm)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/bridge-edge-in-graph/1
    LeetCode    : https://leetcode.com/problems/critical-connections-in-a-network/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Tarjan's Bridge-Finding DFS using discovery time (tin) and lowest reachable time (low)
// S.C : O(V + E) - Adjacency list, tin, low, and visited arrays
class Solution {
private:
    int timer = 1;

    void dfs(int u, int parent, vector<vector<int>>& adj, vector<int>& tin, vector<int>& low,
             vector<bool>& visited, vector<vector<int>>& bridges) {
        visited[u] = true;
        tin[u] = low[u] = timer++;

        for (int v : adj[u]) {
            if (v == parent) continue; // Ignore parent edge

            if (visited[v]) {
                // Back-edge found: update low time
                low[u] = min(low[u], tin[v]);
            } else {
                // Forward tree edge: recurse DFS
                dfs(v, u, adj, tin, low, visited, bridges);
                low[u] = min(low[u], low[v]);

                // Bridge Condition: v cannot reach u or any ancestor of u
                if (low[v] > tin[u]) {
                    bridges.push_back({u, v});
                }
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

        vector<int> tin(n, 0);
        vector<int> low(n, 0);
        vector<bool> visited(n, false);
        vector<vector<int>> bridges;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, -1, adj, tin, low, visited, bridges);
            }
        }

        return bridges;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `tin[u] = low[u] = timer++`.
 * - If unvisited: `dfs(v, u); low[u] = min(low[u], low[v]);`
 *     - If `low[v] > tin[u]`: edge `(u, v)` is a BRIDGE!
 * - If visited (`v != parent`): `low[u] = min(low[u], tin[v]);`
 * - Time: O(V + E), Space: O(V).
 */
