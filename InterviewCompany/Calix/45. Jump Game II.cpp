#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int jump = 0;
        int furthest = 0;
        int end = 0;
        for(int i=0;i<nums.size()-1;i++){
            furthest = max(furthest, i+ nums[i]);

            if(i==end){
                jump++;
                end = furthest;
            }
        }
        return jump;
    }
};