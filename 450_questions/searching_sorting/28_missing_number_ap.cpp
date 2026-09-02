/*
    QUESTION    : Arithmetic Number (Check if number exists in Arithmetic Progression)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/arithmetic-number2815/1
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(1) - Pure mathematical modulo arithmetic
// S.C : O(1) - Constant space
class Solution {
public:
    int inSequence(int A, int B, int C) {
        // Case 1: Common difference C is 0
        if (C == 0) {
            return (A == B) ? 1 : 0;
        }

        // Case 2: (B - A) must have same sign as C and must be divisible by C
        if ((B - A) % C == 0 && (B - A) / C >= 0) {
            return 1;
        }

        return 0;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `C == 0`: return `A == B`.
 * - If `(B - A) % C == 0 && (B - A) / C >= 0`: return 1; else 0.
 * - Time: O(1), Space: O(1).
 */
