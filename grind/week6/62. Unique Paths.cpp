#include<iostream>
#include<vector>
using namespace std;

// question link: https://leetcode.com/problems/unique-paths/

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> memo(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                memo[i][j] = memo[i - 1][j] + memo[i][j - 1];
            }
        }

        return memo[m - 1][n - 1];
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

dry run with m=3 and n=2 
Grid:
Start 
   →    _ 
   ↓     ↓ 
   _  → End

DP Table Filling:   
dp =
1 1
1 2
1 3
Answer = dp[2][1] = 3
n = 2 and m = 3 → 3 unique paths.
dp size is m x n because we are using 2D vector and we are filling the dp table based on the value of m and n.
is it coorect 
vector<vector<int>>memo(m, vector<int>(n, 1)); ?
Yes, the line `vector<vector<int>>memo(m, vector<int>(n, 1));` initializes a 2D vector (or matrix) called `memo` with dimensions `m x n`, where each element is initialized to `1`.
but dp size is also 2? ??


ime Complexity
O(m×n)
Space Complexity
O(m×n)

The recurrence relation is:

dp[i][j]=dp[i−1][j]+dp[i][j−1]

because each cell can only be reached from:

top
left

*/