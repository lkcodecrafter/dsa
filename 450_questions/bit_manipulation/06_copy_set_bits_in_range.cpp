/*
    QUESTION    : Copy set bits in a given range [L, R]
    Company Tags: Adobe, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/set-all-odd-bits/0
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(1) - Bitwise mask generation and bitwise OR operation
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int setSetBit(int x, int y, int l, int r) {
        // Step 1: Calculate the length of the range [l, r]
        int rangeLen = r - l + 1;

        // Step 2: Create a mask with `rangeLen` consecutive 1s
        // Example: If rangeLen = 3, mask = (1 << 3) - 1 = 8 - 1 = 7 (Binary: 111)
        int mask = (1LL << rangeLen) - 1;

        // Step 3: Shift the mask so that the 1s align with position `l` (1-based)
        mask = (mask << (l - 1));

        // Step 4: Extract the set bits of `y` in the range [l, r]
        int bitsToCopy = y & mask;

        // Step 5: Copy the extracted bits into `x` using bitwise OR
        return x | bitsToCopy;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF MASKING RANGE [L, R]
 * ============================================================================
 *
 * Example: x = 10 (1010), y = 13 (1101), l = 2, r = 3 (1-based)
 *
 * rangeLen = 3 - 2 + 1 = 2
 * mask = ((1 << 2) - 1) << (2 - 1) = 3 << 1 = 6 (Binary: 0 1 1 0)
 *
 * y (13)          =  1 1 0 1
 * mask (6)        =  0 1 1 0
 * --------------------------
 * bitsToCopy      =  0 1 0 0  (Bit 3 of y is 1)
 *
 * x (10)          =  1 0 1 0
 * bitsToCopy      =  0 1 0 0
 * --------------------------
 * x | bitsToCopy  =  1 1 1 0  (Value = 14)
 *
 * ============================================================================
 * DRY RUN (x = 8 -> 1000, y = 7 -> 0111, l = 1, r = 2)
 * ============================================================================
 * | Step | Variable | Computation                                    | Value |
 * | :--- | :------- | :--------------------------------------------- | :---- |
 * | 1    | rangeLen | 2 - 1 + 1                                      | 2     |
 * | 2    | mask     | ((1 << 2) - 1) << (1 - 1) = (3) << 0           | 0011  |
 * | 3    | bits     | y & mask = 7 & 3                               | 0011  |
 * | 4    | result   | x | bits = 8 | 3                               | 1011 (11)|
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Window Stencil"
 * Cut a rectangular hole in a piece of paper spanning columns `L` through `R` (`mask`).
 * Place the paper over number `y` to see only its active lights (`y & mask`).
 * Paste those active lights directly onto panel `x` (`x | bits`).
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `mask = ((1LL << (r - l + 1)) - 1) << (l - 1)` creates `1`s from index `l-1` to `r-1`.
 * - `bitsToCopy = y & mask`.
 * - Return `x | bitsToCopy`.
 * - Time Complexity: O(1), Space Complexity: O(1).
 */
