#include <iostream>
#include <vector>
using namespace std;

// Adjacency Matrix Representation
// Unweighted and Directed Graph
// Space Complexity: O(V^2)
// Note: In adjacency matrix we can store only the edges which are present in the graph
int main(int argc, char const *argv[])
{
    int vectices, edges;
    cin >> vectices >> edges;
    vector<int> adjList[vectices]; // array of vectors
    int u, v;
    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v; // 0 to 1 edge
        adjList[u].push_back(v);
        // adjList[v].push_back(u); // For undirected graph
    }

    for (int i = 0; i < vectices; i++)
    {
        cout << i << " -> ";
        for (auto vertex : adjList[i])
        {
            cout << vertex << " ";
        }
        cout << endl;
    }
    return 0;
}
