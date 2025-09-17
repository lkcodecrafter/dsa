# Topological Sort in Graphs (C++)

## ⏱ 00:00 -- Introduction

Topological sorting is used for **Directed Acyclic Graphs (DAGs)**.\
It gives a **linear ordering** of vertices such that for every directed
edge `u → v`, vertex `u` comes before `v` in the ordering.

------------------------------------------------------------------------

## ⏱ 00:39 -- Solving Topological Sort using DFS

**Idea:**\
- Use DFS to visit nodes.\
- After exploring all neighbors, push the node into a **stack**.\
- Reverse the stack to get the topological order.

### Code -- Topological Sort (DFS)

``` cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[node] = true;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, st);
        }
    }
    st.push(node); // push after visiting neighbors
}

vector<int> topoSortDFS(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    stack<int> st;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited, st);
        }
    }

    vector<int> topoOrder;
    while (!st.empty()) {
        topoOrder.push_back(st.top());
        st.pop();
    }
    return topoOrder;
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);

    // Directed edges
    adj[5] = {2, 0};
    adj[4] = {0, 1};
    adj[2] = {3};
    adj[3] = {1};

    vector<int> order = topoSortDFS(adj, V);

    cout << "Topological Sort (DFS): ";
    for (int node : order) cout << node << " ";
    cout << endl;
}
```

------------------------------------------------------------------------

## ⏱ 28:50 -- Time Complexity (DFS Approach)

-   **Time:** `O(V + E)`\
-   **Space:** `O(V)` (visited + recursion stack).

------------------------------------------------------------------------

## ⏱ 36:55 -- Solving Topological Sort using BFS (Kahn's Algorithm)

**Idea (Kahn's Algorithm):**\
- Calculate **in-degree** (number of incoming edges) of all nodes.\
- Push all nodes with in-degree `0` into a queue.\
- Pop nodes from the queue, add to topological order, and reduce
in-degree of neighbors.\
- If in-degree becomes `0`, push into queue.

### Code -- Topological Sort (BFS / Kahn's Algorithm)

``` cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> topoSortBFS(vector<vector<int>>& adj, int V) {
    vector<int> inDegree(V, 0);
    for (int i = 0; i < V; i++) {
        for (int neighbor : adj[i]) {
            inDegree[neighbor]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) q.push(i);
    }

    vector<int> topoOrder;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);

        for (int neighbor : adj[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) q.push(neighbor);
        }
    }
    return topoOrder;
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);

    // Directed edges
    adj[5] = {2, 0};
    adj[4] = {0, 1};
    adj[2] = {3};
    adj[3] = {1};

    vector<int> order = topoSortBFS(adj, V);

    cout << "Topological Sort (BFS - Kahn's Algorithm): ";
    for (int node : order) cout << node << " ";
    cout << endl;
}
```

------------------------------------------------------------------------

## ⏱ 46:51 -- Time Complexity (BFS Approach)

-   **Time:** `O(V + E)`\
-   **Space:** `O(V)` (in-degree array + queue).

------------------------------------------------------------------------

## ⏱ 54:19 -- Last Note

### 🔑 Key Takeaways

-   Topological sort only works on **DAGs**.\
-   DFS method uses **post-order stack**.\
-   BFS (Kahn's Algorithm) uses **in-degree + queue**.\
-   Both run in `O(V + E)` time.
