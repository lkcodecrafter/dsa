/*
    QUESTION    : Fractional Knapsack
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Item struct
struct Item {
    int value;
    int weight;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting items by value/weight ratio + linear greedy filling
// S.C : O(1)       - Constant auxiliary space
class Solution {
public:
    double fractionalKnapsack(int W, Item arr[], int n) {
        // Sort descending by value-to-weight ratio
        sort(arr, arr + n, [](const Item& a, const Item& b) {
            double r1 = (double)a.value / a.weight;
            double r2 = (double)b.value / b.weight;
            return r1 > r2;
        });

        double totalValue = 0.0;
        int remainingWeight = W;

        for (int i = 0; i < n; i++) {
            if (arr[i].weight <= remainingWeight) {
                totalValue += arr[i].value;
                remainingWeight -= arr[i].weight;
            } else {
                // Take fraction of the item
                totalValue += (double)arr[i].value * ((double)remainingWeight / arr[i].weight);
                break; // Knapsack is full
            }
        }

        return totalValue;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Sort descending by ratio `value / weight`.
 * - Take whole items if possible; take fraction of last item to fill knapsack.
 * - Time: O(N log N), Space: O(1).
 */
