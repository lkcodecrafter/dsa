#include <bits/stdc++.h>
using namespace std;

//https://www.youtube.com/watch?v=ZXANlaEuYvQ


class Solution {
public:

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n==1){
            return {0};
        }
        vector<int> indegree(n, 0);
        vector<vector<int>> adj(n);
        vector<int> res;
        queue<int> q;
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            indegree[u]++;
            indegree[v]++;
        }

        for (int i = 0; i < n; i++) {
            if (indegree[i] == 1) {
                q.push(i);
            }
        }

        int remaining = n;
        while (remaining > 2) {
            int size = q.size();
            remaining -= size;
            for (int i = 0; i < size; i++) {
                int node = q.front();
                q.pop();
                for (auto& n : adj[node]) {
                    indegree[n]--;
                    if (indegree[n] == 1) {
                        q.push(n);
                    }
                }
            }
        }

        while (!q.empty()) {
            res.push_back(q.front());
            q.pop();
        }

        return res;
    }
};