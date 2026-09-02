#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
 * Problem: Course Schedule (LeetCode 207)
 * Determine if you can finish all courses given the prerequisites.
 *
 * Pattern: Topological Sort (Kahn's Algorithm) / Directed Acyclic Graph (DAG) cycle detection
 *
 * Complexity:
 * - Time Complexity: O(V + E) where V is the number of courses (numCourses) and E is the number of prerequisites.
 *   Building the graph takes O(E). In Kahn's algorithm, each node and edge is processed at most once: O(V + E).
 * - Space Complexity: O(V + E) for the adjacency list representation of the graph, the indegree array O(V),
 *   and the queue O(V) for BFS traversal.
 *
 * Visualizations:
 * 1. Acyclic Graph (Valid case: no cycle)
 *    0 (indegree=0) ---> 1 (indegree=1) ---> 2 (indegree=1) ---> 3 (indegree=1)
 *
 * 2. Cyclic Graph (Invalid case: has cycle)
 *    0 (indegree=0) ---> 1 (indegree=2) ---> 2 (indegree=1)
 *                           ^                 |
 *                           |                 v
 *                           +---------------- 3 (indegree=1)
 *
 * Memorization Hook:
 * "Find indegrees. Queue up 0-indegree courses. Pop course, increment processed count, decrement indegrees 
 * of neighbors. If any neighbor hits 0 indegree, queue it. Success if processed count equals total courses."
 *
 * 1-Minute Quick Revision:
 * 1. Build an adjacency list `adj` mapping dependencies: prerequisites[i][1] (pre) -> prerequisites[i][0] (course).
 * 2. Maintain an `indegree` array where `indegree[course]` represents the number of prereqs it depends on.
 * 3. Add all courses with `indegree == 0` to a queue `q`.
 * 4. While `q` is not empty:
 *    - Pop the front course `u`, and increment the `count` of completed courses.
 *    - For each neighbor `v` of `u`, decrement its `indegree`. If it becomes 0, push `v` to `q`.
 * 5. Return `count == numCourses`.
 *
 * Dry Run:
 * numCourses = 4, prerequisites = [[1, 0], [2, 1], [3, 2]] (meaning 0 -> 1 -> 2 -> 3)
 * adj = {0: [1], 1: [2], 2: [3]}, indegree = [0, 1, 1, 1]
 *
 * | Step / Iteration | Popped Node u | Neighbors v | indegree[v] after decr | Queue State (Front -> Back) | count | Condition / Action                  |
 * |------------------|---------------|-------------|------------------------|-----------------------------|-------|-------------------------------------|
 * | Initialization   | -             | -           | -                      | [0]                         | 0     | Push node 0 (indegree is 0)         |
 * | Iteration 1      | 0             | 1           | indegree[1] = 0        | [1]                         | 1     | Pop 0; decr indegree[1] -> push 1   |
 * | Iteration 2      | 1             | 2           | indegree[2] = 0        | [2]                         | 2     | Pop 1; decr indegree[2] -> push 2   |
 * | Iteration 3      | 2             | 3           | indegree[3] = 0        | [3]                         | 3     | Pop 2; decr indegree[3] -> push 3   |
 * | Iteration 4      | 3             | -           | -                      | []                          | 4     | Pop 3; no neighbors                 |
 * | End              | -             | -           | -                      | []                          | 4     | count == numCourses (4 == 4) -> true|
 */
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Track the number of dependencies (incoming edges) for each course
        vector<int> indegree(numCourses, 0);
        // Adjacency list representation of the directed dependency graph
        vector<vector<int>> adj(numCourses);
        
        // Build the dependency graph: p[1] -> p[0] means p[1] must be completed before starting p[0]
        for (auto &p : prerequisites) {
            adj[p[1]].push_back(p[0]); 
            indegree[p[0]]++;          // Increment indegree for the dependent course
        }
        
        // Queue to store courses with no prerequisites (indegree == 0)
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int count = 0; // Tracks the number of courses that can be completed
        
        // Process courses in topological order
        while (!q.empty()) {
            int u = q.front(); 
            q.pop();
            count++;
            
            // For all courses that depend on the completed course 'u'
            for (auto v : adj[u]) {
                // Decrement neighbor's indegree. If all prerequisites are cleared (indegree becomes 0)
                if (--indegree[v] == 0) {
                    q.push(v); // Queue it for completion
                }
            }
        }
        
        // If we completed all courses, no cycle was detected
        return count == numCourses;
    }
};