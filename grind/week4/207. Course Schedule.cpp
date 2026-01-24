#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> adj(numCourses);
        for (auto &p : prerequisites) {
            adj[p[1]].push_back(p[0]); // p[1] -> p[0] means p[0] depends on p[1]
            indegree[p[0]]++;          // increase indegree of p[0] means p[0] has one more prerequisite
        }
        queue<int> q;
        for (int i = 0; i < numCourses; i++) 
            if (indegree[i] == 0) q.push(i);
        
        int count = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            count++;
            for (auto v : adj[u]) {
                if (--indegree[v] == 0) q.push(v);
            }
        }
        return count == numCourses;
    }
};