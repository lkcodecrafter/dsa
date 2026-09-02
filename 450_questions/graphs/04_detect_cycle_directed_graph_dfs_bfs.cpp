/*
    QUESTION    : Detect cycle in a directed graph (DFS Recursion Stack & Kahn's BFS Algorithm)
    Company Tags: Amazon, Microsoft, Flipkart, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1
    LeetCode    : https://leetcode.com/problems/course-schedule/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Kahn's Algorithm (BFS) counts processed nodes
// S.C : O(V)     - In-degree array and queue
class Solution {
public:
    bool isCyclic(int V, vector<int> adj[]) {
        vector<int> inDegree(V, 0);

        // Step 1: Compute in-degree for all vertices
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                inDegree[v]++;
            }
        }

        // Step 2: Push all vertices with 0 in-degree into BFS queue
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        int countVisited = 0;

        // Step 3: BFS topological sort processing
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            countVisited++;

            for (int v : adj[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // If countVisited != V, a cycle prevented some nodes from ever reaching 0 in-degree!
        return (countVisited != V);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Kahn's BFS: Calculate `inDegree`. Push all `inDegree == 0` to `queue`.
 * - Process nodes, decrement neighbors' in-degree.
 * - Cycle exists if `countVisited != V`.
 * - Time: O(V + E), Space: O(V).
 */
