/*
    QUESTION    : Power Set: Print all subsequences/subsets of a string using Bit Manipulation
    Company Tags: Amazon, Microsoft, Snapdeal
    GfG Link    : https://practice.geeksforgeeks.org/problems/power-set4302/1
    LeetCode    : https://leetcode.com/problems/subsets/
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * 2^N) - Iterates through all 2^N bitmasks; each mask takes O(N) to build string
// S.C : O(1)       - Auxiliary space (excluding result vector)
class Solution {
public:
    vector<string> AllPossibleStrings(string s) {
        vector<string> result;
        int n = s.length();
        int totalSubsets = (1 << n); // 2^n total subsets

        // Iterate through all bitmasks from 1 to 2^n - 1 (excluding empty subset if required)
        for (int mask = 1; mask < totalSubsets; mask++) {
            string current = "";
            for (int i = 0; i < n; i++) {
                // If the i-th bit of the mask is set, include s[i]
                if (mask & (1 << i)) {
                    current.push_back(s[i]);
                }
            }
            result.push_back(current);
        }

        // Sort result in lexicographical order as per standard problem requirement
        sort(result.begin(), result.end());
        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BITMASK SUBSETS
 * ============================================================================
 *
 * String s = "abc", n = 3
 * Total Subsets = 2^3 = 8
 *
 * Mask (Dec)   Mask (Binary: b2 b1 b0)   Included Chars   Subset String
 * ---------------------------------------------------------------------
 * 0            0 0 0                     None             "" (Empty)
 * 1            0 0 1                     s[0]             "a"
 * 2            0 1 0                     s[1]             "b"
 * 3            0 1 1                     s[0], s[1]       "ab"
 * 4            1 0 0                     s[2]             "c"
 * 5            1 0 1                     s[0], s[2]       "ac"
 * 6            1 1 0                     s[1], s[2]       "bc"
 * 7            1 1 1                     s[0], s[1], s[2] "abc"
 *
 * ============================================================================
 * DRY RUN (s = "ab")
 * ============================================================================
 * | mask | mask (Binary) | i = 0 (bit 0 set?) | i = 1 (bit 1 set?) | Constructed String |
 * | :--- | :------------ | :----------------- | :----------------- | :----------------- |
 * | 1    | 01            | Yes -> 'a'         | No                 | "a"                |
 * | 2    | 10            | No                 | Yes -> 'b'         | "b"                |
 * | 3    | 11            | Yes -> 'a'         | Yes -> 'b'         | "ab"               |
 *
 * Result: {"a", "ab", "b"}
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The 0/1 Toggle Switches"
 * For $N$ items, each item has a switch: $0 = \text{leave}$, $1 = \text{take}$.
 * Counting in binary from $0$ to $2^N - 1$ naturally enumerates every possible
 * combination of switch settings (the Power Set).
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `totalSubsets = (1 << n)` $= 2^n$.
 * - Loop `mask` from $1$ to $2^n - 1$:
 *     - If `(mask & (1 << i))` is non-zero, append `s[i]`.
 * - Sort results lexicographically with `std::sort()`.
 * - Time: O(N * 2^N), Space: O(1) auxiliary.
 */
