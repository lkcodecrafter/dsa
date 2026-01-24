#include <iostream>
#include <vector>
using namespace std;

// Adjacency list Representation
// Unweighted and Undirected Graph
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
    vector<int> adjList[vectices]; // array of vectors
    int u, v;
    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v; // 0 to 1 edge
        adjList[u].push_back(v);
        adjList[v].push_back(u); // For undirected graph
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

/* Input: 5 6
0 1 
1 2
0 2
1 3
3 4
2 3
0 -> 1 2 
1 -> 0 2 3
2 -> 1 0 3
3 -> 1 4 2
4 -> 3
*/