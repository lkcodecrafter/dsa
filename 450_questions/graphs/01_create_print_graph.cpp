/*
    QUESTION    : Print adjacency list for a directed/undirected graph
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/print-adjacency-list-1587115620/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Build adjacency list representation of graph
// S.C : O(V + E) - Adjacency list
class Solution {
public:
    vector<vector<int>> printGraph(int V, vector<pair<int, int>>& edges) {
        vector<vector<int>> adj(V);

        // Populate undirected edges
        for (auto& edge : edges) {
            int u = edge.first;
            int v = edge.second;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        return adj;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `adj[u].push_back(v); adj[v].push_back(u);`
 * - Time: O(V + E), Space: O(V + E).
 */
