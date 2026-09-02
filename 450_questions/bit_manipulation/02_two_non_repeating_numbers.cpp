/*
    QUESTION    : Find the two non-repeating elements in an array of repeating elements
    Company Tags: Amazon, Flipkart, MakeMyTrip, Accolite
    GfG Link    : https://practice.geeksforgeeks.org/problems/finding-the-numbers0215/1
    LeetCode    : https://leetcode.com/problems/single-number-iii/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Two passes over the array of size N
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    vector<int> singleNumber(vector<int> &nums) {
        // Step 1: XOR all elements. Pairs will cancel out (x ^ x = 0), leaving (num1 ^ num2)
        int overallXor = 0;
        for (int num : nums) {
            overallXor ^= num;
        }

        // Step 2: Find rightmost set bit in overallXor
        // Using unsigned int to prevent overflow with INT_MIN
        unsigned int rightmostSetBit = overallXor & (-static_cast<unsigned int>(overallXor));

        // Step 3: Divide numbers into two groups based on whether that bit is set
        int num1 = 0;
        int num2 = 0;

        for (int num : nums) {
            if (num & rightmostSetBit) {
                num1 ^= num; // Group 1 (bit is set)
            } else {
                num2 ^= num; // Group 2 (bit is not set)
            }
        }

        // Return the two distinct elements in ascending order
        if (num1 > num2) swap(num1, num2);
        return {num1, num2};
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF XOR BIT PARTITIONING
 * ============================================================================
 *
 * Array: [ 1, 2, 3, 2, 1, 4 ]
 * Pairs: (1, 1), (2, 2) cancel out.
 * Non-repeating elements: 3 (011) and 4 (100).
 *
 * Step 1: Overall XOR = 3 ^ 4 = 7 (Binary: 111)
 * Step 2: Rightmost set bit = 7 & (-7) = 1 (Binary: 001, bit position 0).
 *
 * Step 3: Partition elements by bit 0:
 * - Group A (0th bit = 1): [ 1, 3, 1 ] -> XOR = 1 ^ 3 ^ 1 = 3!
 * - Group B (0th bit = 0): [ 2, 2, 4 ] -> XOR = 2 ^ 2 ^ 4 = 4!
 *
 * Result: {3, 4}
 *
 * ============================================================================
 * DRY RUN
 * ============================================================================
 * | Step | Operation             | Value / State                               |
 * | :--- | :-------------------- | :------------------------------------------ |
 * | 1    | Compute overallXor    | 1 ^ 2 ^ 3 ^ 2 ^ 1 ^ 4 = 7 (0111)            |
 * | 2    | rightmostSetBit       | 7 & -7 = 1 (0001)                           |
 * | 3    | Group A (bit 0 == 1)  | 1 ^ 3 ^ 1 = 3                               |
 * | 4    | Group B (bit 0 == 0)  | 2 ^ 2 ^ 4 = 4                               |
 * | 5    | Sort & Return         | {3, 4}                                      |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Two Lost Travelers"
 * All paired travelers cancel each other out in the census (`XOR`).
 * The final XOR is the difference between the two lost travelers.
 * Find any single feature where they disagree (`rightmostSetBit`),
 * split the town into two camps based on that feature, and XOR each camp
 * to reveal each unique traveler.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `overallXor = xor` of all elements $= num_1 \oplus num_2$.
 * - `mask = overallXor & (-overallXor)` gives the rightmost differing bit.
 * - Loop over array: if `(x & mask)` is non-zero, XOR into `num1`; else XOR into `num2`.
 * - Time Complexity: O(N), Space Complexity: O(1).
 */
