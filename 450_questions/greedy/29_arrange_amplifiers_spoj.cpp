/*
    QUESTION    : ARRANGE - Arranging Amplifiers (SPOJ)
    Company Tags: Google
    Link        : https://www.spoj.com/problems/ARRANGE/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting descending + handling special base cases for 1, 2, and 3
// S.C : O(1)       - In-place arrangement
class Solution {
public:
    void arrangeAmplifiers(vector<int>& arr) {
        int onesCount = 0;
        vector<int> others;

        for (int x : arr) {
            if (x == 1) onesCount++;
            else others.push_back(x);
        }

        // Sort non-1 amplifiers descending because a^b > b^a when a < b (except for 2 and 3)
        sort(others.rbegin(), others.rend());

        // Print all 1s first (1^x = 1, x^1 = x, so 1s should precede)
        for (int i = 0; i < onesCount; i++) {
            cout << 1 << " ";
        }

        // Special case: if remaining elements are exactly [3, 2], 2^3 (8) < 3^2 (9), so print 2 then 3!
        if (others.size() == 2 && others[0] == 3 && others[1] == 2) {
            cout << 2 << " " << 3 << "\n";
            return;
        }

        for (int x : others) {
            cout << x << " ";
        }
        cout << "\n";
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Print all 1s first.
 * - If remaining is exactly `{3, 2}`, print `2 3` ($2^3 = 8 < 3^2 = 9$).
 * - Otherwise print in descending order.
 * - Time: O(N log N), Space: O(1).
 */
