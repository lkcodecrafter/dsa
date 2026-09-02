/*
    QUESTION    : Value equal to index value (Fixed Point)
    Company Tags: Amazon, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/value-equal-to-index-value1330/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - 1-based indexing search
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    vector<int> valueEqualToIndex(int arr[], int n) {
        vector<int> result;

        for (int i = 0; i < n; i++) {
            // 1-based indexing condition: arr[i] == i + 1
            if (arr[i] == i + 1) {
                result.push_back(arr[i]);
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - For 1-based index: check `arr[i] == i + 1`.
 * - Time: O(N), Space: O(1).
 */
