/*
    QUESTION    : Aggressive Cows (Binary Search on Answer)
    Company Tags: Amazon, Google
    Link        : https://www.spoj.com/problems/AGGRCOW/
    LeetCode    : https://leetcode.com/problems/magnetic-force-between-two-balls/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N + N log(max_dist)) - Sorting stalls + Binary search on maximum minimum distance
// S.C : O(1)                        - Constant auxiliary space
class Solution {
private:
    bool isPossible(const vector<int>& stalls, int k, int minDist) {
        int cowsPlaced = 1;
        int lastPos = stalls[0];

        for (int i = 1; i < stalls.size(); i++) {
            if (stalls[i] - lastPos >= minDist) {
                cowsPlaced++;
                lastPos = stalls[i];
                if (cowsPlaced == k) return true;
            }
        }

        return false;
    }

public:
    int solve(int n, int k, vector<int> &stalls) {
        sort(stalls.begin(), stalls.end());

        int low = 1;
        int high = stalls[n - 1] - stalls[0];
        int ans = 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isPossible(stalls, k, mid)) {
                ans = mid;    // Record valid minimum distance
                low = mid + 1; // Try to maximize distance
            } else {
                high = mid - 1; // Distance too large; shrink
            }
        }

        return ans;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(stalls)`. Binary Search on `minDist \in [1, max_dist]`.
 * - Greedy check: place cow if `stalls[i] - lastPos >= minDist`.
 * - If `isPossible`: `ans = mid; low = mid + 1;` else `high = mid - 1;`.
 * - Time: O(N log(max_dist)), Space: O(1).
 */
