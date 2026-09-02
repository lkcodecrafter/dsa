/*
    QUESTION    : Negative weight cycle (Detect Negative Cycle using Bellman-Ford)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/negative-weight-cycle3504/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V * E) - Bellman-Ford Algorithm
// S.C : O(V)     - Distance array
class Solution {
public:
    int isNegativeWeightCycle(int n, vector<vector<int>> edges) {
        vector<int> dist(n, 1e8);
        dist[0] = 0;

        // Relax edges n - 1 times
        for (int i = 1; i <= n - 1; i++) {
            for (auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int wt = edge[2];

                if (dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // N-th relaxation step: If any distance shortens further, negative cycle exists
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            if (dist[u] + wt < dist[v]) {
                return 1; // Negative weight cycle detected!
            }
        }

        return 0;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Relax all edges $n - 1$ times.
 * - On $n$-th pass: if `dist[u] + wt < dist[v]` $\rightarrow$ return 1 (Negative Cycle).
 * - Time: O(V * E), Space: O(V).
 */
