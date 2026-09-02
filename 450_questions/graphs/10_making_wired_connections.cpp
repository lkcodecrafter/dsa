/*
    QUESTION    : Number of Operations to Make Network Connected (Connecting Cities / Redundant Connections)
    Company Tags: Amazon, Microsoft, Google
    LeetCode    : https://leetcode.com/problems/number-of-operations-to-make-network-connected/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Counting connected components via DFS
// S.C : O(V)     - Visited array and adjacency list
class Solution {
private:
    void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited);
            }
        }
    }

public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        // Need at least n - 1 total cables to connect n computers
        if (connections.size() < n - 1) {
            return -1;
        }

        vector<vector<int>> adj(n);
        for (auto& conn : connections) {
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }

        vector<bool> visited(n, false);
        int componentCount = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                componentCount++;
                dfs(i, adj, visited);
            }
        }

        // To connect K disconnected components, we need (K - 1) operations
        return componentCount - 1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `connections.size() < n - 1` return -1.
 * - Count connected components $C$ using DFS.
 * - Result = $C - 1$.
 * - Time: O(V + E), Space: O(V).
 */
