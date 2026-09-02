/*
    QUESTION    : Minimum number of swaps required to sort an array
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-swaps/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting pairs + O(N) permutation cycle detection
// S.C : O(N)       - Vector of pairs and visited array
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> pos(n);

        for (int i = 0; i < n; i++) {
            pos[i] = {nums[i], i};
        }

        sort(pos.begin(), pos.end());

        vector<bool> visited(n, false);
        int totalSwaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || pos[i].second == i) {
                continue;
            }

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = pos[j].second;
                cycleSize++;
            }

            if (cycleSize > 1) {
                totalSwaps += (cycleSize - 1);
            }
        }

        return totalSwaps;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Store `{nums[i], i}` and sort.
 * - Find permutation cycles: `swaps += (cycleSize - 1)`.
 * - Time: O(N log N), Space: O(N).
 */
