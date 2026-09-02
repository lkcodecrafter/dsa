/*
    QUESTION    : Activity Selection (N meetings in one room)
    Company Tags: Amazon, Microsoft, Flipkart, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1
    LeetCode    : https://leetcode.com/problems/non-overlapping-intervals/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Meeting struct
struct Meeting {
    int start;
    int end;
    int pos;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting meetings by finish time + linear greedy selection
// S.C : O(N)       - Storage for meeting objects
class Solution {
public:
    int maxMeetings(int start[], int end[], int n) {
        vector<Meeting> meetings(n);
        for (int i = 0; i < n; i++) {
            meetings[i] = {start[i], end[i], i + 1};
        }

        // Sort ascending by end time
        sort(meetings.begin(), meetings.end(), [](const Meeting& a, const Meeting& b) {
            return a.end < b.end;
        });

        int count = 1;
        int lastEndTime = meetings[0].end;

        // Greedily pick next meeting whose start time is strictly greater than last end time
        for (int i = 1; i < n; i++) {
            if (meetings[i].start > lastEndTime) {
                count++;
                lastEndTime = meetings[i].end;
            }
        }

        return count;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Sort by `end` time ascending.
 * - Greedily select next meeting if `start > lastEndTime`.
 * - Time: O(N log N), Space: O(N).
 */
