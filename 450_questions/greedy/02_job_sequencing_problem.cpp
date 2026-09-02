/*
    QUESTION    : Job Sequencing Problem (Maximum profit with deadlines)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Job structure
struct Job {
    int id;
    int dead;
    int profit;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N + N * Max_Deadline) - Sort jobs by profit + greedily schedule on latest available slot
// S.C : O(Max_Deadline)              - Slot availability array
class Solution {
public:
    vector<int> JobScheduling(Job arr[], int n) {
        // Sort jobs descending by profit
        sort(arr, arr + n, [](const Job& a, const Job& b) {
            return a.profit > b.profit;
        });

        int maxDeadline = 0;
        for (int i = 0; i < n; i++) {
            maxDeadline = max(maxDeadline, arr[i].dead);
        }

        vector<int> slot(maxDeadline + 1, -1);
        int countJobs = 0;
        int totalProfit = 0;

        for (int i = 0; i < n; i++) {
            // Find free slot starting from job's deadline downwards to 1
            for (int j = arr[i].dead; j > 0; j--) {
                if (slot[j] == -1) {
                    slot[j] = arr[i].id;
                    countJobs++;
                    totalProfit += arr[i].profit;
                    break;
                }
            }
        }

        return {countJobs, totalProfit};
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Sort descending by profit.
 * - For each job: schedule in latest available slot $\le$ `deadline`.
 * - Time: O(N log N + N * max_d), Space: O(max_d).
 */
