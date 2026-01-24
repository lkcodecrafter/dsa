# Graph Problems - BFS & DFS Applications

## 📌 Introduction
This sheet covers **important graph traversal problems** using BFS and DFS.  
We’ll solve three main problems and list some homework questions for practice.

---

## 🔹 Problem 1: Covid Spread
**Problem Link:** [Covid Spread - GFG](https://www.geeksforgeeks.org/problems/covid-spread--141631/1)  

We are given a grid with infected and uninfected people. The virus spreads to adjacent cells in 1 unit of time.  
We must calculate the **time taken for complete spread**.

### C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int helpaterp(vector<vector<int>> hospital) {
    int n = hospital.size(), m = hospital[0].size();
    queue<pair<int,int>> q;
    vector<vector<int>> vis(n, vector<int>(m, 0));
    
    // Push initially infected cells
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(hospital[i][j] == 2) {
                q.push({i,j});
                vis[i][j] = 1;
            }
        }
    }
    
    int time = -1;
    int dx[4] = {0,0,1,-1};
    int dy[4] = {1,-1,0,0};
    
    while(!q.empty()) {
        int size = q.size();
        time++;
        for(int k=0;k<size;k++) {
            auto [x,y] = q.front(); q.pop();
            for(int d=0; d<4; d++) {
                int nx = x+dx[d], ny = y+dy[d];
                if(nx>=0 && ny>=0 && nx<n && ny<m && !vis[nx][ny] && hospital[nx][ny]==1) {
                    hospital[nx][ny] = 2;
                    vis[nx][ny] = 1;
                    q.push({nx,ny});
                }
            }
        }
    }
    return time;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> hospital(n, vector<int>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>hospital[i][j];
    }
    cout<<helpaterp(hospital)<<endl;
}
```
⏱ **Time Complexity:** O(N*M)  
💾 **Space Complexity:** O(N*M)

---

## 🔹 Problem 2: Find the Number of Islands
**Problem Link:** [Number of Islands - GFG](https://www.geeksforgeeks.org/problem...)  

We are given a grid of 1s (land) and 0s (water). Count the number of connected islands.  
Connections can be **8-directional**.

### Method 1 - BFS
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void bfs(int i, int j, vector<vector<int>>& vis, vector<vector<char>>& grid) {
        int n=grid.size(), m=grid[0].size();
        queue<pair<int,int>> q;
        q.push({i,j});
        vis[i][j]=1;
        
        int dx[8] = {-1,-1,-1,0,0,1,1,1};
        int dy[8] = {-1,0,1,-1,1,-1,0,1};
        
        while(!q.empty()) {
            auto [x,y] = q.front(); q.pop();
            for(int d=0; d<8; d++) {
                int nx=x+dx[d], ny=y+dy[d];
                if(nx>=0 && ny>=0 && nx<n && ny<m && grid[nx][ny]=='1' && !vis[nx][ny]) {
                    vis[nx][ny]=1;
                    q.push({nx,ny});
                }
            }
        }
    }
    
    int numIslands(vector<vector<char>>& grid) {
        int n=grid.size(), m=grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m,0));
        int cnt=0;
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]=='1' && !vis[i][j]){
                    cnt++;
                    bfs(i,j,vis,grid);
                }
            }
        }
        return cnt;
    }
};
```

### Method 2 - DFS
```cpp
class Solution {
public:
    void dfs(int i, int j, vector<vector<int>>& vis, vector<vector<char>>& grid) {
        int n=grid.size(), m=grid[0].size();
        vis[i][j]=1;
        
        int dx[8] = {-1,-1,-1,0,0,1,1,1};
        int dy[8] = {-1,0,1,-1,1,-1,0,1};
        
        for(int d=0; d<8; d++) {
            int nx=i+dx[d], ny=j+dy[d];
            if(nx>=0 && ny>=0 && nx<n && ny<m && grid[nx][ny]=='1' && !vis[nx][ny]) {
                dfs(nx,ny,vis,grid);
            }
        }
    }
    
    int numIslands(vector<vector<char>>& grid) {
        int n=grid.size(), m=grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m,0));
        int cnt=0;
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]=='1' && !vis[i][j]){
                    cnt++;
                    dfs(i,j,vis,grid);
                }
            }
        }
        return cnt;
    }
};
```

⏱ **Time Complexity:** O(N*M)  
💾 **Space Complexity:** O(N*M)

---

## 🔹 Problem 3: Replace O’s with X’s
**Problem Link:** [Replace O’s with X’s - GFG](https://www.geeksforgeeks.org/problem...)  

We need to replace all 'O' with 'X' if they are not connected to boundary 'O'.

### C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    void dfs(int i, int j, vector<vector<char>>& mat, vector<vector<int>>& vis){
        int n=mat.size(), m=mat[0].size();
        vis[i][j]=1;
        
        int dx[4] = {0,0,1,-1};
        int dy[4] = {1,-1,0,0};
        
        for(int d=0; d<4; d++){
            int nx=i+dx[d], ny=j+dy[d];
            if(nx>=0 && ny>=0 && nx<n && ny<m && !vis[nx][ny] && mat[nx][ny]=='O'){
                dfs(nx,ny,mat,vis);
            }
        }
    }
    
    vector<vector<char>> fill(int n, int m, vector<vector<char>> mat){
        vector<vector<int>> vis(n, vector<int>(m,0));
        
        // Boundary O’s
        for(int i=0;i<n;i++){
            if(mat[i][0]=='O' && !vis[i][0]) dfs(i,0,mat,vis);
            if(mat[i][m-1]=='O' && !vis[i][m-1]) dfs(i,m-1,mat,vis);
        }
        for(int j=0;j<m;j++){
            if(mat[0][j]=='O' && !vis[0][j]) dfs(0,j,mat,vis);
            if(mat[n-1][j]=='O' && !vis[n-1][j]) dfs(n-1,j,mat,vis);
        }
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mat[i][j]=='O' && !vis[i][j]) mat[i][j]='X';
            }
        }
        return mat;
    }
};
```

⏱ **Time Complexity:** O(N*M)  
💾 **Space Complexity:** O(N*M)

---

## 📝 Homework Problems

1. [Rotten Oranges](https://www.geeksforgeeks.org/problem...)  
2. [X Total Shapes](https://www.geeksforgeeks.org/problem...)  
3. [Number of Provinces](https://www.geeksforgeeks.org/problem...)  

---

## 🎯 Last Note
- BFS is great for shortest time-based problems (Covid Spread, Rotten Oranges).  
- DFS is handy for connected components (Islands, Replace O’s with X’s).  
- Always track visited cells to avoid infinite recursion or re-processing.

