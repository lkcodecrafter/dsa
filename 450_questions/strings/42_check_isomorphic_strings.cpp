/*
    QUESTION    : Isomorphic Strings (Check if two given strings are isomorphic to each other)
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/isomorphic-strings-1587115620/1
    LeetCode    : https://leetcode.com/problems/isomorphic-strings/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Bijective 1-to-1 character mapping check
// S.C : O(256) = O(1) - Mapping tables
class Solution {
public:
    bool areIsomorphic(string str1, string str2) {
        if (str1.length() != str2.length()) return false;

        vector<int> map1(256, -1);
        vector<int> map2(256, -1);

        for (int i = 0; i < str1.length(); i++) {
            char c1 = str1[i];
            char c2 = str2[i];

            // If characters have different previous mapping indices, they are not isomorphic
            if (map1[c1] != map2[c2]) {
                return false;
            }

            // Store current index (1-based to distinguish from uninitialized -1)
            map1[c1] = i + 1;
            map2[c2] = i + 1;
        }

        return true;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `map1[c1] != map2[c2] ? return false : map1[c1] = map2[c2] = i + 1`.
 * - Time: O(N), Space: O(1).
 */
