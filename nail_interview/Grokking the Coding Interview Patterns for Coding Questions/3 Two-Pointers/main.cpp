#include<iostream>
#include<vector>
using namespace std;

/*## 2. Pair with Target Sum (Easy)

``` cpp
*/
vector<int> pairWithTargetSum(vector<int>& arr, int target) {
        int l =0,r = arr.size()-1;
        while(l<=r){
            int sum = arr[l]+ arr[r];
            if(sum==target){
                return {l, r};
            }else if(sum < target){
                l++;
            }else{
                r--;
            }
        }
        return {-1,1};
}

//## 3. Find Non-Duplicate Number Instances (Easy)

int singleNonDuplicate(vector<int>& nums) {
    int x=0;
    for(int n : nums){
        x^=n;
    }
    return x;
}


int main(int argc, char const *argv[])
{
    vector<int>arr={1,2,3,4,5,2};
    vector<int>result = pairWithTargetSum(arr, 1);
    for(int x : result){
        cout<<x << " ";
    }
    cout<<endl;

    vector<int>nums = {4, 1, 2, 1, 2};
    cout<<singleNonDuplicate(nums);
    return 0;
}
