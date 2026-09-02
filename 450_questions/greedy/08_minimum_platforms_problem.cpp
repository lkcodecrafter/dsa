/*
    QUESTION    : Minimum Platforms
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-platforms-1587115620/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting arrival and departure times separately + two-pointer sweep
// S.C : O(1)       - Constant auxiliary space
class Solution {
public:
    int findPlatform(int arr[], int dep[], int n) {
        sort(arr, arr + n);
        sort(dep, dep + n);

        int platformsNeeded = 1;
        int maxPlatforms = 1;

        int i = 1; // Pointer for arrival
        int j = 0; // Pointer for departure

        while (i < n && j < n) {
            // If next train arrives before current train departs, extra platform required
            if (arr[i] <= dep[j]) {
                platformsNeeded++;
                i++;
            } else {
                platformsNeeded--;
                j++;
            }

            maxPlatforms = max(maxPlatforms, platformsNeeded);
        }

        return maxPlatforms;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(arr)`, `sort(dep)`. Two pointers `i = 1, j = 0`.
 * - If `arr[i] <= dep[j]`: `platforms++; i++;` else `platforms--; j++;`.
 * - Time: O(N log N), Space: O(1).
 */
