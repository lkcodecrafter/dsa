/*
    QUESTION    : Max Length Chain (Maximum Length Chain of Pairs)
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/max-length-chain/1
    LeetCode    : https://leetcode.com/problems/maximum-length-of-pair-chain/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Pair struct
struct val {
    int first;
    int second;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Greedy Activity Selection by second element
// S.C : O(1)       - In-place sorting
class Solution {
public:
    int maxChainLen(struct val p[], int n) {
        // Sort pairs ascending by second element
        sort(p, p + n, [](const val& a, const val& b) {
            return a.second < b.second;
        });

        int chainLen = 1;
        int lastEnd = p[0].second;

        for (int i = 1; i < n; i++) {
            if (p[i].first > lastEnd) {
                chainLen++;
                lastEnd = p[i].second;
            }
        }

        return chainLen;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Sort by `second` ascending.
 * - If `p[i].first > lastEnd`: `chainLen++; lastEnd = p[i].second;`
 * - Time: O(N log N), Space: O(1).
 */
