#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
DFS (Depth First Search):
Goes as deep as possible along one path before backtracking.
Uses a stack or recursion.
Time Complexity: O(V + E)
Space Complexity: O(V) for the recursion stack or explicit stack.
📝 Dry Run (Graph edges: 0–1, 0–2, 1–3, 2–4)
Start at 0 → go to 1 → go to 3 → backtrack to 1 → backtrack to 0 → go to 2 → go to 4
✅ Output: 0 1 3 2 4
DFS Real Life Applications
Pathfinding and maze solving.
Topological sorting.
Cycle detection in graphs.

Dry Run
Start at 0 → go to 1 → go to 3 → backtrack
From 0 → go to 2 → go to 4 → backtrack
✅ Output: 0 1 3 2 4

*/

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

// Method 2: By using Stack.
vector<int> dfsOfGraph(int V, vector<int> adj[])
{
    // Code here
    vector<bool> visited(V, 0);
    vector<int> ans;
    stack<int> s;
    s.push(0);

    int node;
    while (!s.empty())
    {
        node = s.top();
        s.pop();
        if (!visited[node])
        {
            visited[node] = 1;
            ans.push_back(node);
            for (int i = adj[node].size() - 1; i >= 0; i--)
            {
                s.push(adj[node][i]);
            }
        }
    }
    return ans;
}

int main() {
    int V = 5; 
    vector<vector<int>> adj(V);

    // Undirected graph edges
    adj[0] = {1, 2};
    adj[1] = {0, 3};
    adj[2] = {0, 4};
    adj[3] = {1};
    adj[4] = {2};

    vector<bool> visited(V, false);
    cout << "DFS Traversal: ";
    dfs(0, adj, visited);
}
