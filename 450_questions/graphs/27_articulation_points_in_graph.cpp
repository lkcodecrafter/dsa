/*
    QUESTION    : Articulation Point - I (Cut Vertices in a Graph - Tarjan's Algorithm)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/articulation-point-1/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Tarjan's Articulation Point DFS
// S.C : O(V)     - tin, low, visited, and isAP arrays
class Solution {
private:
    int timer = 1;

    void dfs(int u, int parent, vector<int> adj[], vector<int>& tin, vector<int>& low,
             vector<bool>& visited, vector<bool>& isAP) {
        visited[u] = true;
        tin[u] = low[u] = timer++;
        int children = 0;

        for (int v : adj[u]) {
            if (v == parent) continue;

            if (visited[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                children++;
                dfs(v, u, adj, tin, low, visited, isAP);
                low[u] = min(low[u], low[v]);

                // Case 1: Non-root node is AP if low[v] >= tin[u]
                if (parent != -1 && low[v] >= tin[u]) {
                    isAP[u] = true;
                }
            }
        }

        // Case 2: Root node is AP if it has 2 or more independent children in DFS tree
        if (parent == -1 && children > 1) {
            isAP[u] = true;
        }
    }

public:
    vector<int> articulationPoints(int V, vector<int> adj[]) {
        vector<int> tin(V, 0);
        vector<int> low(V, 0);
        vector<bool> visited(V, false);
        vector<bool> isAP(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, -1, adj, tin, low, visited, isAP);
            }
        }

        vector<int> result;
        for (int i = 0; i < V; i++) {
            if (isAP[i]) {
                result.push_back(i);
            }
        }

        return result.empty() ? vector<int>{-1} : result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Non-root AP: `low[v] >= tin[u]`.
 * - Root AP: `parent == -1 && children > 1`.
 * - Time: O(V + E), Space: O(V).
 */
