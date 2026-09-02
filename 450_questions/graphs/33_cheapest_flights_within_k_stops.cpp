/*
    QUESTION    : Cheapest Flights Within K Stops
    Company Tags: Amazon, Google, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/cheapest-flights-within-k-stops/1
    LeetCode    : https://leetcode.com/problems/cheapest-flights-within-k-stops/
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(K * E) - Level-order BFS Dijkstra relaxation up to K + 1 flight edges
// S.C : O(V + E) - Queue and distance array
class Solution {
public:
    int CheapestFLight(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<vector<pair<int, int>>> adj(n);
        for (auto& flight : flights) {
            adj[flight[0]].push_back({flight[1], flight[2]});
        }

        // Queue stores {stops, {node, cost}}
        queue<pair<int, pair<int, int>>> q;
        q.push({0, {src, 0}});

        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            int stops = curr.first;
            int u = curr.second.first;
            int cost = curr.second.second;

            if (stops > K) continue;

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (cost + weight < dist[v] && stops <= K) {
                    dist[v] = cost + weight;
                    q.push({stops + 1, {v, cost + weight}});
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
 * - BFS queue ordered strictly by stops: `{stops, {node, cost}}`.
 * - If `cost + wt < dist[v]` and `stops <= K`: `dist[v] = cost + wt; q.push({stops + 1, {v, dist[v]}});`
 * - Time: O(K * E), Space: O(V + E).
 */
