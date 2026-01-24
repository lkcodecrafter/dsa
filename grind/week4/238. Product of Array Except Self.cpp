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
};