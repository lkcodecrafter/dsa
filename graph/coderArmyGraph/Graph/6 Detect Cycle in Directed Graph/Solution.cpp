#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool detectCycleDfs(int node, vector<vector<int>> &adj, vector<bool> &visisted, vector<bool> &recStack)
{
    visisted[node] = true;
    recStack[node] = true;
    for (int i : adj[node])
    {
        if (!visisted[i] && detectCycleDfs(i, adj, visisted, recStack))
        {
            return true;
        }
        else if (recStack[i])
        {
            return true; // cycle detected if present in stack
        }
    }
    recStack[node] = false;
    return false;
}

bool hasCycleDFS(vector<vector<int>> &adj, int V)
{
    vector<bool> visisted(V, 0);
    vector<bool> recStack(V, 0);
    for (int i = 0; i < V; i++)
    {
        if (!visisted[i])
        {
            detectCycleDfs(i, adj, visisted, recStack);
            return true;
        }
    }
    return false;
}

bool hasCycleBFS(vector<vector<int>> &adj, int V)
{
    /*
    Compute in-degree of each node.
    Use BFS to remove nodes with in-degree 0.
    If after BFS, some nodes are left → cycle exists.
    */
    vector<int> inDegree(V, 0);
    for (int i = 0; i < V; i++)
    {
        for (int neighbour : adj[i])
            inDegree[neighbour]++;
    }
    
    queue<int> q;
    int count = 0;
    for (int i = 0; i < V; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        count++;
        for(int neighbour : adj[node]){
            inDegree[neighbour]--;
            if(inDegree[neighbour]==0)
            q.push(neighbour);
        }
    }
    return (count!=V);
}

int main()
{
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

    
    if (hasCycleBFS(adj, V))
        cout << "Cycle detected using BFS (Kahn's Algorithm)" << endl;
    else
        cout << "No cycle (BFS)" << endl;    
}
/*
Context

We are running DFS, and we use two arrays:
visited[node] → tells us if a node has ever been visited in any DFS run.
Once visited, it stays true permanently.
recStack[node] → tells us if a node is part of the current DFS recursion path (active stack).

This is what helps us detect cycles.

That line:
else if (recStack[neighbor]) {
    return true; // Found cycle
}


This happens when:
The neighbor is already visited.
And it is still present in the current recursion stack.

👉 Meaning:
We are trying to visit a node that is already in our current DFS path.
This indicates a back edge → which means cycle exists in a directed graph.

Example Walkthrough (your graph)
0 → 1 → 2 → 3
    ↑       |
    └───────┘
Dry run:

Start DFS(0)
visited[0] = true, recStack[0] = true

DFS(1)
visited[1] = true, recStack[1] = true

DFS(2)
visited[2] = true, recStack[2] = true

DFS(3)
visited[3] = true, recStack[3] = true

From node 3, go to neighbor = 1

visited[1] = true already ✅

recStack[1] = true → means node 1 is still in current DFS path!

Boom 💥 → cycle detected.

Why do we need this check?

If we only checked visited[neighbor], we might falsely think every edge to a visited node is a cycle (which is wrong).
The key idea:

A back edge to a node in recursion stack = cycle
An edge to a visited node that is not in recursion stack = safe (not a cycle)

👉 So, this line:

else if (recStack[neighbor])

is specifically detecting a back edge in a DFS tree, which is the definition of a cycle in directed graphs.

That line
if (!visited[neighbor] && dfsCycle(neighbor, adj, visited, recStack)) {
    return true;
}

👉 Meaning:

!visited[neighbor] → If the neighbor hasn’t been visited yet, go deeper with DFS.
dfsCycle(neighbor, adj, visited, recStack) → Run DFS recursively from that neighbor.
If that DFS call finds a cycle (returns true), we immediately return true all the way up.

💡 Think of it like delegating the search:

"I haven’t visited my neighbor. Let me explore its entire path. If the neighbor’s DFS reports a cycle, I also report a cycle."

Why we backtrack

At the end of the function:

recStack[node] = false; // backtrack
When we enter a node in DFS, we mark:

visited[node] = true;
recStack[node] = true;   // "I’m in the current recursion path"

After exploring all neighbors, we remove the node from the recursion path:
recStack[node] = false;

Why is this needed?

Imagine DFS as walking down a path in a maze:
recStack = the footprints on your current path.
If you reach a function and see your own footprints again → cycle!
But once you backtrack (return from recursion), you erase the footprints because you’re no longer on that path.
If we don’t backtrack (recStack[node] = false), nodes would stay forever marked as "on path", and every future edge to them would look
like a cycle (false positives).

Dry Run on Your Graph
Graph:

0 → 1 → 2 → 3 → 1  (cycle)


DFS(0): mark recStack[0] = true

DFS(1): mark recStack[1] = true

DFS(2): mark recStack[2] = true

DFS(3): mark recStack[3] = true

Neighbor = 1 → already recStack[1] = true → cycle ✅

When DFS(3) finishes, it sets recStack[3] = false (backtracking).
Then DFS(2) sets recStack[2] = false, and so on.
This ensures only the current call stack is marked.

🔑 Summary:

if (!visited[neighbor] && dfsCycle(...)) return true;
→ Explore new neighbors, propagate cycle detection up the recursion.

recStack[node] = false; // backtrack
→ Remove node from recursion path once done, so future DFS calls aren’t confused.

*/
