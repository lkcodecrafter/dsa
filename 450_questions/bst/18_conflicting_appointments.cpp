/*
    QUESTION    : Given n appointments, find all conflicting appointments
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/given-n-appointments-find-conflicting-appointments/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure for an Interval
struct Interval {
    int start;
    int end;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting appointments by start time takes O(N log N) + O(N) linear sweep
// S.C : O(1)       - In-place comparison after sorting
class Solution {
public:
    vector<pair<Interval, Interval>> findConflicts(vector<Interval>& appointments) {
        vector<pair<Interval, Interval>> conflicts;
        int n = appointments.size();
        if (n <= 1) return conflicts;

        // Step 1: Sort appointments primarily by their start times
        sort(appointments.begin(), appointments.end(), [](const Interval &a, const Interval &b) {
            return a.start < b.start;
        });

        // Step 2: Compare each appointment with its predecessor
        for (int i = 1; i < n; i++) {
            // An overlap occurs if the current start time is strictly less than previous appointment's end time
            if (appointments[i].start < appointments[i - 1].end) {
                conflicts.push_back({appointments[i - 1], appointments[i]});
            }
        }

        return conflicts;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF CONFLICT DETECTION
 * ============================================================================
 *
 * Given Appointments: [1, 5], [3, 7], [2, 6], [10, 15], [5, 6], [4, 100]
 *
 * Sorted by Start Time:
 * [1, 5]   |-------|
 * [2, 6]     |-------|       <-- Conflicts with [1, 5] (2 < 5)
 * [3, 7]       |-------|     <-- Conflicts with [2, 6] (3 < 6)
 * [4, 100]       |-------------------------...|
 * [5, 6]           |---|
 * [10, 15]               |-----|
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Sort intervals by `start` time: `sort(app.begin(), app.end(), [](a, b){ return a.start < b.start; })`.
 * - For `i = 1` to `n - 1`:
 *     - If `appointments[i].start < appointments[i - 1].end`: conflict detected between `i - 1` and `i`.
 * - Time: O(N log N), Space: O(1).
 */
