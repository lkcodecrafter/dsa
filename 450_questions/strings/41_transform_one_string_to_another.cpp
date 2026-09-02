/*
    QUESTION    : Transform One String to Another using Minimum Number of Given Operation (Front shift only)
    Company Tags: Google
    GfG Link    : https://www.geeksforgeeks.org/transform-one-string-to-another-using-minimum-number-of-given-operation/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Two pointers matching characters from right to left
// S.C : O(256) = O(1) - Anagram frequency check
class Solution {
public:
    int minOps(string& A, string& B) {
        int m = A.length();
        int n = B.length();

        if (m != n) return -1;

        // Verify strings are anagrams of each other
        vector<int> count(256, 0);
        for (int i = 0; i < n; i++) {
            count[A[i]]++;
            count[B[i]]--;
        }
        for (int i = 0; i < 256; i++) {
            if (count[i] != 0) return -1;
        }

        int ops = 0;
        int i = n - 1;
        int j = n - 1;

        // Match characters from right to left
        while (i >= 0) {
            if (A[i] == B[j]) {
                i--;
                j--;
            } else {
                // Character A[i] needs to be shifted to the front
                ops++;
                i--;
            }
        }

        return ops;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Check anagrams.
 * - Match backwards `i = n - 1, j = n - 1`.
 * - If `A[i] == B[j]`: `i--; j--;` else `ops++; i--;`
 * - Time: O(N), Space: O(1).
 */
