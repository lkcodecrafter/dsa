/*
    QUESTION    : Mobile numeric keypad (Count numbers of length N using valid key transitions)
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/mobile-numeric-keypad5456/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * 10) = O(N) - Keypad transition state DP
// S.C : O(10) = O(1)     - 1D DP array of size 10
class Solution {
public:
    long long getCount(int N) {
        if (N == 1) return 10;

        // Keypad adjacency (self + up, down, left, right):
        // 1 2 3
        // 4 5 6
        // 7 8 9
        // * 0 #
        vector<vector<int>> moves = {
            {0, 8},          // 0
            {1, 2, 4},       // 1
            {2, 1, 3, 5},    // 2
            {3, 2, 6},       // 3
            {4, 1, 5, 7},    // 4
            {5, 2, 4, 6, 8}, // 5
            {6, 3, 5, 9},    // 6
            {7, 4, 8},       // 7
            {8, 5, 7, 9, 0}, // 8
            {9, 6, 8}        // 9
        };

        vector<long long> prev(10, 1);

        for (int len = 2; len <= N; len++) {
            vector<long long> curr(10, 0);

            for (int digit = 0; digit <= 9; digit++) {
                for (int nextDigit : moves[digit]) {
                    curr[digit] += prev[nextDigit];
                }
            }

            prev = curr;
        }

        long long totalCount = 0;
        for (int d = 0; d <= 9; d++) {
            totalCount += prev[d];
        }

        return totalCount;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `curr[d] = sum(prev[adj])` where `adj` includes self + neighbors on keypad.
 * - Time: O(N), Space: O(1).
 */
