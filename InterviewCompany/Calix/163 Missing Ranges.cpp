/*
You are given an inclusive range [lower, upper] and a sorted unique integer array nums, where all elements are within the inclusive range.

A number x is considered missing if x is in the range [lower, upper] and x is not in nums.

Return the shortest sorted list of ranges that exactly covers all the missing numbers. That is, no element of nums is included in any of the ranges, and each missing number is covered by one of the ranges.
*/
#include<stdlib.h>
#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:


vector<vector<int>> missingRanges(vector<int> &arr, int lower, int upper) {
    int n = arr.size();
    vector<vector<int>> res;

    // Case: empty array
    if (n == 0) {
        res.push_back({lower, upper});
        return result;
    }

    // Check for missing range before the first element
    if (lower < arr[0])
        res.push_back({lower, arr[0] - 1});

    // Check for missing ranges between consecutive elements
    for (int i = 0; i < n - 1; ++i)
        if (arr[i + 1] - arr[i] > 1)
            res.push_back({arr[i] + 1, arr[i + 1] - 1});

    // Check for missing range after the last element
    if (n > 0 && upper > arr[n - 1])
        res.push_back({arr[n - 1] + 1, upper});

    return res;
}
};

int main() {
    int lower = 10, upper = 50;
    vector<int> arr{14, 15, 20, 30, 31, 45};
    Solution sol;
    vector<vector<int>> res = sol.missingRanges(arr, lower, upper);
    for (const vector<int> &v : res)
        cout << v[0] << " " << v[1] << endl;
    return 0;
}