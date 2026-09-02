/*
    QUESTION    : Minimum time taken by each job to be completed given by a Directed Acyclic Graph
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/minimum-time-taken-by-each-job-to-be-completed-given-by-a-directed-acyclic-graph/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Kahn's Topological Sort tracking levels
// S.C : O(V)     - In-degree and job time arrays
class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>> &edges, int m) {
        vector<vector<int>> adj(n + 1);
        vector<int> inDegree(n + 1, 0);

        for (int i = 0; i < m; i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
            inDegree[edges[i][1]]++;
        }

        queue<int> q;
        vector<int> jobTime(n + 1, 0);

        // Push jobs with no prerequisites (take 1 unit of time)
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
                jobTime[i] = 1;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    jobTime[v] = jobTime[u] + 1;
                    q.push(v);
                }
            }
        }

        vector<int> result(jobTime.begin() + 1, jobTime.end());
        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `jobTime[i] = 1` for nodes with `inDegree == 0`.
 * - For neighbor `v`: `jobTime[v] = jobTime[u] + 1` when `inDegree[v] == 0`.
 * - Time: O(V + E), Space: O(V).
 */
