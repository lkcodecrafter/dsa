/*
    QUESTION    : Calculate square of a number without using *, / and pow()
    Company Tags: Amazon, Adobe
    GfG Link    : https://www.geeksforgeeks.org/calculate-square-of-a-number-without-using-and-pow/
*/

#include <iostream>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(log N) - Halves n at each recursive step (similar to fast exponentiation)
// S.C : O(log N) - Recursion stack space
class Solution {
public:
    int square(int n) {
        // Base Case
        if (n == 0) return 0;

        // Handle negative numbers: (-n)^2 = n^2
        if (n < 0) n = -n;

        // Mathematical identity:
        // If n is even: n = 2*x  =>  n^2 = (2*x)^2 = 4 * x^2 = (square(x) << 2)
        // If n is odd:  n = 2*x + 1 => n^2 = (2*x + 1)^2 = 4*x^2 + 4*x + 1 = (square(x) << 2) + (x << 2) + 1

        int x = n >> 1; // x = floor(n / 2)

        if ((n & 1) == 0) {
            // Even case
            return (square(x) << 2);
        } else {
            // Odd case
            return ((square(x) << 2) + (x << 2) + 1);
        }
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF SQUARE RECURSION
 * ============================================================================
 *
 * Example: square(5)
 *   n = 5 (odd) -> x = 5 >> 1 = 2
 *   square(5) = (square(2) << 2) + (2 << 2) + 1
 *
 *   square(2):
 *     n = 2 (even) -> x = 2 >> 1 = 1
 *     square(2) = (square(1) << 2)
 *
 *     square(1):
 *       n = 1 (odd) -> x = 1 >> 1 = 0
 *       square(1) = (square(0) << 2) + (0 << 2) + 1 = 0 + 0 + 1 = 1.
 *
 *   Backtrack to square(2): 1 << 2 = 4.
 *   Backtrack to square(5): (4 << 2) + (2 << 2) + 1 = 16 + 8 + 1 = 25!
 *
 * ============================================================================
 * DRY RUN (n = 6)
 * ============================================================================
 * | Call | n | x = n >> 1 | Is Even? | Formula | Computed Result |
 * | :--- | :-| :--------- | :------- | :------ | :-------------- |
 * | 1    | 6 | 3          | Yes      | square(3) << 2 | 9 << 2 = 36    |
 * | 2    | 3 | 1          | No       | (square(1)<<2) + (1<<2) + 1 | (1<<2) + 4 + 1 = 9 |
 * | 3    | 1 | 0          | No       | (square(0)<<2) + (0<<2) + 1 | 0 + 0 + 1 = 1      |
 * | 4    | 0 | -          | Base     | return 0 | 0              |
 *
 * Output = 36.
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The 4-Square Expansion"
 * Algebra identity $(2x + 1)^2 = 4x^2 + 4x + 1$.
 * Multiplying by 4 in binary is just shifting left twice (`<< 2`).
 * Reduce problem size by half ($x = n/2$) at every step until you hit zero!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Let $x = n >> 1$.
 * - If $n$ is even: return `square(x) << 2`.
 * - If $n$ is odd: return `(square(x) << 2) + (x << 2) + 1`.
 * - Base Case: `if (n == 0) return 0;`
 * - Time Complexity: O(log N), Space Complexity: O(log N).
 */
