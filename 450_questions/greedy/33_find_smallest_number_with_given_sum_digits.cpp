/*
    QUESTION    : Smallest number with given sum of digits and number of digits
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/smallest-number5829/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(D) where D is number of digits - Greedy construction from least significant digit backwards
// S.C : O(D) - Result string
class Solution {
public:
    string smallestNumber(int S, int D) {
        // Maximum sum possible with D digits is 9 * D
        if (S > 9 * D || (S == 0 && D > 1)) {
            return "-1";
        }

        vector<int> digits(D, 0);

        // Reserve 1 for the most significant digit (index 0) to avoid leading zero
        S -= 1;

        // Greedily fill digits with 9 from right to left
        for (int i = D - 1; i > 0; i--) {
            if (S >= 9) {
                digits[i] = 9;
                S -= 9;
            } else {
                digits[i] = S;
                S = 0;
            }
        }

        // Add remaining sum + 1 to the most significant digit
        digits[0] = S + 1;

        string result = "";
        for (int d : digits) {
            result += to_string(d);
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `S > 9 * D` return "-1".
 * - Reserve `S -= 1` for first digit.
 * - Greedily fill rightmost digits with `min(9, S)`.
 * - First digit = `S + 1`.
 * - Time: O(D), Space: O(D).
 */
