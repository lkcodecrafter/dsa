#include<iostream>
#include<queue>
#include <functional>
using namespace std;

// https://www.youtube.com/watch?v=bfKwLi6jtDk&list=PLpIkg8OmuX-KJPC18SGiRUzJQAYo839ox&index=17

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