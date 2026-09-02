/*
    QUESTION    : Implementing Dijkstra Algorithm (Single Source Shortest Path with non-negative edge weights)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(E log V) - Min-Heap Dijkstra Algorithm
// S.C : O(V)       - Distance array and priority queue
class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
        // Min-Heap stores {distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

        vector<int> dist(V, INT_MAX);

        dist[S] = 0;
        minHeap.push({0, S});

        while (!minHeap.empty()) {
            int d = minHeap.top().first;
            int u = minHeap.top().second;
            minHeap.pop();

            // Skip outdated pairs
            if (d > dist[u]) continue;

            for (auto& edge : adj[u]) {
                int v = edge[0];
                int weight = edge[1];

                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    minHeap.push({dist[v], v});
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
 * - `minHeap.push({0, S}); dist[S] = 0;`
 * - Relaxation: `if (dist[u] + weight < dist[v]) { dist[v] = dist[u] + weight; minHeap.push({dist[v], v}); }`
 * - Time: O(E log V), Space: O(V).
 */
