/*
You are given an inclusive range [lower, upper] and a sorted unique integer array nums, where all elements are within the inclusive range.

A number x is considered missing if x is in the range [lower, upper] and x is not in nums.

Return the shortest sorted list of ranges that exactly covers all the missing numbers. That is, no element of nums is included in any of the ranges, and each missing number is covered by one of the ranges.
*/
#include<stdlib.h>
#include<iostream>
#include<vector>

using namespace std;


class Solution {
public:
    void solve(vector<int>& candidates, int target, vector<vector<int>>& result,
               int idx, vector<int> curr) {
        if (target < 0) {
            return;
        }
        if (target == 0) {
            result.push_back(curr);
            return;
        }
        for (int i = idx; i < candidates.size(); i++) {
            curr.push_back(candidates[i]);
            solve(candidates, target - candidates[i], result, i, curr);
            curr.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> curr;
        solve(candidates, target, result, 0, curr);
        return result;
    }
};

int main() {    
    return 0;
}