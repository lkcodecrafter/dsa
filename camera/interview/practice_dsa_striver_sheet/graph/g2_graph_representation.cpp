#include <iostream>
#include <vector>

using namespace std;

// 1. Adjacency Matrix Representation
// Space Complexity: O(N * N)
// Time Complexity to take input: O(M)
void adjacencyMatrixRepresentation() {
    int n, m;
    cin >> n >> m; // n: nodes, m: edges

    // 1-based indexing
    // If n = 5, matrix will be 6x6 (from 0 to 5)
    // Initialize matrix with 0
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u][v] = 1;
        adj[v][u] = 1; // Omit this line for a directed graph
    }
}

// 2. Adjacency List Representation
// Space Complexity: O(N + 2M) for undirected, O(N + M) for directed
// Time Complexity to take input: O(M)
void adjacencyListRepresentation() {
    int n, m;
    cin >> n >> m; // n: nodes, m: edges

    // 1-based indexing
    // Array of vectors
    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        // u -> v edge
        adj[u].push_back(v);
        // v -> u edge (Omit this for a directed graph)
        adj[v].push_back(u);
    }
}

// Note on Weighted Graph Representation:
// For adjacency matrix, store weight instead of 1: adj[u][v] = weight;
// For adjacency list, use vector of pairs: vector<pair<int, int>> adj[n + 1];
// Inside the loop:
// int u, v, wt;
// cin >> u >> v >> wt;
// adj[u].push_back({v, wt});
// adj[v].push_back({u, wt});

int main() {
    // You can call either representation here based on requirement
    // adjacencyMatrixRepresentation();
    adjacencyListRepresentation();
    return 0;
}
