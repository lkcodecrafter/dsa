/*
    QUESTION    : Count number of bits to be flipped to convert A to B
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/bit-difference-1587115620/1
    LeetCode    : https://leetcode.com/problems/minimum-bit-flips-to-convert-number/
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(K) - K is the number of differing bits between A and B (K <= 32)
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int countBitsFlip(int a, int b) {
        // XOR gives 1 at all bit positions where bits in A and B differ
        int diff = a ^ b;

        // Count set bits in diff using Brian Kernighan's Algorithm
        int flips = 0;
        while (diff > 0) {
            diff = diff & (diff - 1);
            flips++;
        }

        return flips;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BIT FLIPPING
 * ============================================================================
 *
 * Example: A = 10 (1010), B = 20 (10100)
 *
 * A      =  0 1 0 1 0  (10)
 * B      =  1 0 1 0 0  (20)
 * -------------------------
 * A ^ B  =  1 1 1 1 0  (30) -> 4 differing bit positions (set bits)!
 *
 * Number of bits to flip = 4.
 *
 * ============================================================================
 * DRY RUN (A = 20 -> 10100, B = 25 -> 11001)
 * ============================================================================
 * | Step | diff = A ^ B | diff (Binary) | Kernighan Operation | flips |
 * | :--- | :----------- | :------------ | :------------------ | :---- |
 * | Init | 20 ^ 25 = 13 | 01101         | -                   | 0     |
 * | 1    | 13           | 01101         | 13 & 12 = 12 (01100)| 1     |
 * | 2    | 12           | 01100         | 12 & 11 = 8  (01000)| 2     |
 * | 3    | 8            | 01000         | 8 & 7   = 0  (00000)| 3     |
 * | End  | 0            | -             | Loop Ends           | 3     |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Toggle Switch Inspector"
 * To see how many light switches differ between two control panels,
 * compare them with an XOR logic gate. Every switch that disagrees turns ON (`1`).
 * Count the glowing switches to know how many toggles are needed.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `diff = A ^ B` flags all mismatched bit positions as `1`.
 * - Count set bits in `diff` using `diff & (diff - 1)` or `__builtin_popcount(a ^ b)`.
 * - Time: O(differing bits) <= 32, Space: O(1).
 */
