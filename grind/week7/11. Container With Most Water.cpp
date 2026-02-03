#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:

    int maxArea(vector<int>& height) {
        int mx = INT_MIN;
        int left =0;
        int right = height.size()-1;
        while(left<right){
            int water  = (right - left) * min(height[left], height[right]);
                mx =max(water, mx);
            
            if(height[left]< height[right]){
                left++;
            }else{
                right--;
            }
        }
    return mx;
    }


};
