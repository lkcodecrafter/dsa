/*
    QUESTION    : Water Jug problem using BFS
    Company Tags: Google
    GfG Link    : https://www.geeksforgeeks.org/water-jug-problem-using-bfs/
    LeetCode    : https://leetcode.com/problems/water-and-jug-problem/
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(m * n) - BFS state space search across all jug capacity pairs
// S.C : O(m * n) - Visited state set and queue
class Solution {
public:
    int minSteps(int m, int n, int d) {
        // Target d cannot exceed capacity of both jugs
        if (d > max(m, n)) return -1;

        // BFS state: {jug1_amt, jug2_amt}
        queue<pair<pair<int, int>, int>> q; // {{j1, j2}, steps}
        set<pair<int, int>> visited;

        q.push({{0, 0}, 0});
        visited.insert({0, 0});

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            int j1 = curr.first.first;
            int j2 = curr.first.second;
            int steps = curr.second;

            if (j1 == d || j2 == d) {
                return steps;
            }

            // 6 Possible Operations:
            vector<pair<int, int>> nextStates = {
                {m, j2},                                      // Fill Jug 1
                {j1, n},                                      // Fill Jug 2
                {0, j2},                                      // Empty Jug 1
                {j1, 0},                                      // Empty Jug 2
                {j1 - min(j1, n - j2), j2 + min(j1, n - j2)}, // Pour Jug 1 -> Jug 2
                {j1 + min(j2, m - j1), j2 - min(j2, m - j1)}  // Pour Jug 2 -> Jug 1
            };

            for (auto& state : nextStates) {
                if (visited.find(state) == visited.end()) {
                    visited.insert(state);
                    q.push({state, steps + 1});
                }
            }
        }

        return -1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - BFS on 6 transitions: Fill 1, Fill 2, Empty 1, Empty 2, Pour 1->2, Pour 2->1.
 * - Target reached when `j1 == d || j2 == d`.
 * - Time: O(m * n), Space: O(m * n).
 */
