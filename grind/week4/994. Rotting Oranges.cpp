#include<iostream>
#include<queue>
using namespace std;


class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int fresh = 0;
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int,int>>q;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    fresh++;
                }else if(grid[i][j]==2){
                    q.push({i,j});
                }
            }
        }

        vector<pair<int,int>>dir = { 
            {1,0},{-1,0},{0,1},{0,-1}
        };
        int mint=0;
        while(!q.empty() && fresh > 0){
            int size = q.size();
            for(int k=0;k<size;k++){
            auto [i,j] = q.front();
            q.pop();

            for(auto d : dir){
                int ni = i+d.first;
                int nj = j+d.second;

                if(ni >= 0 && nj >= 0 &&  nj <n && ni <m && grid[ni][nj]==1){
                    grid[ni][nj]=2;
                    fresh--;
                    q.push({ni,nj});
                }
            }
            }
            mint++;
        }

        return fresh == 0 ? mint : -1;
    }
};
