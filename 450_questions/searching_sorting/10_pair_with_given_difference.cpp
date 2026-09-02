/*
    QUESTION    : Find Pair Given Difference
    Company Tags: Amazon, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/find-pair-given-difference1559/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting + Two pointers
// S.C : O(1)       - Constant auxiliary space
class Solution {
public:
    int findPair(int n, int x, vector<int> &arr) {
        sort(arr.begin(), arr.end());

        int i = 0;
        int j = 1;

        while (i < n && j < n) {
            int diff = arr[j] - arr[i];

            if (i != j && diff == x) {
                return 1; // Pair found
            } else if (diff < x) {
                j++;
            } else {
                i++;
            }

            if (i == j) j++;
        }

        return -1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(arr)`. Two pointers `i = 0, j = 1`.
 * - If `arr[j] - arr[i] == x && i != j`: return `1`.
 * - If `< x`: `j++`; else `i++`.
 * - Time: O(N log N), Space: O(1).
 */
