/*
    QUESTION    : Kth smallest number again
    Company Tags: Amazon, Directi
    Link        : https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/kth-smallest-number-again-2/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N + Q * N) - Merge intervals + linear range location per query
// S.C : O(N)               - Merged intervals vector
class Solution {
public:
    long long findKth(vector<pair<long long, long long>>& intervals, long long k) {
        // Step 1: Sort intervals by start
        sort(intervals.begin(), intervals.end());

        // Step 2: Merge overlapping intervals
        vector<pair<long long, long long>> merged;
        merged.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i].first <= merged.back().second) {
                merged.back().second = max(merged.back().second, intervals[i].second);
            } else {
                merged.push_back(intervals[i]);
            }
        }

        // Step 3: Locate which interval contains the Kth smallest element
        for (auto& iv : merged) {
            long long count = iv.second - iv.first + 1;
            if (k <= count) {
                return iv.first + k - 1;
            }
            k -= count;
        }

        return -1; // K is larger than total numbers available
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Merge overlapping intervals.
 * - For each interval: `count = end - start + 1`. If `k <= count`, return `start + k - 1`; else `k -= count`.
 * - Time: O(N log N + Q * N), Space: O(N).
 */
