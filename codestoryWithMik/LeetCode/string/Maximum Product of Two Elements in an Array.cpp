#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:

    int maxProduct(vector<int>& nums) {
      int sum = 0;
      int first = nums[0];
      for (int  i = 1; i < nums.size(); i++)
      {
        sum=max(sum, (first-1)* (nums[i]-1));
        first=max(nums[i],first);
      }
    
      return sum;
    }
    
};




int main(){    
    Solution sol;
    vector<int>nums={3,4,5,2};
    sol.maxProduct(nums);
    return 0;
}