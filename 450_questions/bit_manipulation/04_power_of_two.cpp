/*
    QUESTION    : Program to find whether a no is power of two
    Company Tags: Amazon, Microsoft, Google, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/power-of-2-1587115620/1
    LeetCode    : https://leetcode.com/problems/power-of-two/
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(1) - Single bitwise AND comparison
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    bool isPowerofTwo(long long n) {
        // A power of 2 has exactly one set bit.
        // For n > 0, n & (n - 1) clears that only set bit, turning the value to 0.
        return (n > 0) && ((n & (n - 1)) == 0);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF POWERS OF 2 IN BINARY
 * ============================================================================
 *
 * Decimal       Binary       n - 1 (Binary)     n & (n - 1)
 * -------------------------------------------------------------
 * 1 (2^0)       0 0 0 1      0 0 0 0            0 0 0 0  (True)
 * 2 (2^1)       0 0 1 0      0 0 0 1            0 0 0 0  (True)
 * 4 (2^2)       0 1 0 0      0 0 1 1            0 0 0 0  (True)
 * 8 (2^3)       1 0 0 0      0 1 1 1            0 0 0 0  (True)
 * 6 (Not power) 0 1 1 0      0 1 0 1            0 1 0 0  (False, 4 != 0)
 *
 * ============================================================================
 * DRY RUN
 * ============================================================================
 * | n | Condition n > 0 | n & (n - 1) | Is (n & (n-1)) == 0? | Result |
 * | :- | :-------------- | :---------- | :------------------- | :----- |
 * | 16 | True            | 16 & 15 = 0 | True                 | True   |
 * | 18 | True            | 18 & 17 = 16| False                | False  |
 * | 0  | False           | -           | -                    | False  |
 * | -4 | False           | -           | -                    | False  |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Lonely Lone Wolf Bit"
 * In binary, every power of 2 is a single `1` followed only by `0`s (e.g. `1000`).
 * Subtracting 1 flips everything up to that `1` (`0111`).
 * Their bitwise AND is completely zero.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Property of Power of 2: Exactly ONE bit is set.
 * - Checking expression: `n > 0 && (n & (n - 1)) == 0`.
 * - Edge Cases: Check `n > 0` because negative numbers and zero are not powers of two.
 * - Time: O(1), Space: O(1).
 */
