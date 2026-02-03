#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>>list;
        vector<int>current;
        solve(nums,list, current,0);
        return list;
    }
    void solve(vector<int>& nums, vector<vector<int>>& list, vector<int>& current, int index){
        list.push_back(current);
        for(int i=index;i<nums.size();i++){
            current.push_back(nums[i]);
            solve(nums, list, current, i+1);
            current.pop_back();
        }
    }
};