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
            if(st.find(temp)!=st.end() && solve(s, idx+l , n)){ // if temp is found in st and the remaining string can be segmented then we can say that the current string can also be segmented
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

// short dry run
// s="leetcode", wordDict=["leet","code"]
// st={"leet","code"}
// solve("leetcode", 0, 8)
// idx=0, n=8
// temp="l", not found in st
// temp="le", not found in st   
// temp="lee", not found in st
// temp="leet", found in st and solve("leetcode", 4, 8)
// idx=4, n=8
// temp="c", not found in st
// temp="co", not found in st
// temp="cod", not found in st  
// temp="code", found in st and solve("leetcode", 8, 8)
// idx=8, n=8, return true
// return true for idx=4 and then return true for idx=0
