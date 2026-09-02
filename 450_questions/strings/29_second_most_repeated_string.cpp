/*
    QUESTION    : Second most repeated string in a sequence
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/second-most-repeated-string-in-a-sequence0534/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * L) - Hash map frequency count + finding first and second maximum
// S.C : O(N * L) - Hash map storing strings
class Solution {
public:
    string secFrequent(string arr[], int n) {
        unordered_map<string, int> freq;

        for (int i = 0; i < n; i++) {
            freq[arr[i]]++;
        }

        int maxFreq = INT_MIN;
        int secMaxFreq = INT_MIN;

        for (auto& entry : freq) {
            if (entry.second > maxFreq) {
                secMaxFreq = maxFreq;
                maxFreq = entry.second;
            } else if (entry.second > secMaxFreq && entry.second != maxFreq) {
                secMaxFreq = entry.second;
            }
        }

        for (auto& entry : freq) {
            if (entry.second == secMaxFreq) {
                return entry.first;
            }
        }

        return "";
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `freq[arr[i]]++`.
 * - Find first and second max frequency `maxFreq` and `secMaxFreq`.
 * - Return string matching `secMaxFreq`.
 * - Time: O(N * L), Space: O(N * L).
 */
