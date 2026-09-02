/*
    QUESTION    : Generate IP Addresses (Restore IP Addresses)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/generate-ip-addresses/1
    LeetCode    : https://leetcode.com/problems/restore-ip-addresses/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(1) - Constant number of IP combinations (3^4 <= 81 checks)
// S.C : O(1) - Result array
class Solution {
private:
    bool isValid(const string& s) {
        if (s.empty() || s.length() > 3) return false;
        if (s.length() > 1 && s[0] == '0') return false; // Leading zero invalid
        int num = stoi(s);
        return num >= 0 && num <= 255;
    }

public:
    vector<string> genIp(string s) {
        vector<string> result;
        int n = s.length();
        if (n < 4 || n > 12) return result;

        for (int i = 1; i < n && i <= 3; i++) {
            for (int j = i + 1; j < n && j <= i + 3; j++) {
                for (int k = j + 1; k < n && k <= j + 3; k++) {
                    string s1 = s.substr(0, i);
                    string s2 = s.substr(i, j - i);
                    string s3 = s.substr(j, k - j);
                    string s4 = s.substr(k);

                    if (isValid(s1) && isValid(s2) && isValid(s3) && isValid(s4)) {
                        result.push_back(s1 + "." + s2 + "." + s3 + "." + s4);
                    }
                }
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - 3 nested loops to split string into 4 parts `s1, s2, s3, s4`.
 * - `isValid(s)`: length 1..3, no leading '0', value $\in [0, 255]$.
 * - Time: O(1), Space: O(1).
 */
