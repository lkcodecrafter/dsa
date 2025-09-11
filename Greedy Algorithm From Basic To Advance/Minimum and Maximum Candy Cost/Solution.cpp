/*
 https://www.geeksforgeeks.org/problems/shop-in-candy-store1145/1

 In a candy store, there are different types of candies available and prices[i] represent the price of  ith types of candies. You are now provided with an attractive offer.
For every candy you buy from the store, you can get up to k other different candies for free. Find the minimum and maximum amount of money needed to buy all the candies.
Note: In both cases, you must take the maximum number of free candies possible during each purchase.

Examples :

Input: prices[] = [3, 2, 1, 4], k = 2
Output: [3, 7]
Explanation: As according to the offer if you buy one candy you can take at most k more for free. So in the first case, you buy the candy worth 1 and takes candies worth 3 and 4 for free, also you need to buy candy worth 2. So min cost: 1+2 = 3. In the second case, you can buy the candy worth 4 and takes candies worth 1 and 2 for free, also you need to buy candy worth 3. So max cost: 3+4 = 7.
Input: prices[] = [3, 2, 1, 4, 5], k = 4
Output: [1, 5]
Explanation: For minimimum cost buy the candy with the cost 1 and get all the other candies for free. For maximum cost buy the candy with the cost 5 and get all other candies for free.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
    
class Solution {
  public:
    vector<int> minMaxCandy(vector<int>& prices, int k) {
        vector<int> ans(2, 0);
        sort(prices.begin(), prices.end());
        int n = prices.size();
        
        // Minimum cost
        // EXPLANATION: Buy the cheapest candy and take the costliest k candies for free.
        // Then buy the next cheapest candy and take the next costliest k candies for free.
        // Repeat this until all candies are bought.
        // dry run for prices = [1, 2, 3, 4, 5], k = 2
        // buy 1, take 5 and 4 for free -> buy 2, take 3 for free -> total cost = 1 + 2 = 3
        int i = 0, j = n - 1;
        while (i <= j) {
            ans[0] += prices[i];
            i++;
            j -= k;
        }
        
        // Maximum cost
        // EXPLANATION: Buy the costliest candy and take the cheapest k candies for free.
        // Then buy the next costliest candy and take the next cheapest k candies for free.
        // Repeat this until all candies are bought.
        // dry run for prices = [1, 2, 3, 4, 5], k = 2
        // buy 5, take 1 and 2 for free -> buy 4,
        // take 3 for free -> total cost = 5 + 4 = 9
        i = 0, j = n - 1;
        while (i <= j) {
            ans[1] += prices[j];
            j--;
            i += k;
        }
        
        return ans;
    }
};