/*
    QUESTION    : BFS of graph (Breadth First Traversal)
    Company Tags: Amazon, Microsoft, Samsung, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Level-order breadth-first traversal
// S.C : O(V)     - Visited array and queue
class Solution {
public:
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        vector<int> bfs;
        vector<bool> visited(V, false);
        queue<int> q;

        // Start BFS from node 0
        q.push(0);
        visited[0] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            bfs.push_back(node);

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return bfs;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `q.push(0); visited[0] = true;`
 * - While `!q.empty()`: pop `node`, visit unvisited neighbors: `visited[neighbor] = true; q.push(neighbor);`
 * - Time: O(V + E), Space: O(V).
 */
