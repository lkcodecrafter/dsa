/*
    QUESTION    : Course Schedule II (Find the Ordering of Tasks / Prerequisites)
    Company Tags: Amazon, Microsoft, Google, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/course-schedule/1
    LeetCode    : https://leetcode.com/problems/course-schedule-ii/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Kahn's Topological Sort
// S.C : O(V + E) - Adjacency list and in-degree vector
class Solution {
public:
    vector<int> findOrder(int n, int m, vector<vector<int>> prerequisites) {
        vector<vector<int>> adj(n);
        vector<int> inDegree(n, 0);

        for (auto& prereq : prerequisites) {
            adj[prereq[1]].push_back(prereq[0]); // [course, prereq] -> prereq -> course
            inDegree[prereq[0]]++;
        }

        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> order;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            order.push_back(u);

            for (int v : adj[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // If cycle exists, impossible to finish all courses
        if (order.size() != n) {
            return {};
        }

        return order;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Directed edge: `prereq -> course`.
 * - Run Kahn's Algorithm. If `order.size() == n` return `order`, else return `{}`.
 * - Time: O(V + E), Space: O(V + E).
 */
