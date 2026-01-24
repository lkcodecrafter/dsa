#include <iostream>
#include <vector>
using namespace std;

// Adjacency Matrix Representation
// Undirected and Weighted Graph
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
int main(int argc, char const *argv[])
{
    int vectices, edges;
    cin >> vectices >> edges;
    vector<pair<int, int>> adjList[vectices]; // array of vectors
    int u, v, weight;
    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v >> weight; // 0 to 1 edge
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // For undirected graph
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
Input: 5 6
0 1 10
0 2 5
1 2 9
1 3 8
3 4 11
2 4 5
0 -> (1, 10) (2, 5) 
1 -> (0, 10) (2, 9) (3, 8)
2 -> (0, 5) (1, 9) (4, 5)
3 -> (1, 8) (4, 11)
4 -> (3, 11) (2, 5)
*/