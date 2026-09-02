/*
    QUESTION    : Square root of an integer (Count Squares / Integer Sqrt)
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/count-squares3649/1
    LeetCode    : https://leetcode.com/problems/sqrtx/
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(log N) - Binary search on answer space [1...N]
// S.C : O(1)     - Constant auxiliary space
class Solution {
public:
    long long int floorSqrt(long long int x) {
        if (x == 0 || x == 1) return x;

        long long low = 1, high = x, ans = 1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (mid * mid == x) {
                return mid;
            } else if (mid * mid < x) {
                ans = mid; // Candidate floor square root
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Binary search on `[1, x]`.
 * - If `mid * mid <= x`: `ans = mid; low = mid + 1;`
 * - Else: `high = mid - 1;`
 * - Time: O(log x), Space: O(1).
 */
