/*
    QUESTION    : Distance from the Source (Bellman-Ford Algorithm)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V * E) - Relaxes all edges V - 1 times + 1 negative cycle detection pass
// S.C : O(V)     - Distance array
class Solution {
public:
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        vector<int> dist(V, 1e8);
        dist[S] = 0;

        // Step 1: Relax all edges V - 1 times
        for (int i = 1; i <= V - 1; i++) {
            for (auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int wt = edge[2];

                if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // Step 2: Nth relaxation check for negative weight cycles
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                return {-1}; // Negative weight cycle detected!
            }
        }

        return dist;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Relax all edges $V - 1$ times: `if (dist[u] + wt < dist[v]) dist[v] = dist[u] + wt;`
 * - $V$-th pass: if any distance further decreases $\rightarrow$ negative cycle!
 * - Time: O(V * E), Space: O(V).
 */
