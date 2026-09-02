/*
    QUESTION    : Reverse a String
    Company Tags: Amazon, Microsoft, Adobe
    LeetCode    : https://leetcode.com/problems/reverse-string/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Two pointers in-place swap
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `left = 0, right = n - 1`.
 * - `while (left < right) { swap(s[left++], s[right--]); }`
 * - Time: O(N), Space: O(1).
 */
