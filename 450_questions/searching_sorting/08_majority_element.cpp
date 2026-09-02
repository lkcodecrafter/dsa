/*
    QUESTION    : Majority Element (Appearing more than N/2 times)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/majority-element-1587115620/1
    LeetCode    : https://leetcode.com/problems/majority-element/
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Boyer-Moore Voting Algorithm in a single pass + verification pass
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int majorityElement(int a[], int size) {
        int candidate = -1;
        int count = 0;

        // Step 1: Find candidate using Boyer-Moore Voting Algorithm
        for (int i = 0; i < size; i++) {
            if (count == 0) {
                candidate = a[i];
                count = 1;
            } else if (a[i] == candidate) {
                count++;
            } else {
                count--;
            }
        }

        // Step 2: Verify candidate appears strictly more than size / 2 times
        int actualCount = 0;
        for (int i = 0; i < size; i++) {
            if (a[i] == candidate) {
                actualCount++;
            }
        }

        return (actualCount > size / 2) ? candidate : -1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Boyer-Moore Voting:
 *     - If `count == 0`: `candidate = a[i]; count = 1;`
 *     - Else if `a[i] == candidate`: `count++`; else `count--`.
 * - Verify if `actualCount > size / 2`.
 * - Time: O(N), Space: O(1).
 */
