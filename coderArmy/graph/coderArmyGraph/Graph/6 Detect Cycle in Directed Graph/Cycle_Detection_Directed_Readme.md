# Cycle Detection in Directed Graph (C++)

## ⏱ 00:00 – Introduction
Detecting cycles in **directed graphs** is important for:  
- Detecting deadlocks.  
- Validating dependency graphs.  
- Ensuring a graph is a DAG (for topological sort).  

---

## ⏱ 00:56 – Method 1: Cycle Detection using DFS

**Idea:**  
- Maintain two arrays:  
  - `visited[]`: marks if a node has been visited.  
  - `recStack[]`: keeps track of the current recursion path.  
- If a node is visited **and** in the recursion stack → cycle detected.  

### Code – DFS Cycle Detection (Directed Graph)
```cpp
#include <iostream>
#include <vector>
using namespace std;

bool dfsCycle(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& recStack) {
    visited[node] = true;
    recStack[node] = true;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor] && dfsCycle(neighbor, adj, visited, recStack)) {
            return true;
        }
        else if (recStack[neighbor]) {
            return true; // Found cycle
        }
    }

    recStack[node] = false; // backtrack
    return false;
}

bool hasCycleDFS(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfsCycle(i, adj, visited, recStack)) return true;
        }
    }
    return false;
}

int main() {
    int V = 4;
    vector<vector<int>> adj(V);

    // Directed edges
    adj[0] = {1};
    adj[1] = {2};
    adj[2] = {3};
    adj[3] = {1}; // cycle

    if (hasCycleDFS(adj, V))
        cout << "Cycle detected using DFS" << endl;
    else
        cout << "No cycle (DFS)" << endl;
}
```

---

## ⏱ 50:19 – Time and Space Complexity (DFS)
- **Time:** `O(V + E)`  
- **Space:** `O(V)` (visited + recursion stack).  

---

## ⏱ 1:00:21 – Method 2: Cycle Detection using BFS (Kahn's Algorithm)

**Idea:**  
- Compute **in-degree** of each node.  
- Use BFS to remove nodes with in-degree `0`.  
- If after BFS, some nodes are left → cycle exists.  

### Code – BFS Cycle Detection (Directed Graph)
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool hasCycleBFS(vector<vector<int>>& adj, int V) {
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

    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;

        for (int neighbor : adj[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) q.push(neighbor);
        }
    }

    return count != V; // if not all nodes processed → cycle exists
}

int main() {
    int V = 4;
    vector<vector<int>> adj(V);

    // Directed edges
    adj[0] = {1};
    adj[1] = {2};
    adj[2] = {3};
    adj[3] = {1}; // cycle

    if (hasCycleBFS(adj, V))
        cout << "Cycle detected using BFS (Kahn's Algorithm)" << endl;
    else
        cout << "No cycle (BFS)" << endl;
}
```

---

## ⏱ 1:10:40 – Time and Space Complexity (BFS)
- **Time:** `O(V + E)`  
- **Space:** `O(V)` (in-degree array + queue).  

---

## ⏱ 1:16:02 – Last Note  

### 🔑 Key Takeaways  
- DFS detects cycle using **recursion stack**.  
- BFS detects cycle using **Kahn’s Algorithm (topological sort)**.  
- Both run in `O(V + E)`.  
- DFS is simpler for recursive solutions.  
- BFS is useful for topological sorting and level-wise graph analysis.  
