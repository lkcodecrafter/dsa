/*
    QUESTION    : EKO - Eko (Lumberjack Mirko Sawblade Height)
    Company Tags: Amazon, Google
    Link        : https://www.spoj.com/problems/EKO/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * log(Max_Height)) - Binary search on sawblade height H
// S.C : O(1)                   - Constant auxiliary space
class Solution {
private:
    bool isWoodSufficient(const vector<long long>& trees, long long M, long long H) {
        long long totalWood = 0;
        for (long long height : trees) {
            if (height > H) {
                totalWood += (height - H);
            }
        }
        return totalWood >= M;
    }

public:
    long long getMaxSawbladeHeight(const vector<long long>& trees, long long M) {
        long long low = 0;
        long long high = *max_element(trees.begin(), trees.end());
        long long bestHeight = 0;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (isWoodSufficient(trees, M, mid)) {
                bestHeight = mid; // Wood collected >= M: try higher sawblade
                low = mid + 1;
            } else {
                high = mid - 1;   // Wood collected < M: lower sawblade
            }
        }

        return bestHeight;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Binary search on blade height $H \in [0, \max(tree)]$.
 * - If `totalWood >= M`: `bestHeight = mid; low = mid + 1;` else `high = mid - 1;`.
 * - Time: O(N log(max_h)), Space: O(1).
 */
