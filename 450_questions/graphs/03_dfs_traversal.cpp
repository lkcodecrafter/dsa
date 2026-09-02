/*
    QUESTION    : DFS of Graph (Depth First Traversal)
    Company Tags: Amazon, Microsoft, Samsung, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Recursive Depth First Search
// S.C : O(V)     - Visited array and recursion call stack
class Solution {
private:
    void dfs(int node, vector<int> adj[], vector<bool>& visited, vector<int>& result) {
        visited[node] = true;
        result.push_back(node);

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, result);
            }
        }
    }

public:
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        vector<int> result;
        vector<bool> visited(V, false);

        dfs(0, adj, visited, result);
        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `visited[node] = true; result.push_back(node);`
 * - For each unvisited neighbor: `dfs(neighbor, adj, visited, result)`.
 * - Time: O(V + E), Space: O(V).
 */
