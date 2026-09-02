/*
    QUESTION    : Convert a sentence into its equivalent mobile numeric keypad sequence
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/convert-sentence-equivalent-mobile-numeric-keypad-sequence/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Direct keypad lookup table
// S.C : O(1) - Fixed keypad mapping
class Solution {
public:
    string printSequence(string S) {
        string keypad[] = {
            "2", "22", "222",        // A, B, C
            "3", "33", "333",        // D, E, F
            "4", "44", "444",        // G, H, I
            "5", "55", "555",        // J, K, L
            "6", "66", "666",        // M, N, O
            "7", "77", "777", "7777",// P, Q, R, S
            "8", "88", "888",        // T, U, V
            "9", "99", "999", "9999" // W, X, Y, Z
        };

        string result = "";

        for (char ch : S) {
            if (ch == ' ') {
                result += "0";
            } else if (ch >= 'A' && ch <= 'Z') {
                result += keypad[ch - 'A'];
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Lookup table `keypad[26]`.
 * - If space, append "0"; else append `keypad[ch - 'A']`.
 * - Time: O(N), Space: O(1).
 */
