/*
    QUESTION    : Shop in Candy Store (Min and Max money to buy all candies)
    Company Tags: Amazon, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/shop-in-candy-store1145/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting candy prices + two-pointer greedy bounds
// S.C : O(1)       - Constant auxiliary space
class Solution {
public:
    vector<int> candyStore(int candies[], int N, int K) {
        sort(candies, candies + N);

        // 1. Calculate Minimum Cost: Buy cheapest candies from left, take K expensive free from right
        int minCost = 0;
        int i = 0, j = N - 1;
        while (i <= j) {
            minCost += candies[i++];
            j -= K; // Take K free candies
        }

        // 2. Calculate Maximum Cost: Buy most expensive candies from right, take K cheapest free from left
        int maxCost = 0;
        i = 0;
        j = N - 1;
        while (i <= j) {
            maxCost += candies[j--];
            i += K; // Take K free candies
        }

        return {minCost, maxCost};
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(candies)`.
 * - Min Cost: buy `candies[i++]`, discard `j -= K`.
 * - Max Cost: buy `candies[j--]`, discard `i += K`.
 * - Time: O(N log N), Space: O(1).
 */
