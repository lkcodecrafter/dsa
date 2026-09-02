/*
    QUESTION    : Count total set bits in all numbers from 1 to n
    Company Tags: Amazon, Microsoft, Samsung, Payu
    GfG Link    : https://practice.geeksforgeeks.org/problems/count-total-set-bits-1587115620/1
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(log N) - Recursively subtracts largest power of 2 <= n at each step
// S.C : O(log N) - Recursion stack depth
class Solution {
private:
    // Helper function to find largest power of 2 <= n, returns exponent x where 2^x <= n
    int findLargestPowerOf2(int n) {
        int x = 0;
        while ((1 << (x + 1)) <= n) {
            x++;
        }
        return x;
    }

public:
    int countSetBits(int n) {
        // Base Case
        if (n <= 0) return 0;

        int x = findLargestPowerOf2(n); // 2^x is the largest power of 2 <= n

        // 1. Bits in all numbers from 0 to 2^x - 1 = x * 2^(x - 1)
        int bitsUpTo2PowX = x * (1 << (x - 1));

        // 2. The MSB (most significant bit at pos x) for numbers from 2^x to n = (n - 2^x + 1)
        int msbFrom2PowXToN = n - (1 << x) + 1;

        // 3. The remaining lower bits for numbers from 2^x to n is equivalent to countSetBits(n - 2^x)
        int rest = countSetBits(n - (1 << x));

        return bitsUpTo2PowX + msbFrom2PowXToN + rest;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 3-PART DECOMPOSITION
 * ============================================================================
 *
 * Example: n = 11 (Binary: 1011)
 * Largest power of 2 <= 11 is 8 (x = 3, since 2^3 = 8 <= 11).
 *
 * Group 1: Numbers 0 to 7 (0000 to 0111) -> 8 numbers, 3 bit columns:
 *   Total 1s = 3 * 2^(3-1) = 3 * 4 = 12 bits.
 *
 * Group 2: The MSB (bit pos 3) for numbers 8 to 11 (1000, 1001, 1010, 1011):
 *   Count = 11 - 8 + 1 = 4 bits.
 *
 * Group 3: Lower bits for 8 to 11 (after removing MSB):
 *   8  (1000) -> 000 (0)
 *   9  (1001) -> 001 (1)
 *   10 (1010) -> 010 (2)
 *   11 (1011) -> 011 (3)
 *   Equivalent to countSetBits(11 - 8) = countSetBits(3).
 *
 * Total = 12 + 4 + countSetBits(3) = 16 + 4 = 20 bits!
 *
 * ============================================================================
 * DRY RUN (n = 4)
 * ============================================================================
 * | Level | n | x (2^x <= n) | x * 2^(x-1) | n - 2^x + 1 | Recursive Call | Subtotal |
 * | :---- | :-| :----------- | :---------- | :---------- | :------------- | :------- |
 * | 1     | 4 | x = 2 (4)    | 2 * 2^1 = 4 | 4 - 4 + 1=1 | countSetBits(0)| 4+1+0 = 5|
 * | 2     | 0 | -            | -           | -           | Base Case -> 0 | 0        |
 *
 * Output = 5.
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The 3-Piece Binary Cake"
 * Slice numbers $1$ to $N$ into 3 sections:
 * 1. The complete rectangular power-of-2 block ($x \cdot 2^{x-1}$).
 * 2. The leading 1-bits on the remaining numbers ($N - 2^x + 1$).
 * 3. The recurring leftover suffix cake (`countSetBits(N - 2^x)`).
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Find $x$ such that $2^x \le N$.
 * - Three formula components:
 *     1. `bitsUpTo2PowX = x * (1 << (x - 1))`
 *     2. `msbFrom2PowXToN = n - (1 << x) + 1`
 *     3. `rest = countSetBits(n - (1 << x))`
 * - Base Case: `if (n <= 0) return 0;`
 * - Time: O(log N), Space: O(log N).
 */
