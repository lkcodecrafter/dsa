/*
    QUESTION    : Bipartite Graph (Check if graph can be 2-colored)
    Company Tags: Amazon, Microsoft, Google, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/bipartite-graph/1
    LeetCode    : https://leetcode.com/problems/is-graph-bipartite/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - BFS 2-Coloring algorithm
// S.C : O(V)     - Color array and queue
class Solution {
private:
    bool bfsCheck(int start, int V, vector<int> adj[], vector<int>& color) {
        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                // If neighbor is uncolored, assign opposite color
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                }
                // If neighbor has same color, odd-length cycle exists -> Not Bipartite!
                else if (color[v] == color[u]) {
                    return false;
                }
            }
        }

        return true;
    }

public:
    bool isBipartite(int V, vector<int> adj[]) {
        vector<int> color(V, -1); // -1 = uncolored, 0 = color A, 1 = color B

        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (!bfsCheck(i, V, adj, color)) {
                    return false;
                }
            }
        }

        return true;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - 2-Coloring BFS: uncolored neighbor gets `1 - color[u]`.
 * - If `color[v] == color[u]`: return `false` (odd cycle detected).
 * - Time: O(V + E), Space: O(V).
 */
