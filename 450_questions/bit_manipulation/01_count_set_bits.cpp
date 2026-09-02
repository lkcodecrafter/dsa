/*
    QUESTION    : Count set bits in an integer
    Company Tags: Microsoft, Yahoo, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/set-bits0143/1
    LeetCode    : https://leetcode.com/problems/number-of-1-bits/
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(K) - Brian Kernighan’s Algorithm runs in time proportional to number of set bits (K <= 32)
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int setBits(int N) {
        int count = 0;

        // Brian Kernighan’s Algorithm: N & (N - 1) unsets the rightmost set bit
        while (N > 0) {
            N = (N & (N - 1));
            count++;
        }

        return count;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BRIAN KERNIGHAN'S ALGORITHM
 * ============================================================================
 *
 * Example: N = 12 (Binary: 1100)
 *
 * Iteration 1:
 *   N     = 12 -> 1 1 0 0
 *   N - 1 = 11 -> 1 0 1 1
 *   ---------------------
 *   N & (N - 1)= 1 0 0 0 (Value = 8, rightmost 1 at bit pos 2 is cleared!)
 *   count = 1
 *
 * Iteration 2:
 *   N     = 8  -> 1 0 0 0
 *   N - 1 = 7  -> 0 1 1 1
 *   ---------------------
 *   N & (N - 1)= 0 0 0 0 (Value = 0, rightmost 1 at bit pos 3 is cleared!)
 *   count = 2
 *
 * Loop ends (N == 0). Result count = 2.
 *
 * ============================================================================
 * DRY RUN (N = 13 -> Binary: 1101)
 * ============================================================================
 * | Iteration | N (Decimal) | N (Binary) | N - 1 (Binary) | N & (N - 1) | count |
 * | :-------- | :---------- | :--------- | :------------- | :---------- | :---- |
 * | 1         | 13          | 1101       | 1100           | 1100 (12)   | 1     |
 * | 2         | 12          | 1100       | 1011           | 1000 (8)    | 2     |
 * | 3         | 8           | 1000       | 0111           | 0000 (0)    | 3     |
 * | End       | 0           | -          | -              | -           | 3     |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Pop-A-Mole Bit Game"
 * Subtracting 1 from a number inverts all bits after the rightmost `1` (including that `1`).
 * Doing `N & (N - 1)` eliminates that single rightmost `1` like whacking a mole.
 * Count how many whacks it takes to reach 0!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `N = N & (N - 1)` clears the lowest/rightmost set bit in $O(1)$.
 * - Loop until $N = 0$, incrementing `count` each iteration.
 * - Runs in $O(\text{number of 1s})$ instead of standard 32-bit loop.
 * - Alternative in modern C++: `__builtin_popcount(N)`.
 * - Time: O(Set Bits), Space: O(1).
 */
