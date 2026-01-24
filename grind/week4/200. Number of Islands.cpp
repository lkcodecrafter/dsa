#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int count =0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='1'){
                    count++;
                    dfs(grid, i,j, m,n);
                }
            }
        }

        return count;
    }

    void dfs(vector<vector<char>>& grid, int i, int j, int m, int n){
        if(i<0 || j<0 || i>=m || j>=n || grid[i][j]=='0'){ // grid[i][j]=='0' means water or visited
            return;
        }
        grid[i][j]='0'; // mark as visited
        dfs(grid, i+1, j,m,n);
        dfs(grid, i-1, j,m,n);
        dfs(grid, i, j+1,m,n);
        dfs(grid, i, j-1,m,n);

    }
};