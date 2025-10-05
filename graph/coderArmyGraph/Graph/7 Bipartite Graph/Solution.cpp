#include <iostream>
#include <bits/stdc++.h>
using namespace std;

bool isBipartiteBFS(int V, vector<int> adj[])
{
    vector<int> color(V, -1);
    for (int start = 0; start < V; start++)
    {
        if (color[start] == -1)
        {
            queue<int> q;
            q.push(start);
            color[start] = 0;
            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                for (int neigh : adj[node])
                {
                    if (color[neigh] == -1)
                    {
                        color[neigh] = 1 - color[node];
                        q.push(neigh);
                    }
                    else if (color[neigh] == color[node])
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool dfs(int node, int col, vector<int> &color, vector<vector<int>> &adj)
{
    color[node] = col;
    for (int neigh : adj[node])
    {
        if (color[neigh] == -1)
        {
            if (!dfs(neigh, 1 - col, color, adj))
            {
                return false;
            }
        }
        else if (color[neigh] == col)
        {
            return false;
        }
    }
    return true;
}
bool isBipartite(vector<vector<int>> &graph)
{
    int V = graph.size();
    vector<int> color(V, -1);
    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1)
        {
            if (!dfs(i, 0, color, graph))
            {
                return false;
            }
        }
    }
    return true;
}
int main()
{
    int V, E;
    cin >> V >> E;
    vector<int> adj[V];
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (isBipartiteBFS(V, adj))
        cout << "Graph is Bipartite\n";
    else
        cout << "Graph is NOT Bipartite\n";
    return 0;
}