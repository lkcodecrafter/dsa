#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int>result(n,1);
        int left =1;
        int right =1;
        for(int i=0;i<n;i++){
            result[i]=left;
            left*=nums[i];
        }
        for(int  i=n-1;i>=0;i--){
            result[i]*=right;
            right*=nums[i];
        }

        return result;
    }

    // Time Complexity: O(n)
    // Space Complexity: O(1) (excluding output array)
    // dry run: nums = [1,2,3,4]
    // left = 1, right = 1, result = [1,1,1,1]
    // i=0: result[0] = left = 1, left = left * nums[0] = 1 * 1 = 1
    // i=1: result[1] = left = 1, left = left * nums[1] = 1 * 2 = 2
    // i=2: result[2] = left = 2, left = left * nums[2] = 2 * 3 = 6
    // i=3: result[3] = left = 6, left = left * nums[3] = 6 * 4 = 24
    // i=3: result[3] = result[3] * right = 6 * 1 = 6, right = right * nums[3] = 1 * 4 = 4
    // i=2: result[2] = result[2] * right = 2 * 4 = 8, right = right * nums[2] = 4 * 3 = 12
    // i=1: result[1] = result[1] * right = 1 * 12 = 12, right = right * nums[1] = 12 * 2 = 24
    // i=0: result[0] = result[0] * right = 1 * 24 = 24, right = right * nums[0] = 24 * 1 = 24
    // result = [24,12,8,6]

};