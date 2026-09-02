/*
    QUESTION    : Minimum edges to reverse to make path from a source to a destination (0-1 BFS)
    Company Tags: Directi, Amazon
    GfG Link    : https://www.geeksforgeeks.org/minimum-edges-reverse-make-path-source-destination/
*/

#include <iostream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - 0-1 BFS: original edges have weight 0 (push_front), reversed edges have weight 1 (push_back)
// S.C : O(V + E) - Adjacency list and deque
class Solution {
public:
    int minEdgeReversals(vector<pair<int, int>>& edgeList, int V, int E, int src, int dst) {
        // Directed graph with weighted edges: original edge weight 0, reverse edge weight 1
        vector<vector<pair<int, int>>> adj(V);

        for (int i = 0; i < E; i++) {
            int u = edgeList[i].first;
            int v = edgeList[i].second;
            adj[u].push_back({v, 0}); // Original direction
            adj[v].push_back({u, 1}); // Reversed direction requires 1 reversal
        }

        vector<int> dist(V, INT_MAX);
        deque<int> dq;

        dist[src] = 0;
        dq.push_front(src);

        // 0-1 BFS
        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();

            if (u == dst) {
                return dist[dst];
            }

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;

                    if (weight == 0) {
                        dq.push_front(v); // 0 weight -> highest priority
                    } else {
                        dq.push_back(v);  // 1 weight -> standard queue
                    }
                }
            }
        }

        return (dist[dst] == INT_MAX) ? -1 : dist[dst];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Model as 0-1 Graph: edge `u -> v` has weight 0; reverse `v -> u` has weight 1.
 * - Run 0-1 BFS with `std::deque`: push 0-weight to front, 1-weight to back.
 * - Time: O(V + E), Space: O(V + E).
 */
