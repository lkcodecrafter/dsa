/*
    QUESTION    : Smallest window in a string containing all the characters of another string (Minimum Window Substring)
    Company Tags: Amazon, Microsoft, Google, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/smallest-window-in-a-string-containing-all-the-characters-of-another-string-1587115621/1
    LeetCode    : https://leetcode.com/problems/minimum-window-substring/
*/

#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Sliding window two pointers
// S.C : O(256) = O(1) - Frequency array
class Solution {
public:
    string smallestWindow (string s, string p) {
        if (s.length() < p.length()) return "-1";

        vector<int> mapP(256, 0);
        for (char ch : p) mapP[ch]++;

        vector<int> mapS(256, 0);
        int matchedCount = 0;
        int requiredCount = p.length();

        int minLen = INT_MAX;
        int startIndex = -1;
        int left = 0;

        for (int right = 0; right < s.length(); right++) {
            char rChar = s[right];
            mapS[rChar]++;

            if (mapP[rChar] > 0 && mapS[rChar] <= mapP[rChar]) {
                matchedCount++;
            }

            // Shrink window from left as much as possible once all characters of p are matched
            while (matchedCount == requiredCount) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    startIndex = left;
                }

                char lChar = s[left];
                mapS[lChar]--;

                if (mapP[lChar] > 0 && mapS[lChar] < mapP[lChar]) {
                    matchedCount--;
                }

                left++;
            }
        }

        return (startIndex == -1) ? "-1" : s.substr(startIndex, minLen);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Expand `right`: if `mapS[ch] <= mapP[ch]`, `matchedCount++`.
 * - While `matchedCount == requiredCount`: record min window, shrink `left`.
 * - Time: O(N), Space: O(1).
 */
