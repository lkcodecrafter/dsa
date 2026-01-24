#include<iostream>
#include<vector>
using namespace std;


// Input: nums = [3,1,-2,-5,2,-4]
// Output: [3,-2,1,-5,2,-4]
vector<int> rearrangeArray(vector<int>& nums) {

    int size = nums.size();
    int posIndex = 0;
    int negIndex =1;

    vector<int>result(size,0);
    for(int i=0;i<size;i++){
        if(nums[i]>0){
            result[posIndex]=nums[i];
            posIndex+=2;
        }else{
            result[negIndex]=nums[i];
            negIndex+=2;
        }
    }

    for(int i=0;i<result.size();i++){
        cout<<result[i] << " ";
    }
    return result;
}

    int pivotIndex(vector<int>& nums) {
        int result =0;
        int leftSum=0;
        int rightSum = 0;
        for(int &n : nums){
            rightSum+=n;
        }
        for(int i=0;i<nums.size();i++){
            rightSum -= nums[i];

            if(leftSum == rightSum){
                return i;
            }
            leftSum += nums[i];
        }
        return -1;
    }


int main(int argc, char const *argv[])
{
    vector<int>nums={3,1,-2,-5,2,-4};
    rearrangeArray(nums);

    return 0;
}
