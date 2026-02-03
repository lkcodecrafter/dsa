#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        int idx = 0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(dfs( board, m,n,i,j,word, idx )){
                    return true;
                }
            }
        }
        return false;
 
    }

    private:
    bool dfs(vector<vector<char>>& board,int m, int n, int i, int j,  string& word, int idx){
        if(idx == word.length()){
            return true;
        }
        if(i < 0 || j < 0 || i>=m || j >= n || board[i][j]!=word[idx]){
            return false;
        }

        char temp = board[i][j];
        board[i][j] ='#';

        bool found = dfs(board, m,n,i+1,j,word, idx+1) || 
        dfs(board, m,n,i-1,j,word, idx +1) || 
        dfs(board, m,n,i,j+1,word, idx +1) ||
        dfs(board, m,n,i,j-1,word, idx+1);

        board[i][j]=temp;

        return found;
    }
};