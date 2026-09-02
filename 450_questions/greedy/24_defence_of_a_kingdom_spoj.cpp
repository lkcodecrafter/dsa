/*
    QUESTION    : DEFKIN - Defense of a Kingdom (SPOJ)
    Company Tags: Google
    Link        : https://www.spoj.com/problems/DEFKIN/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting X and Y coordinates to find maximum undefended gap rectangle
// S.C : O(N)       - Coordinate vectors
class Solution {
public:
    int maxUndefendedArea(int w, int h, int n, vector<pair<int, int>>& towers) {
        vector<int> x, y;
        x.push_back(0);
        y.push_back(0);

        for (int i = 0; i < n; i++) {
            x.push_back(towers[i].first);
            y.push_back(towers[i].second);
        }

        x.push_back(w + 1);
        y.push_back(h + 1);

        sort(x.begin(), x.end());
        sort(y.begin(), y.end());

        int maxXGap = 0;
        int maxYGap = 0;

        for (int i = 1; i < x.size(); i++) {
            maxXGap = max(maxXGap, x[i] - x[i - 1] - 1);
            maxYGap = max(maxYGap, y[i] - y[i - 1] - 1);
        }

        return maxXGap * maxYGap;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Store tower coordinates with boundaries `0` and `w+1` (for X), `0` and `h+1` (for Y).
 * - Sort and find `maxXGap = max(x[i] - x[i-1] - 1)` and `maxYGap = max(y[i] - y[i-1] - 1)`.
 * - Result = `maxXGap * maxYGap`.
 * - Time: O(N log N), Space: O(N).
 */
