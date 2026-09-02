/*
    QUESTION    : Roman Number to Integer
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/roman-number-to-integer3201/1
    LeetCode    : https://leetcode.com/problems/roman-to-integer/
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear scan comparing adjacent Roman numeral values
// S.C : O(1) - Constant auxiliary space
class Solution {
private:
    int value(char r) {
        switch (r) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default: return 0;
        }
    }

public:
    int romanToDecimal(string &str) {
        int total = 0;
        int n = str.length();

        for (int i = 0; i < n; i++) {
            int s1 = value(str[i]);

            // If current symbol is smaller than next symbol, subtract it (e.g. IV = 5 - 1 = 4)
            if (i + 1 < n) {
                int s2 = value(str[i + 1]);
                if (s1 >= s2) {
                    total += s1;
                } else {
                    total += (s2 - s1);
                    i++; // Skip next character
                }
            } else {
                total += s1;
            }
        }

        return total;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `val(str[i]) < val(str[i+1])`: `total += (val[i+1] - val[i]); i++;`
 * - Else: `total += val[i]`.
 * - Time: O(N), Space: O(1).
 */
