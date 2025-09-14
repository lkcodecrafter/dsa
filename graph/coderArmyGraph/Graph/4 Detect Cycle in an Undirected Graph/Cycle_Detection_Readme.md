# Cycle Detection in Graphs (C++)

## ⏱ 00:00 -- Introduction

Cycle detection is important in graph theory.\
- **Cycle**: A path that starts and ends at the same vertex with at
least one edge.\
- Used in: - Deadlock detection (OS).\
- Detecting circular dependencies.\
- Checking if a graph is a tree.

------------------------------------------------------------------------

## ⏱ 00:53 -- Cycle Detection using DFS

**Idea:**\
- Use recursion + visited array.\
- Keep track of the **parent** of each node.\
- If you reach a visited node that is **not the parent**, a cycle
exists.

### Code -- DFS Cycle Detection

``` cpp
#include <iostream>
#include <vector>
using namespace std;

bool dfsCycle(int node, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (dfsCycle(neighbor, node, adj, visited))
                return true;
        }
        else if (neighbor != parent) {
            return true; // Found a back edge → cycle
        }
    }
    return false;
}

bool hasCycleDFS(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfsCycle(i, -1, adj, visited))
                return true;
        }
    }
    return false;
}

int main() {
    int V = 5;
    vector<vector<int>> adj(V);

    // Undirected graph edges
    adj[0] = {1, 2};
    adj[1] = {0, 3};
    adj[2] = {0, 3};  // creates a cycle 0-2-3-1
    adj[3] = {1, 2};
    adj[4] = {}; // isolated

    if (hasCycleDFS(adj, V))
        cout << "Cycle detected using DFS" << endl;
    else
        cout << "No cycle (DFS)" << endl;
}
```

------------------------------------------------------------------------

## ⏱ 39:55 -- DFS Time and Space Complexity

-   **Time:** `O(V + E)`\
-   **Space:** `O(V)` (visited array + recursion stack).

------------------------------------------------------------------------

## ⏱ 55:37 -- Cycle Detection using BFS

**Idea (Kahn's Algorithm style):**\
- Use a queue and track parents.\
- If a visited node is found **not equal to parent**, cycle exists.

### Code -- BFS Cycle Detection

``` cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool bfsCycle(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<pair<int,int>> q; // {node, parent}
    visited[start] = true;
    q.push({start, -1});

    while (!q.empty()) {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push({neighbor, node});
            }
            else if (neighbor != parent) {
                return true; // Found cycle
            }
        }
    }
    return false;
}

bool hasCycleBFS(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (bfsCycle(i, adj, visited))
                return true;
        }
    }
    return false;
}

int main() {
    int V = 5;
    vector<vector<int>> adj(V);

    // Undirected graph edges
    adj[0] = {1, 2};
    adj[1] = {0, 3};
    adj[2] = {0, 3};  // creates a cycle
    adj[3] = {1, 2};
    adj[4] = {};

    if (hasCycleBFS(adj, V))
        cout << "Cycle detected using BFS" << endl;
    else
        cout << "No cycle (BFS)" << endl;
}
```

------------------------------------------------------------------------

## ⏱ 1:02:00 -- BFS Time and Space Complexity

-   **Time:** `O(V + E)`\
-   **Space:** `O(V)` (queue + visited array).

------------------------------------------------------------------------

## ⏱ 1:11:13 -- Last Note

### 🔑 Key Takeaways

-   DFS and BFS can both detect cycles in `O(V + E)`.\
-   DFS uses **recursion**; BFS uses **queue**.\
-   Both need a **parent check** to avoid false cycles.\
-   Works for **undirected graphs**.\
-   For **directed graphs**, cycle detection uses **DFS with recursion
    stack** or **Kahn's algorithm (topological sort)**.
