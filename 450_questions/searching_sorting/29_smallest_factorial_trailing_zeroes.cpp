/*
    QUESTION    : Smallest number with at least N trailing zeroes in factorial
    Company Tags: Amazon, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/smallest-factorial-number5929/1
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(log(5 * N) * log5(N)) - Binary search on answer + Legendre's formula for counting factors of 5
// S.C : O(1)                    - Constant auxiliary space
class Solution {
private:
    // Legendre's Formula: counts trailing zeros in p!
    int countTrailingZeros(int p) {
        int count = 0;
        for (int f = 5; p / f > 0; f *= 5) {
            count += p / f;
        }
        return count;
    }

public:
    int findNum(int n) {
        if (n == 1) return 5;

        // Binary search range [0, 5 * n]
        int low = 0;
        int high = 5 * n;
        int ans = low;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (countTrailingZeros(mid) >= n) {
                ans = mid;
                high = mid - 1; // Try finding smaller number
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Legendre formula: `zeros(p) = p/5 + p/25 + p/125 + ...`
 * - Binary search on `[0, 5*n]`.
 * - If `zeros(mid) >= n`: `ans = mid; high = mid - 1;` else `low = mid + 1;`.
 * - Time: O(log N), Space: O(1).
 */
