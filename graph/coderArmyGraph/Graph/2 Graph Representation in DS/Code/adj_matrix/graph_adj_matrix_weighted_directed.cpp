#include <iostream>
#include <vector>
using namespace std;

// Adjacency Matrix Representation
// Unweighted and Directed Graph
// Space Complexity: O(V^2)
// Note: In adjacency matrix we can store only the edges which are present in the graph
// but in adjacency matrix we have to store all the edges including the edges which are not present in the graph
// so in sparse graph adjacency list is better than adjacency matrix
// but in dense graph adjacency matrix is better than adjacency list
// because in dense graph E is close to V^2
// and in sparse graph E << V^2
// so in dense graph adjacency matrix will take O(V^2) space
// and in sparse graph adjacency list will take O(V + E) space
// so in dense graph adjacency matrix is better than adjacency list
// Weighted and Directed Graph
// Space Complexity: O(V^2)
int main(int argc, char const *argv[])
{
    int vectices, edges;
    cin >> vectices >> edges;
    vector<vector<int>> adjMatrix(vectices, vector<int>(vectices, 0));
    int u, v, weight;
    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v >> weight; // 0 to 1 edge
        adjMatrix[u][v] = weight;
        // adjMatrix[v][u] = weight; // For undirected graph
    }
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
