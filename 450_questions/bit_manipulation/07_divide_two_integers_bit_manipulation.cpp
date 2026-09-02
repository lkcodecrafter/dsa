/*
    QUESTION    : Divide two integers without using multiplication, division and mod operator
    Company Tags: Amazon, Microsoft, Facebook
    GfG Link    : https://practice.geeksforgeeks.org/problems/division-without-using-multiplication-division-and-mod-operator/0
    LeetCode    : https://leetcode.com/problems/divide-two-integers/
*/

#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O((log N)^2) or O(32) - Repeatedly subtract largest power-of-2 multiple of divisor
// S.C : O(1)                 - Constant auxiliary space
class Solution {
public:
    int divide(long long dividend, long long divisor) {
        // Handle 32-bit integer overflow edge case: INT_MIN / -1 = INT_MAX + 1 (overflows)
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        // Determine sign of the result
        bool isNegative = (dividend < 0) ^ (divisor < 0);

        // Work with absolute values in long long to prevent overflow
        long long n = abs(dividend);
        long long d = abs(divisor);
        long long quotient = 0;

        // Exponential bit-shifting subtraction
        while (n >= d) {
            int count = 0;
            // Find largest power of 2 such that (d << (count + 1)) <= n
            while (n >= (d << (count + 1))) {
                count++;
            }

            quotient += (1LL << count);
            n -= (d << count); // Subtract the largest multiple found
        }

        return isNegative ? -quotient : quotient;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BIT-SHIFT DIVISION
 * ============================================================================
 *
 * Example: Dividend = 43, Divisor = 8
 *
 * Step 1:
 *   8 << 0 = 8   <= 43
 *   8 << 1 = 16  <= 43
 *   8 << 2 = 32  <= 43  (count = 2)
 *   8 << 3 = 64  > 43 (Too big)
 *   -> quotient += (1 << 2) = 4
 *   -> n = 43 - 32 = 11
 *
 * Step 2:
 *   8 << 0 = 8   <= 11  (count = 0)
 *   8 << 1 = 16  > 11 (Too big)
 *   -> quotient += (1 << 0) = 1
 *   -> n = 11 - 8 = 3
 *
 * Step 3:
 *   n (3) < divisor (8) -> Stop!
 *
 * Total Quotient = 4 + 1 = 5, Remainder = 3.
 *
 * ============================================================================
 * DRY RUN (dividend = 22, divisor = 3)
 * ============================================================================
 * | Iteration | n  | d | Max Shift (count) | d << count | quotient Added | Remaining n |
 * | :-------- | :- | :-| :---------------- | :--------- | :------------- | :---------- |
 * | 1         | 22 | 3 | count = 2         | 3 << 2 = 12| 1 << 2 = 4     | 22 - 12 = 10|
 * | 2         | 10 | 3 | count = 1         | 3 << 1 = 6 | 1 << 1 = 2     | 10 - 6  = 4 |
 * | 3         | 4  | 3 | count = 0         | 3 << 0 = 3 | 1 << 0 = 1     | 4 - 3   = 1 |
 * | End       | 1  | 3 | n < d             | -          | Total = 7      | Final Rem=1 |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Doubling Currency Bills"
 * Instead of paying a debt $N$ by handing over $1 bills one by one ($O(N)$),
 * you double the bills: $1 \rightarrow 2 \rightarrow 4 \rightarrow 8 \rightarrow 16...$
 * Pay the largest doubled bundle you can afford, then repeat on the remainder.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sign = (dividend < 0) ^ (divisor < 0)`.
 * - While `n >= d`:
 *     - Find largest `count` where `n >= (d << (count + 1))`.
 *     - `quotient += (1LL << count)`, `n -= (d << count)`.
 * - Edge case: `INT_MIN / -1` returns `INT_MAX`.
 * - Time Complexity: O((log N)^2) or O(32), Space Complexity: O(1).
 */
