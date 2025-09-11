/*

https://www.geeksforgeeks.org/problems/-minimum-number-of-coins4426/1

Given an infinite supply of each denomination of Indian currency { 1, 2, 5, 10 } and a target value n.
Find the minimum number of coins and/or notes needed to make the change for Rs n.

Examples:

Input: n = 39
Output: 6
Explaination: 39 can be formed using 3 coins of 10 rupees, 1 coin of 5 rupees and 2 coins of 2 rupees so minimum coins required are 6.
Input: n = 121
Output: 13

Explaination: 121 can be formed using 12 coins of 10 rupees and 1 coin of 1 rupees.
Constraints:
1 ≤ n ≤ 106
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
    int findMin(int n)
    {
        vector<int> currency = {1,2,5,10};
        int count= 0;
        for (int i = currency.size()-1; i >= 0; i--)
        {
            if(n>=currency[i])
            {
               count += n / currency[i];
               n %= currency[i];
            }
        }
        return count;
    }
};