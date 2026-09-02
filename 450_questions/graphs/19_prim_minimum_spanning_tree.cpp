/*
    QUESTION    : Minimum Spanning Tree (Prim's Algorithm using Min-Heap)
    Company Tags: Amazon, Microsoft, Adobe, Cisco
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-spanning-tree/1
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(E log V) - Min-Heap greedy frontier expansion
// S.C : O(V)       - Visited array and priority queue
class Solution {
public:
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // Min-Heap stores {weight, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

        vector<bool> inMST(V, false);
        minHeap.push({0, 0}); // Start from node 0 with weight 0

        int mstWeight = 0;

        while (!minHeap.empty()) {
            auto curr = minHeap.top();
            minHeap.pop();

            int weight = curr.first;
            int u = curr.second;

            // If already included in MST, skip
            if (inMST[u]) continue;

            inMST[u] = true;
            mstWeight += weight;

            // Push all unvisited adjacent edges to Min-Heap
            for (auto& edge : adj[u]) {
                int v = edge[0];
                int w = edge[1];

                if (!inMST[v]) {
                    minHeap.push({w, v});
                }
            }
        }

        return mstWeight;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `minHeap.push({0, 0})`.
 * - Pop `{weight, u}`. If `!inMST[u]`: `inMST[u] = true; mstWeight += weight;`
 * - Push all adjacent unvisited edges to `minHeap`.
 * - Time: O(E log V), Space: O(V).
 */
