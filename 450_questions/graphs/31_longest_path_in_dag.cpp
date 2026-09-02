/*
    QUESTION    : Longest Path in a Directed Acyclic Graph (DAG)
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Topological sort relaxation in linear time
// S.C : O(V + E) - Adjacency list and distance array
class Solution {
public:
    vector<int> maximumDistance(vector<vector<int>> edges, int v, int e, int src) {
        vector<vector<pair<int, int>>> adj(v);
        vector<int> inDegree(v, 0);

        for (int i = 0; i < e; i++) {
            adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
            inDegree[edges[i][1]]++;
        }

        // Topological Sort via Kahn's Algorithm
        queue<int> q;
        for (int i = 0; i < v; i++) {
            if (inDegree[i] == 0) q.push(i);
        }

        vector<int> topo;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto& edge : adj[u]) {
                int neighbor = edge.first;
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) q.push(neighbor);
            }
        }

        // Longest path distance array initialized to INT_MIN
        vector<int> dist(v, INT_MIN);
        dist[src] = 0;

        for (int u : topo) {
            if (dist[u] != INT_MIN) {
                for (auto& edge : adj[u]) {
                    int neighbor = edge.first;
                    int weight = edge.second;

                    if (dist[u] + weight > dist[neighbor]) {
                        dist[neighbor] = dist[u] + weight;
                    }
                }
            }
        }

        return dist;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Compute Topological Sort.
 * - `dist[src] = 0`, rest `INT_MIN`.
 * - Process nodes in topo order: `dist[v] = max(dist[v], dist[u] + wt)`.
 * - Time: O(V + E), Space: O(V + E).
 */
