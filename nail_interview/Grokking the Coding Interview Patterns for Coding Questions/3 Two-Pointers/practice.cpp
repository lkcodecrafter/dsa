#include <iostream>
#include <vector>
using namespace std;

vector<int> sortedSquares(vector<int> &nums)
{
    int l = 0, r = nums.size() - 1;
    int k = r;
    vector<int> result(nums.size());
    while (l <= r)
    {
        if (abs(nums[l]) > abs(nums[r]))
        {
            result[k--] = nums[l] * nums[l];
            l++;
        }
        else
        {
            result[k--] = nums[r] * nums[r];
            r--;
        }
    }
    return result;
}

// move zeroes
//  [0,0,1,0,1]

void printArray(vector<int> &result)
{
    for (auto x : result)
    {
        cout << x << " ";
    }
}

void moveZeroes(vector<int> &nums)
{
    int n = nums.size();
    int i = 0, pos = 0;

    for (int i = 0; i < n; i++)
    {
        if (nums[i] != 0)
        {
            nums[pos] = nums[i];
            pos++;
        }
    }

    // while(pos<n){
    //     nums[pos++]=0;
    // }

    printArray(nums);
}

int main()
{
    vector<int> num = {-7, -3, 2, 3, 11};
    vector<int> result = sortedSquares(num);

    for (auto x : result)
    {
        cout << x << " ";
    }

    cout << "Move Zeroes ---> ";
    vector<int> zeroes = {0, 0, 1, 0, 1};
    moveZeroes(zeroes);
}