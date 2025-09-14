#include <iostream>
#include <vector>
using namespace std;

// Adjacency Matrix Representation
// Weighted and Undirected Graph
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
        adjMatrix[v][u] = weight; // For undirected graph
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
// Input: 5 6
// 0 1 4
// 0 2 10
// 1 2 7 
// 1 3 8
// 3 4
// 4
// Output:
// 0 4 10 0 0
// 4 0 7 8 0
// 10 7 0 0 0
// 0 8 0 0 1
// 0 0 0 1 0
// Adjacency List Representation
// Weighted and Undirected Graph
// Space Complexity: O(V + E)
// Note: In adjacency list we can store only the edges which are present in the graph
// but in adjacency matrix we have to store all the edges including the edges which are not present in the graph
// so in sparse graph adjacency list is better than adjacency matrix
// but in dense graph adjacency matrix is better than adjacency list
// because in dense graph E is close to V^2
// and in sparse graph E << V^2
// so in dense graph adjacency matrix will take O(V^2) space
// and in sparse graph adjacency list will take O(V + E) space
// so in dense graph adjacency matrix is better than adjacency list
