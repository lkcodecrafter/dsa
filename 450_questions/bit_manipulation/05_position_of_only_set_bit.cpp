/*
    QUESTION    : Find position of the only set bit (1-based position from right)
    Company Tags: Amazon, Microsoft, Snapdeal
    GfG Link    : https://practice.geeksforgeeks.org/problems/find-position-of-set-bit3706/1
*/

#include <iostream>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(1) - Checked using power of 2 test + log2 computation
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int findPosition(int N) {
        // Condition: N must be greater than 0 and have exactly one set bit (i.e. power of 2)
        if (N <= 0 || (N & (N - 1)) != 0) {
            return -1; // Not a valid power of 2
        }

        // log2(N) gives the 0-based bit position; add 1 for 1-based indexing
        return log2(N) + 1;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BIT POSITION
 * ============================================================================
 *
 * N = 16 (Binary: 1 0 0 0 0)
 * Bit Indices from right (1-based):
 * Pos:    5   4   3   2   1
 * Bits: [ 1 | 0 | 0 | 0 | 0 ]
 * log2(16) = 4 -> 1-based pos = 4 + 1 = 5.
 *
 * N = 12 (Binary: 1 1 0 0) -> Has two set bits -> Returns -1.
 *
 * ============================================================================
 * DRY RUN
 * ============================================================================
 * | N (Decimal) | Binary | (N & (N - 1)) | Valid (One Bit)? | log2(N) + 1 | Output |
 * | :---------- | :----- | :------------ | :--------------- | :---------- | :----- |
 * | 2           | 0010   | 2 & 1 = 0     | Yes              | 1 + 1 = 2   | 2      |
 * | 5           | 0101   | 5 & 4 = 4     | No               | -           | -1     |
 * | 8           | 1000   | 8 & 7 = 0     | Yes              | 3 + 1 = 4   | 4      |
 * | 0           | 0000   | N <= 0        | No               | -           | -1     |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Singlet Beacon"
 * Check if the radio tower has only ONE signal transmitter activated (`(N & (N - 1)) == 0`).
 * If valid, the logarithm base 2 reveals the exact frequency channel (index) of the transmitter.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `N <= 0 || (N & (N - 1)) != 0`, return `-1` (either 0 or multiple set bits).
 * - Otherwise: position = `log2(N) + 1` (or count shifts in a `while(N > 0)` loop).
 * - Time: O(1), Space: O(1).
 */
