/*
    QUESTION    : Shortest Job First (or SJF) CPU Scheduling (Non-preemptive)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/program-for-shortest-job-first-or-sjf-cpu-scheduling-set-1-non-preemptive/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting burst times minimizes average waiting time
// S.C : O(1)       - Constant auxiliary space
class Solution {
public:
    long long solve(vector<int>& bt) {
        sort(bt.begin(), bt.end());

        long long totalWaitTime = 0;
        long long currentWaitTime = 0;

        for (int i = 0; i < bt.size(); i++) {
            totalWaitTime += currentWaitTime;
            currentWaitTime += bt[i];
        }

        // Return average waiting time (floor)
        return totalWaitTime / bt.size();
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(bt)`.
 * - `totalWait += currentWait; currentWait += bt[i];`
 * - Return `totalWait / n`.
 * - Time: O(N log N), Space: O(1).
 */
