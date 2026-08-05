/*
QUESTION:
There are a total of numCourses courses you have to take, labeled from 0 to
numCourses - 1. You are given an array prerequisites where prerequisites[i] =
[ai, bi] indicates that you must take course bi first if you want to take course
ai.

Return true if you can finish all courses. Otherwise, return false.

APPROACH:
- We can model the problem as a directed graph, where each course is a node, and
a prerequisite pair [ai, bi] indicates a directed edge from course bi to course
ai.
- To check if we can finish all courses, we need to ensure that the directed
graph is a DAG (Directed Acyclic Graph) with no cycles.
- If there are cycles in the graph, it means there is a circular dependency
between courses, and we cannot finish all courses in such cases.
- To check for cycles, we can use Kahn's algorithm for Topological Sorting.
- If we can perform a successful Topological Sort (i.e., there is no cycle),
then it means we can finish all courses.

COMPLEXITY ANALYSIS:
- Time Complexity: O(N + E), where N is the number of courses (nodes) and E is
the number of prerequisites (edges) in the graph. We perform a BFS-like
traversal of all nodes and edges.
- Space Complexity: O(N + E), where N is the number of courses (nodes) and E is
the number of prerequisites (edges) in the graph. We use additional space to
store the adjacency list and indegree of each node.

DRY RUN:

Scenario 1: Possible to Finish All Courses (No Cycle)
Input: numCourses = 3, prerequisites = [[1, 0], [2, 1]]
Edges: 0 -> 1 and 1 -> 2

1. Initialization:
   - indeg = [0, 0, 0]
   - Build Graph & Indegrees:
     - Edge [1, 0]: Build 0 -> 1, indeg[1] becomes 1
     - Edge [2, 1]: Build 1 -> 2, indeg[2] becomes 1
   - Final indeg = [0, 1, 1]
   - adj = {0: [1], 1: [2], 2: []}

2. Find nodes with indegree 0:
   - Course 0 has indegree 0. Push 0. Queue q = [0]
   - cnt = 0

3. BFS Traversal:
   - Pop 0 from queue. cnt becomes 1.
     - Look at neighbors of 0: [1]
     - Decrement indeg[1] to 0. Since it's 0, push 1. Queue q = [1]
   - Pop 1 from queue. cnt becomes 2.
     - Look at neighbors of 1: [2]
     - Decrement indeg[2] to 0. Since it's 0, push 2. Queue q = [2]
   - Pop 2 from queue. cnt becomes 3.
     - Look at neighbors of 2: None. Queue q is now empty.

4. Result Check:
   - cnt (3) == numCourses (3) -> Returns true (All courses can be finished!)


Scenario 2: Impossible to Finish All Courses (Cycle Present)
Input: numCourses = 2, prerequisites = [[1, 0], [0, 1]]
Edges: 0 -> 1 and 1 -> 0 (Cycle: 0 -> 1 -> 0)

1. Initialization:
   - indeg = [0, 0]
   - Build Graph & Indegrees:
     - Edge [1, 0]: Build 0 -> 1, indeg[1] becomes 1
     - Edge [0, 1]: Build 1 -> 0, indeg[0] becomes 1
   - Final indeg = [1, 1]
   - adj = {0: [1], 1: [0]}

2. Find nodes with indegree 0:
   - No course has indegree 0. Queue q = [] (empty)
   - cnt = 0

3. BFS Traversal:
   - Queue is empty, so loop is skipped entirely.

4. Result Check:
   - cnt (0) == numCourses (2) is false -> Returns false (Cannot finish all
courses due to cyclic dependencies)
*/

bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
  vector<int> indeg(numCourses, 0);
  vector<vector<int>> adj(numCourses);

  // Calculate the indegree of each course and build the adjacency list
  for (auto it : prerequisites) {
    indeg[it[0]]++; // this lines means it[0] has one incoming edge
    adj[it[1]].push_back(
        it[0]); // this lines means it[0] has an edge from it[1]
  }

  queue<int> q;

  // Find courses with indegree 0 and add them to the queue
  for (int i = 0; i < numCourses; i++) {
    if (indeg[i] == 0) {
      q.push(i);
    }
  }

  int cnt = 0;

  while (!q.empty()) {
    int node = q.front();
    q.pop();
    cnt++;

    // Remove the course and its outgoing edges
    for (auto v : adj[node]) {
      indeg[v]--;
      if (indeg[v] == 0) {
        q.push(v);
      }
    }
  }

  // If the count of finished courses is equal to the total number of courses,
  // return true
  return cnt == numCourses;
}
