/*
    QUESTION    : Weighted Job Scheduling (Maximum Profit in Non-overlapping Jobs)
    Company Tags: Amazon, Google, Flipkart
    LeetCode    : https://leetcode.com/problems/maximum-profit-in-job-scheduling/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Job representation
struct Job {
    int start, end, profit;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting by finish time + Binary search on compatible non-overlapping job
// S.C : O(N)       - DP array
class Solution {
private:
    int findLastNonConflicting(const vector<Job>& jobs, int i) {
        int low = 0, high = i - 1;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (jobs[mid].end <= jobs[i].start) {
                ans = mid;
                low = mid + 1; // Look for closer compatible job on right
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }

public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<Job> jobs(n);

        for (int i = 0; i < n; i++) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }

        // Sort ascending by end time
        sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
            return a.end < b.end;
        });

        vector<int> dp(n, 0);
        dp[0] = jobs[0].profit;

        for (int i = 1; i < n; i++) {
            int incProfit = jobs[i].profit;
            int lastCompatible = findLastNonConflicting(jobs, i);

            if (lastCompatible != -1) {
                incProfit += dp[lastCompatible];
            }

            dp[i] = max(dp[i - 1], incProfit);
        }

        return dp[n - 1];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Sort jobs by `end` time ascending.
 * - Binary search last job with `jobs[k].end <= jobs[i].start`.
 * - `dp[i] = max(dp[i-1], jobs[i].profit + (k != -1 ? dp[k] : 0))`.
 * - Time: O(N log N), Space: O(N).
 */
