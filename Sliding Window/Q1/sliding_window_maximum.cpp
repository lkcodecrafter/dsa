#include<iostream>
#include<vector>
#include<deque>

using namespace std;

vector<int>maxSlidingWindow(vector<int>& nums, int k){
    deque<int>q;
    vector<int>result;
    for(int index =0;index<k;index++){
        int element = nums[index];

        while(!q.empty() && element > nums[q.back()]){
            q.pop_back();
        }
        q.push_back(index);
    }

    // Reprocess Window
    for(int index = k;index<nums.size();index++){
        result.push_back(nums[q.front()]);

        while(!q.empty() && index - q.front() >= k){
            q.pop_front();
        }
        while(!q.empty() && nums[index]> nums[q.back()]){
            q.pop_back();
        }
        q.push_back(index);
    }
    result.push_back(nums[q.front()]);
    return result;
}
int main(int argc, char const *argv[])
{
    /* code */
    vector<int>nums = {1,3,-1,-3,5,3,6,7 };
    int k =3;
    vector<int>ans =  maxSlidingWindow(nums, k);

    for(auto s : ans){
        cout<<s<< " ";
    }
    
    return 0;
}
