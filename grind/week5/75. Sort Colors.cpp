#include<iostream>
#include<vector>
 
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int i=0;
        int j =0;
        int k =nums.size()-1;
        while(j<=k){
            if(nums[j]==1){
                j++;
            }else if(nums[j]==2){
                swap(nums[j], nums[k]);
                k--;
            }else{
                swap(nums[j], nums[i]);
                j++;
                i++;
            }
        }
    }
};

// Dry Run with Visualization
// Example: nums = [2,0,2,1,1,0]
// Step 0: Initialize pointers
// i=0, j=0, k=5
// Step 1: j=0, nums[j]=2
// Swap nums[j] and nums[k]: [0,0,2,1,1,2]
// k=4
// Step 2: j=0, nums[j]=0
// Swap nums[j] and nums[i]: [0,0,2,1,1,2]
// i=1, j=1
// Step 3: j=1, nums[j]=0
// Swap nums[j] and nums[i]: [0,0,2,1,1,2]
// i=2, j=2
// Step 4: j=2, nums[j]=2
// Swap nums[j] and nums[k]: [0,0,1,1,2,2]
// k=3
// Step 5: j=2, nums[j]=1
// j=3, nums[j]=1
// j=4, nums[j]=2
// Final Result: [0,0,1,1,2,2]
