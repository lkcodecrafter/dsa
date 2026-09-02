/*
    QUESTION    : Maximum meetings in one room (Return 1-based indices of meetings selected)
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximum-meetings-in-one-room/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Meeting representation
struct Meeting {
    int start;
    int end;
    int pos;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting by finish time + greedy selection
// S.C : O(N)       - Selected meetings result list
class Solution {
public:
    vector<int> maxMeetings(int N, vector<int> &S, vector<int> &F) {
        vector<Meeting> meetings(N);
        for (int i = 0; i < N; i++) {
            meetings[i] = {S[i], F[i], i + 1};
        }

        // Sort by end time ascending; if end times equal, sort by original position
        sort(meetings.begin(), meetings.end(), [](const Meeting& a, const Meeting& b) {
            if (a.end == b.end) return a.pos < b.pos;
            return a.end < b.end;
        });

        vector<int> selectedMeetings;
        selectedMeetings.push_back(meetings[0].pos);
        int lastEndTime = meetings[0].end;

        for (int i = 1; i < N; i++) {
            if (meetings[i].start > lastEndTime) {
                selectedMeetings.push_back(meetings[i].pos);
                lastEndTime = meetings[i].end;
            }
        }

        sort(selectedMeetings.begin(), selectedMeetings.end()); // Return indices in ascending order
        return selectedMeetings;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Store `{start, end, pos}`. Sort by `end` time ascending.
 * - Select meeting if `start > lastEndTime`.
 * - Sort and return selected indices.
 * - Time: O(N log N), Space: O(N).
 */
