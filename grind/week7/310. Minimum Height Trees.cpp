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
            indegree[u]++; // indegree of u is increased by 1
            indegree[v]++; // indegree of v is increased by 1 // final indegree value now as {0, 2, 2, 1, 1}
            // visualize the graph as 0--1--2--3 and 1--4, so indegree of 0 is 1, indegree of 1 is 2, indegree of 2 is 2, 
            // indegree of 3 is 1 and indegree of 4 is 1
            // visua of indegree is {1, 2, 2, 1, 1} how 
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