/*
    QUESTION    : Detect cycle in an undirected graph (DFS with Parent Pointer)
    Company Tags: Amazon, Microsoft, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - DFS with parent tracking
// S.C : O(V)     - Visited array and recursion call stack
class Solution {
private:
    bool dfs(int node, int parent, vector<int> adj[], vector<bool>& visited) {
        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, node, adj, visited)) {
                    return true;
                }
            }
            // If neighbor is already visited AND is NOT the parent of current node, cycle detected!
            else if (neighbor != parent) {
                return true;
            }
        }

        return false;
    }

public:
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfs(i, -1, adj, visited)) {
                    return true;
                }
            }
        }

        return false;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `if (!visited[neighbor]) dfs(neighbor, node)`.
 * - `else if (neighbor != parent) return true;` (Cycle found).
 * - Time: O(V + E), Space: O(V).
 */
