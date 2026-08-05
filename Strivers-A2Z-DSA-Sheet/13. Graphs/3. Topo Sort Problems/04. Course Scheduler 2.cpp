/*
QUESTION:
There are a total of numCourses courses you have to take, labeled from 0 to
numCourses - 1. You are given an array prerequisites where prerequisites[i] =
[ai, bi] indicates that you must take course bi first if you want to take course
ai.

Return the ordering of courses you should take to finish all courses. If there
are many valid answers, return any of them. If it is impossible to finish all
courses, return an empty array.

APPROACH:
- We can model the problem as a directed graph, where each course is a node, and
a prerequisite pair [ai, bi] indicates a directed edge from course bi to course
ai.
- To find the course ordering, we can use Kahn's algorithm for Topological
Sorting.
- If we can perform a successful Topological Sort, it means we can finish all
courses, and the order in which we pop the nodes from the queue will give us the
correct course order.
- If there is a cycle in the graph (i.e., it is not possible to finish all
courses), the algorithm will not be able to remove all nodes with indegree 0,
and we will not get a valid course ordering.

COMPLEXITY ANALYSIS:
- Time Complexity: O(N + E), where N is the number of courses (nodes) and E is
the number of prerequisites (edges) in the graph. We perform a BFS-like
traversal of all nodes and edges.
- Space Complexity: O(N + E), where N is the number of courses (nodes) and E is
the number of prerequisites (edges) in the graph. We use additional space to
store the adjacency list and indegree of each node.

DRY RUN:

Scenario 1: Possible to complete all courses (No cycle)
Input: numCourses = 4, prerequisites = [[1,0], [2,0], [3,1], [3,2]]
Graph representation:
- To take 1, take 0 first (0 -> 1)
- To take 2, take 0 first (0 -> 2)
- To take 3, take 1 first (1 -> 3)
- To take 3, take 2 first (2 -> 3)

1. Initialization:
   - indeg = [0, 0, 0, 0] (Size 4, initialized with 0)
   - adj = [[], [], [], []] (Size 4, empty lists)

2. Calculate Indegree & Build Adjacency List:
   - Edge [1, 0]: Build 0 -> 1. indeg[1] = 1, adj[0] = [1]
   - Edge [2, 0]: Build 0 -> 2. indeg[2] = 1, adj[0] = [1, 2]
   - Edge [3, 1]: Build 1 -> 3. indeg[3] = 1, adj[1] = [3]
   - Edge [3, 2]: Build 2 -> 3. indeg[3] = 2, adj[2] = [3]

   Final indegree array: [0, 1, 1, 2]
   Final adjacency list: {0: [1, 2], 1: [3], 2: [3], 3: []}

3. Populate Queue with 0-indegree nodes:
   - indeg[0] == 0: Push 0. Queue q = [0]

4. BFS Process:
   - Pop 0:
     - Push 0 to courseOrder. courseOrder = [0]
     - Neighbors of 0: [1, 2]
     - Neighbor 1: indeg[1] becomes 0 -> Push 1. Queue q = [1]
     - Neighbor 2: indeg[2] becomes 0 -> Push 2. Queue q = [1, 2]
   - Pop 1:
     - Push 1 to courseOrder. courseOrder = [0, 1]
     - Neighbors of 1: [3]
     - Neighbor 3: indeg[3] becomes 1
   - Pop 2:
     - Push 2 to courseOrder. courseOrder = [0, 1, 2]
     - Neighbors of 2: [3]
     - Neighbor 3: indeg[3] becomes 0 -> Push 3. Queue q = [3]
   - Pop 3:
     - Push 3 to courseOrder. courseOrder = [0, 1, 2, 3]
     - Neighbors of 3: None.

5. Verification:
   - courseOrder size (4) == numCourses (4) -> Return courseOrder: [0, 1, 2, 3]
(or [0, 2, 1, 3])


Scenario 2: Cycle detected (Cannot complete all courses)
Input: numCourses = 2, prerequisites = [[1, 0], [0, 1]]
Graph representation:
- To take 1, take 0 first (0 -> 1)
- To take 0, take 1 first (1 -> 0)

1. Initialization:
   - indeg = [0, 0]
   - Build Graph & Indegrees:
     - Edge [1, 0]: Build 0 -> 1, indeg[1] = 1
     - Edge [0, 1]: Build 1 -> 0, indeg[0] = 1
   - Final indegree array: [1, 1]
   - Final adjacency list: {0: [1], 1: [0]}

2. Populate Queue with 0-indegree nodes:
   - No course has indegree 0. Queue q = [] (empty)

3. BFS Process:
   - Queue is empty, loop does not execute.

4. Verification:
   - courseOrder size (0) != numCourses (2) -> Return empty list {}
*/

vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
  // indeg array stores the count of incoming edges (prerequisites) for each
  // course
  vector<int> indeg(numCourses, 0);

  // adj list stores the dependency graph (which courses open up after taking a
  // course)
  vector<vector<int>> adj(numCourses);

  // Build the graph and calculate indegree of each course
  for (auto it : prerequisites) {
    int u = it[1]; // u is the prerequisite course (must be taken first)
    int v = it[0]; // v is the course that depends on u

    indeg[v]++;          // Increment indegree since course v depends on u
    adj[u].push_back(v); // Add a directed edge from u to v (u -> v)
  }

  // Queue to keep track of courses that have 0 prerequisites left
  queue<int> q;

  // Find all courses with 0 prerequisites to start with
  for (int i = 0; i < numCourses; i++) {
    if (indeg[i] == 0) {
      q.push(i); // Add course i to queue as we can take it directly
    }
  }

  // Vector to store the final sequence of courses to take
  vector<int> courseOrder;

  // Process courses one by one
  while (!q.empty()) {
    int node = q.front(); // Get the front course from queue
    q.pop();              // Remove it from the queue

    courseOrder.push_back(node); // Add this course to our final order

    // For all courses that depend on this current completed course
    for (auto v : adj[node]) {
      indeg[v]--; // Decrement the dependency count of the neighbor course

      // If all prerequisites of neighbor course v are completed, push it to
      // queue
      if (indeg[v] == 0) {
        q.push(v);
      }
    }
  }

  // If we completed all courses, return the valid ordering
  if (courseOrder.size() == numCourses) {
    return courseOrder;
  }

  // Otherwise, there was a cycle (circular dependency) and it's impossible to
  // complete all courses
  return {};
}
