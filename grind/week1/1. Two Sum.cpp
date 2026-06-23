#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

/*
Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

i -> 0 -> 2
9-2 = 7

i -> 1 -> 7
9-7 = 2

[,0]


mp{ {2,0},
    {}   }

*/

class Solution {
public:

    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>mp;
		for(int i=0;i<nums.size();i++){
			int x = target - nums[i];
			if(mp.find(x)!=mp.end()){
				return  {mp[x], i};
			}
			mp[nums[i]]=i;
		}
        return {-1,-1};
    }

};