/*
    QUESTION    : Maximum trains for which stoppage can be provided
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/maximum-trains-stoppage-can-provided/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Train structure
struct Train {
    int arrTime, deptTime, platform;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Grouping by platform + Activity Selection per platform
// S.C : O(N + P)   - Platform lists and train vectors
class Solution {
public:
    int maxStop(int n, int m, vector<vector<int>>& trains) {
        // Platform indexed lists of trains
        vector<vector<pair<int, int>>> plat(n + 1);

        for (int i = 0; i < m; i++) {
            plat[trains[i][2]].push_back({trains[i][1], trains[i][0]}); // {deptTime, arrTime}
        }

        int totalStoppages = 0;

        // Run activity selection independently on each platform
        for (int i = 1; i <= n; i++) {
            if (plat[i].empty()) continue;

            sort(plat[i].begin(), plat[i].end()); // Sort ascending by departure time

            totalStoppages++;
            int lastDept = plat[i][0].first;

            for (int j = 1; j < plat[i].size(); j++) {
                if (plat[i][j].second >= lastDept) {
                    totalStoppages++;
                    lastDept = plat[i][j].first;
                }
            }
        }

        return totalStoppages;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Group trains by platform number.
 * - Run standard activity selection on departure time for each platform independently.
 * - Time: O(M log M), Space: O(M + N).
 */
