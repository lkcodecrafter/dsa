/*
    QUESTION    : Check if given graph is tree or not
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://www.geeksforgeeks.org/check-given-graph-tree/
    LeetCode    : https://leetcode.com/problems/graph-valid-tree/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - DFS traversal for cycle detection and connectivity check
// S.C : O(V)     - Visited vector and recursion stack
class Solution {
private:
    bool isCyclicUtil(int u, int parent, vector<bool> &visited, const vector<vector<int>> &adj) {
        visited[u] = true;

        for (int v : adj[u]) {
            if (!visited[v]) {
                if (isCyclicUtil(v, u, visited, adj)) {
                    return true;
                }
            } else if (v != parent) {
                // If adjacent node is visited and not parent of current node, cycle exists!
                return true;
            }
        }

        return false;
    }

public:
    bool isTree(int V, int E, vector<vector<int>> &adj) {
        // Condition 1: A tree with V vertices MUST have exactly V - 1 edges
        if (E != V - 1) return false;

        vector<bool> visited(V, false);

        // Condition 2: No cycle in graph
        if (isCyclicUtil(0, -1, visited, adj)) {
            return false;
        }

        // Condition 3: Graph must be fully connected
        for (int i = 0; i < V; i++) {
            if (!visited[i]) return false;
        }

        return true;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TREE CONDITIONS FOR GRAPH
 * ============================================================================
 *
 * An undirected graph is a tree if and only if:
 * 1. Edge Count == V - 1
 * 2. It is Acyclic (No cycles)
 * 3. It is Connected (All V vertices reachable from vertex 0)
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Check `E == V - 1`.
 * - Run DFS from `0` to check for cycles (`visited[v] && v != parent`).
 * - Verify `visited[i] == true` for all $i \in [0, V-1]$.
 * - Time: O(V + E), Space: O(V).
 */
