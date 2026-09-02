/*
    QUESTION    : Choose and Swap (Lexicographically smallest string by swapping all occurrences of two characters)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/choose-and-swap0531/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Set tracking unique characters in sorted order
// S.C : O(26) = O(1) - Set of alphabet characters
class Solution {
public:
    string chooseandswap(string a) {
        set<char> s;
        for (char ch : a) {
            s.insert(ch);
        }

        for (int i = 0; i < a.length(); i++) {
            s.erase(a[i]); // Remove current character as candidate

            if (s.empty()) break;

            char smallestAvailable = *s.begin();

            // If a strictly smaller character appears later in the string, swap them!
            if (smallestAvailable < a[i]) {
                char ch1 = a[i];
                char ch2 = smallestAvailable;

                for (int j = 0; j < a.length(); j++) {
                    if (a[j] == ch1) a[j] = ch2;
                    else if (a[j] == ch2) a[j] = ch1;
                }

                break; // Only one swap allowed
            }
        }

        return a;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `set<char> s(a.begin(), a.end())`.
 * - For each char: `s.erase(a[i])`. If `*s.begin() < a[i]`, swap all occurrences of `a[i]` and `*s.begin()`.
 * - Time: O(N), Space: O(1).
 */
