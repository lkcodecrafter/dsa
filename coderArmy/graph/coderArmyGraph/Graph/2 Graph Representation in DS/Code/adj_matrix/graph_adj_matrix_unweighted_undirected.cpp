#include <iostream>
#include <vector>
using namespace std;

// Adjacency Matrix Representation
// Unweighted and Undirected Graph
// Space Complexity: O(V^2)
int main(int argc, char const *argv[])
{
    int vectices, edges;
    cin >> vectices >> edges;
    vector<vector<bool>> adjMatrix(vectices, vector<bool>(vectices, 0));

    int u, v;

    // why edges and not vectices because in adjacency matrix we have to fill the edges only
    // vectices are already initialized with 0
    // if we take vectices then it will take O(V^2) time complexity
    // but if we take edges then it will take O(E) time complexity
    // and in sparse graph E << V^2
    // and in dense graph E is close to V^2
    // so in both cases it is better to take edges
    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v; // 0 to 1 edge
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // For undirected graph
    }

    // pri
    for (int i = 0; i < vectices; i++)
    {
        for (int j = 0; j < vectices; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

// Input: 5 6
// 0 1
// 0 2
// 1 2
// 1 3
// 2 4
// 3 4
// Output:
// 0 1 1 0 0
// 1 0 1 1 0
// 1 1 0 0 1
// 0 1 0 0 1
// 0 0 1 1 0
// Adjacency List Representation
// Unweighted and Undirected Graph
// Space Complexity: O(V + E)

