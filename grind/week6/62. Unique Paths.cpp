#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>>memo(n, vector<int>(n, 1));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                memo[i][j]=memo[i-1][j]+ memo[i][j-1];
            }
        }     
        return memo[m-1][n-1];
    }
};

/*

🔎 Dry Run Example
Input:


m = 3, n = 3
Grid:


Start → _ → _
   ↓     ↓   ↓
   _ → _ → End


DP Table Filling:


dp =
1 1 1
1 2 3
1 3 6
Answer = dp[2][2] = 6

🎯 Final Answer
For a 3x3 grid → 6 unique paths.

*/