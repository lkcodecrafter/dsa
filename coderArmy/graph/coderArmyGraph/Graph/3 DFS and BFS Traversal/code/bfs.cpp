#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
BFS (Breadth First Search):
Starts at a source node.
Visits all neighbors (level by level).
Uses a queue (FIFO).
Time Complexity: O(V + E)
Space Complexity: O(V) for the queue and visited array.

📝 Dry Run (Graph edges: 0–1, 0–2, 1–3, 2–4)

Start at 0 → visit neighbors → [1, 2]
Visit 1 → neighbor [3]
Visit 2 → neighbor [4]
Visit 3, 4 → done
✅ Output: 0 1 2 3 4

BFS Real Life Applications
Shortest path in unweighted graphs.
Web crawling (layer by layer).
Network broadcasting.
Social network friend suggestions (friends of friends).

*/

void bfs(int start, vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int V = 5; // vertices
    vector<vector<int>> adj(V);

    // Undirected graph edges
    adj[0] = {1, 2};
    adj[1] = {0, 3};
    adj[2] = {0, 4};
    adj[3] = {1};
    adj[4] = {2};

    cout << "BFS Traversal: ";
    bfs(0, adj, V);
}
