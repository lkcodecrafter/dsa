#include <iostream>
#include <vector>
using namespace std;
// Adjacency Matrix Representation
// Weighted and Directed Graph
// Space Complexity: O(V + E)
int main(int argc, char const *argv[])
{
    int vectices, edges;
    cin>> vectices >> edges;
    vector<pair<int,int>>adjList[vectices]; // array of vectors
    int u,v,weight;
    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v >> weight; // 0 to 1 edge
        adjList[u].push_back({v,weight});
        // adjList[v].push_back({u,weight}); // For undirected graph
    }

    for (int i = 0; i < vectices; i++)
    {
        cout << i << " -> ";
        for (auto vertex : adjList[i])
        {
            cout << "(" << vertex.first << ", " << vertex.second << ") ";
        }
        cout << endl;
    }
    return 0;
}


/*
📊 Comparing Adjacency Matrix vs Adjacency List
Feature	Adjacency Matrix	Adjacency List
Storage	O(V²)	O(V + E)
Edge Lookup	O(1)	O(degree of vertex)
Add Edge	O(1)	O(1) (amortized, if using vector)
Remove Edge	O(1)	O(degree of vertex)
Best for	Dense graphs (lots of edges)	Sparse graphs (few edges compared to V²)
Memory Usage	High (even if few edges exist)	Efficient (stores only existing edges)

👉 Rule of Thumb:

Use Adjacency Matrix when the graph is dense or when you need constant-time edge lookup.

Use Adjacency List when the graph is sparse or when memory efficiency matters.

🌳 Tree vs Graph

Tree

Special type of graph.

Connected and acyclic (no cycles).

If there are V vertices → it has exactly V - 1 edges.

Example: Family tree, file system hierarchy.

Graph

More general structure.

Can be connected or disconnected.

May contain cycles.

Edges can be directed/undirected, weighted/unweighted.

Visualization:

Tree (Acyclic)
      (0)
     /   \
   (1)   (2)
   / \
 (3) (4)

Graph (Can have cycles)
  (0) --- (1)
   |     /   \
   |    /     \
  (2) -------- (3)

*/