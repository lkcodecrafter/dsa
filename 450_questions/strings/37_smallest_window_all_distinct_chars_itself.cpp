/*
    QUESTION    : Smallest distant window (Smallest window containing all distinct characters of string itself)
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/smallest-distant-window3132/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <climits>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Two-pointer sliding window
// S.C : O(256) = O(1) - Frequency array
class Solution {
public:
    int findSubString(string str) {
        unordered_set<char> distinctChars(str.begin(), str.end());
        int totalDistinct = distinctChars.size();

        vector<int> freq(256, 0);
        int matchedDistinct = 0;
        int minLen = INT_MAX;
        int left = 0;

        for (int right = 0; right < str.length(); right++) {
            if (freq[str[right]] == 0) {
                matchedDistinct++;
            }
            freq[str[right]]++;

            // Shrink window from left
            while (matchedDistinct == totalDistinct) {
                minLen = min(minLen, right - left + 1);

                freq[str[left]]--;
                if (freq[str[left]] == 0) {
                    matchedDistinct--;
                }
                left++;
            }
        }

        return minLen;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `totalDistinct = set(str).size()`.
 * - Expand `right`: if `freq[str[right]] == 0`, `matchedDistinct++`.
 * - While `matchedDistinct == totalDistinct`: `minLen = min(minLen, right - left + 1);` shrink `left`.
 * - Time: O(N), Space: O(1).
 */
