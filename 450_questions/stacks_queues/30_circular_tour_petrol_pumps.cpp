/*
    QUESTION    : Find the first circular tour that visits all Petrol Pumps (Gas Station)
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/circular-tour-1587115620/1
    LeetCode    : https://leetcode.com/problems/gas-station/
*/

#include <iostream>
#include <vector>

using namespace std;

// Structure for petrol pump
struct petrolPump {
    int petrol;
    int distance;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Single linear greedy pass
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int tour(petrolPump p[], int n) {
        int deficit = 0;
        int currentBalance = 0;
        int start = 0;

        for (int i = 0; i < n; i++) {
            currentBalance += (p[i].petrol - p[i].distance);

            // If current balance drops below 0, cannot reach station i + 1 from current start
            if (currentBalance < 0) {
                deficit += currentBalance;
                currentBalance = 0;
                start = i + 1; // Try starting from next station
            }
        }

        // If total balance + deficit >= 0, a complete circular tour is possible starting at `start`
        if (currentBalance + deficit >= 0) {
            return start;
        }

        return -1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `currentBalance += (petrol - distance)`.
 * - If `currentBalance < 0`: `deficit += currentBalance; currentBalance = 0; start = i + 1;`
 * - Return `(currentBalance + deficit >= 0) ? start : -1`.
 * - Time: O(N), Space: O(1).
 */
