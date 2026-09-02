/*
    QUESTION    : Bishu and Soldiers
    Company Tags: Amazon, Flipkart
    Link        : https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/bishu-and-soldiers/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N + Q log N) - Sorting + Prefix sum + Binary search (upper_bound) per query
// S.C : O(N)                - Prefix sum array
class Solution {
public:
    void solve(int n, vector<int>& powers, int q, const vector<int>& queries) {
        sort(powers.begin(), powers.end());

        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + powers[i];
        }

        for (int power : queries) {
            // Count soldiers Bishu can defeat (power <= P) using upper_bound
            int count = upper_bound(powers.begin(), powers.end(), power) - powers.begin();
            int totalSum = prefixSum[count];
            cout << count << " " << totalSum << "\n";
        }
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(powers)`. Build `prefixSum`.
 * - `count = upper_bound(powers.begin(), powers.end(), P) - powers.begin()`.
 * - `sum = prefixSum[count]`.
 * - Time: O((N + Q) log N), Space: O(N).
 */
