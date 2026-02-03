#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:

/*
    bool solve(vector<int>& nums, int x, int i) {
        if (x == 0) {
            return true;
        }
        if(i>=nums.size()){
            return false;
        }
        bool take = false;
        if (x >= nums[i]) {
            take = solve(nums, x - nums[i], i + 1);
        }
        bool not_take = solve(nums, x, i + 1);

        return take || not_take;
    }
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++)
            sum += nums[i]; 
        if (sum % 2 != 0) { return false; }
        int x = sum / 2;
        return solve(nums, x, 0);
    }
*/

    // using memoization
    bool solve(vector<int>& nums, int x, int i, vector<vector<int>>& dp) {
        if (x == 0) {
            return true;
        }

        if (i >= nums.size()) {
            return false;
        }
        if (dp[i][x] != -1) {
            return dp[i][x];
        }
        bool take = false;
        if (x >= nums[i]) {
            take = solve(nums, x - nums[i], i + 1, dp);
        }
        bool not_take = solve(nums, x, i + 1, dp);

        return dp[i][x] = take || not_take;
    }
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++)
            sum += nums[i];
        if (sum % 2 != 0) {
            return false;
        }
        int x = sum / 2;
        vector<vector<int>> dp(n, vector<int>(x + 1, -1));
        return solve(nums, x, 0, dp);
    }

};