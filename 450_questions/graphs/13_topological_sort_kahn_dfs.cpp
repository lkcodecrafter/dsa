/*
    QUESTION    : Topological sort (Kahn's Algorithm & DFS with Stack)
    Company Tags: Amazon, Microsoft, Google, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/topological-sort/1
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Kahn's Algorithm (BFS)
// S.C : O(V)     - In-degree array and queue
class Solution {
public:
    vector<int> topoSort(int V, vector<int> adj[]) {
        vector<int> inDegree(V, 0);

        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                inDegree[v]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            topo.push_back(u);

            for (int v : adj[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        return topo;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Compute in-degrees. Push `inDegree == 0` to queue.
 * - Append `u` to topo sort; decrement neighbor in-degrees; push newly zeroed nodes.
 * - Time: O(V + E), Space: O(V).
 */
