/*
    QUESTION    : Find duplicate characters in a string
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/print-all-the-duplicates-in-the-input-string/
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Hash map frequency counter
// S.C : O(K) where K <= 256 - Frequency table
class Solution {
public:
    void printDuplicates(string str) {
        unordered_map<char, int> count;

        for (char ch : str) {
            count[ch]++;
        }

        for (auto it : count) {
            if (it.second > 1) {
                cout << it.first << ", count = " << it.second << "\n";
            }
        }
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `count[ch]++`.
 * - Print keys where `count[ch] > 1`.
 * - Time: O(N), Space: O(1) / O(256).
 */
