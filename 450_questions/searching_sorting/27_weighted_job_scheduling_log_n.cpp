/*
    QUESTION    : Weighted Job Scheduling in O(N Log N) time
    Company Tags: Amazon, Google, Flipkart
    GfG Link    : https://www.geeksforgeeks.org/weighted-job-scheduling-log-n-time/
    LeetCode    : https://leetcode.com/problems/maximum-profit-in-job-scheduling/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Job structure
struct Job {
    int start, finish, profit;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting jobs by finish time + DP with binary search for non-conflicting jobs
// S.C : O(N)       - DP array
class Solution {
private:
    // Binary search to find the latest non-overlapping job (finish <= jobs[index].start)
    int latestNonConflict(const vector<Job>& jobs, int index) {
        int low = 0, high = index - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (jobs[mid].finish <= jobs[index].start) {
                if (jobs[mid + 1].finish <= jobs[index].start) {
                    low = mid + 1;
                } else {
                    return mid;
                }
            } else {
                high = mid - 1;
            }
        }

        return -1;
    }

public:
    int findMaxProfit(vector<Job>& jobs, int n) {
        // Step 1: Sort jobs ascending by finish time
        sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
            return a.finish < b.finish;
        });

        vector<int> dp(n, 0);
        dp[0] = jobs[0].profit;

        // Step 2: DP transition
        for (int i = 1; i < n; i++) {
            int incProfit = jobs[i].profit;
            int l = latestNonConflict(jobs, i);
            if (l != -1) {
                incProfit += dp[l];
            }

            int excProfit = dp[i - 1];
            dp[i] = max(incProfit, excProfit);
        }

        return dp[n - 1];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Sort by `finish` time.
 * - `dp[i] = max(dp[i - 1], jobs[i].profit + dp[latestNonConflict(i)])`.
 * - Find non-conflict in $O(\log N)$ using binary search.
 * - Time: O(N log N), Space: O(N).
 */
