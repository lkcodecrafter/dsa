/*
    QUESTION    : Min Number of Flips (to make binary string alternate)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/min-number-of-flips3210/1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Single pass comparing with '0101...' and '1010...'
// S.C : O(1) - Two flip counters
class Solution {
public:
    int minFlips(string S) {
        int flipsStartingWith0 = 0;
        int flipsStartingWith1 = 0;

        for (int i = 0; i < S.length(); i++) {
            char expectedChar0 = (i % 2 == 0) ? '0' : '1';
            char expectedChar1 = (i % 2 == 0) ? '1' : '0';

            if (S[i] != expectedChar0) flipsStartingWith0++;
            if (S[i] != expectedChar1) flipsStartingWith1++;
        }

        return min(flipsStartingWith0, flipsStartingWith1);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Count mismatches against pattern "0101..." and "1010...".
 * - Return `min(flips0, flips1)`.
 * - Time: O(N), Space: O(1).
 */
