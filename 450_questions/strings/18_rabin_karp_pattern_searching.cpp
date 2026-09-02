/*
    QUESTION    : Rabin-Karp Algorithm for Pattern Searching
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N + M) average case, O(N * M) worst case
// S.C : O(1) - Rolling hash constant space
class Solution {
private:
    const int d = 256;      // Alphabet size
    const int q = 1000000007; // Prime modulus for hash

public:
    vector<int> search(string pat, string txt) {
        vector<int> result;
        int m = pat.length();
        int n = txt.length();

        if (m > n) return result;

        long long p = 0; // Hash value for pattern
        long long t = 0; // Hash value for text window
        long long h = 1;

        // The value of h would be "pow(d, m-1)%q"
        for (int i = 0; i < m - 1; i++) {
            h = (h * d) % q;
        }

        // Calculate initial hash value of pattern and first window of text
        for (int i = 0; i < m; i++) {
            p = (d * p + pat[i]) % q;
            t = (d * t + txt[i]) % q;
        }

        // Slide the pattern over text one by one
        for (int i = 0; i <= n - m; i++) {
            // If hash values match, verify character-by-character to avoid spurious hits
            if (p == t) {
                bool match = true;
                for (int j = 0; j < m; j++) {
                    if (txt[i + j] != pat[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    result.push_back(i + 1); // 1-based indexing
                }
            }

            // Calculate hash value for next window of text: remove leading digit, add trailing digit
            if (i < n - m) {
                t = (d * (t - txt[i] * h) + txt[i + m]) % q;
                if (t < 0) t = (t + q);
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Rolling Hash formula: `t = (d * (t - txt[i]*h) + txt[i+m]) % q`.
 * - If hash matches, verify characters directly.
 * - Time: O(N + M) avg, Space: O(1).
 */
