/*
    QUESTION    : Maximum difference of zeros and ones in binary string (Kadane's Algorithm)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximum-difference-of-zeros-and-ones-in-binary-string4111/1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Kadane's Algorithm converting '0' to +1 and '1' to -1
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int maxSubstring(string S) {
        int maxEndingHere = 0;
        int maxSoFar = -1;

        for (char ch : S) {
            int val = (ch == '0') ? 1 : -1;

            maxEndingHere = max(val, maxEndingHere + val);
            maxSoFar = max(maxSoFar, maxEndingHere);
        }

        return maxSoFar;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Map `'0' -> +1`, `'1' -> -1`.
 * - Run Kadane's Algorithm: `maxEnding = max(val, maxEnding + val); maxSoFar = max(maxSoFar, maxEnding);`
 * - Time: O(N), Space: O(1).
 */
