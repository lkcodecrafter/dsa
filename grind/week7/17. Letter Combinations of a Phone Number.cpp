#include<iostream>
#include<vector>
using namespace std;

 class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string>mapping={"","", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        string temp ="";
        vector<string>res;
        backtrack(digits, 0,temp, res, mapping);
    return res;
    }
    void backtrack(string& digits, int index, string temp, vector<string>& res, vector<string>& mapping){
        if(index == digits.size()){
            res.push_back(temp);
            return;
        }

        int k = digits[index] - '0';
        string& letters = mapping[k];
        for(char l : letters){
            temp.push_back(l);
            backtrack(digits, index+1, temp, res, mapping);
            temp.pop_back();
        }
        
    }
};
