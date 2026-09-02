/*
    QUESTION    : Chinese Postman or Route Inspection Problem
    Company Tags: Google
    GfG Link    : https://www.geeksforgeeks.org/chinese-postman-route-inspection-problem/
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V^3 + 2^K * K^2) where K is number of odd degree vertices - Floyd Warshall + Bitmask Matching
// S.C : O(2^K) - Memoization table
class Solution {
private:
    int matchOddVertices(int mask, const vector<int>& odd, const vector<vector<int>>& dist, vector<int>& dp) {
        if (mask == 0) return 0;
        if (dp[mask] != -1) return dp[mask];

        int k = odd.size();
        int ans = INT_MAX;

        // Find first unmatched odd vertex
        int p1 = 0;
        while (!(mask & (1 << p1))) p1++;

        // Try pairing p1 with every other available odd vertex p2
        for (int p2 = p1 + 1; p2 < k; p2++) {
            if (mask & (1 << p2)) {
                int cost = dist[odd[p1]][odd[p2]] + matchOddVertices(mask ^ (1 << p1) ^ (1 << p2), odd, dist, dp);
                ans = min(ans, cost);
            }
        }

        return dp[mask] = ans;
    }

public:
    int minRouteInspection(int V, const vector<vector<int>>& edges) {
        vector<vector<int>> dist(V, vector<int>(V, 1e8));
        vector<int> degree(V, 0);
        int totalEdgeWeight = 0;

        for (int i = 0; i < V; i++) dist[i][i] = 0;

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);
            degree[u]++;
            degree[v]++;
            totalEdgeWeight += w;
        }

        // All-Pairs Shortest Path (Floyd-Warshall)
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        // Identify all odd-degree vertices
        vector<int> odd;
        for (int i = 0; i < V; i++) {
            if (degree[i] % 2 != 0) {
                odd.push_back(i);
            }
        }

        if (odd.empty()) {
            return totalEdgeWeight; // Graph is already Eulerian!
        }

        int k = odd.size();
        vector<int> dp(1 << k, -1);
        int minDuplicateWeight = matchOddVertices((1 << k) - 1, odd, dist, dp);

        return totalEdgeWeight + minDuplicateWeight;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If all degrees even: `return sum(edges)`.
 * - Else: find odd degree vertices, pair them using Floyd-Warshall + Bitmask Matching to minimize duplicated edges.
 * - Time: O(V^3 + 2^K * K^2), Space: O(2^K).
 */
