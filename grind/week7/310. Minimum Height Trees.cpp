#include <bits/stdc++.h>
using namespace std;

//https://www.youtube.com/watch?v=ZXANlaEuYvQ


class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n==1) return {0};

        vector<int>adj[n];
        vector<int>indegree(n,0);

        for(auto&e: edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            indegree[e[0]]++;
            indegree[e[1]]++;
        }

        queue<int>q;
        for(int i=0;i<n;i++){
            if(indegree[i]==1){
                q.push(i);
            }
        }

        int remainingNodes = n;
        while(remainingNodes > 2){
            int sz = q.size();
            remainingNodes -= sz;

            for(int i=0;i<sz;i++){
                int node = q.front();
                q.pop();

                for(auto&neighbor: adj[node]){
                    indegree[neighbor]--;
                    if(indegree[neighbor]==1){
                        q.push(neighbor);
                    }
                }
            }
        }

        vector<int>res;
        while(!q.empty()){
            res.push_back(q.front());
            q.pop();
        }

        return res;
    }
};