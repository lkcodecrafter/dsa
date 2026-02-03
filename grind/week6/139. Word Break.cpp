#include<iostream>
#include<unordered_set>
#include<vector>
#include<string>
#include <cstring>
 
using namespace std;

// https://www.youtube.com/watch?v=oBUpyPZ08zU

class Solution {
public:
    unordered_set<string>st;
    int dp[301];
    bool solve(string& s, int idx, int n){
        if(n==idx){
            return true;
        }
        if(dp[idx]!=-1){
            return dp[idx];
        }
        if(st.find(s)!=st.end()){
            return dp[idx]=true;
        }

        for(int l = 1;l<n;l++){
            string temp = s.substr(idx, l);
            if(st.find(temp)!=st.end() && solve(s, idx+l , n)){
                return dp[idx]=true;
            }
            
        }
    return dp[idx]=false;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.length();
        memset(dp, -1, sizeof(dp));
        for(string& word : wordDict){
            st.insert(word);
        }
        return solve(s,0,n);
    }
};