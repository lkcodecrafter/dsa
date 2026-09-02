/*
    QUESTION    : Boyer Moore Algorithm for Pattern Searching (Bad Character Heuristic)
    Company Tags: Google, Amazon
    GfG Link    : https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N / M) best case, O(N * M) worst case
// S.C : O(256) = O(1) - Bad character lookup table
class Solution {
private:
    void badCharHeuristic(const string& str, int size, int badchar[256]) {
        for (int i = 0; i < 256; i++) {
            badchar[i] = -1;
        }
        for (int i = 0; i < size; i++) {
            badchar[(int)str[i]] = i;
        }
    }

public:
    vector<int> search(string txt, string pat) {
        vector<int> result;
        int m = pat.size();
        int n = txt.size();

        int badchar[256];
        badCharHeuristic(pat, m, badchar);

        int s = 0; // Shift of pattern with respect to text

        while (s <= (n - m)) {
            int j = m - 1;

            // Reduce index j while characters of pattern and text match at current shift s
            while (j >= 0 && pat[j] == txt[s + j]) {
                j--;
            }

            // Pattern present at current shift
            if (j < 0) {
                result.push_back(s);
                s += (s + m < n) ? m - badchar[(int)txt[s + m]] : 1;
            } else {
                // Shift pattern so bad character aligns with last occurrence in pattern
                s += max(1, j - badchar[(int)txt[s + j]]);
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Precompute `badchar[256]` with last index of each character in pattern.
 * - Match backwards from `j = m - 1`. Shift `s += max(1, j - badchar[txt[s + j]])`.
 * - Time: O(N / M) best, O(N * M) worst. Space: O(1).
 */
