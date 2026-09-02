/*
    QUESTION    : Minimum sum of two numbers formed from digits of an array
    Company Tags: Amazon, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-sum4058/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting the digits of array + O(N) string addition
// S.C : O(N)       - Space for storing string representations of two numbers
class Solution {
private:
    // Helper to add two large numbers represented as strings
    string addStrings(const string &num1, const string &num2) {
        string sumStr = "";
        int i = num1.length() - 1;
        int j = num2.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0) {
            int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
            int digit2 = (j >= 0) ? num2[j--] - '0' : 0;

            int total = digit1 + digit2 + carry;
            sumStr.push_back((total % 10) + '0');
            carry = total / 10;
        }

        reverse(sumStr.begin(), sumStr.end());

        // Remove leading zeros
        int start = 0;
        while (start < sumStr.length() - 1 && sumStr[start] == '0') {
            start++;
        }

        return sumStr.substr(start);
    }

public:
    string minSum(int arr[], int n) {
        // Step 1: Sort the digits in ascending order
        sort(arr, arr + n);

        string num1 = "";
        string num2 = "";

        // Step 2: Distribute digits alternately to num1 and num2 to minimize place values
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0 && num1.empty() && num2.empty()) {
                continue; // Ignore leading zeros
            }
            if (i % 2 == 0) {
                num1.push_back(arr[i] + '0');
            } else {
                num2.push_back(arr[i] + '0');
            }
        }

        if (num1.empty() && num2.empty()) return "0";
        if (num1.empty()) return num2;
        if (num2.empty()) return num1;

        // Step 3: Return the sum of the two numbers
        return addStrings(num1, num2);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF ALTERNATING DIGIT DISTRIBUTION
 * ============================================================================
 *
 * Given Digits: [ 6, 8, 4, 5, 2, 3 ]
 *
 * Step 1: Sort ascending -> [ 2, 3, 4, 5, 6, 8 ]
 *
 * Step 2: Alternate to num1 and num2:
 *   num1 (even indices): 2, 4, 6 -> "246"
 *   num2 (odd indices) : 3, 5, 8 -> "358"
 *
 * Step 3: Sum = 246 + 358 = 604!
 *
 * ============================================================================
 * DRY RUN (arr = {5, 3, 0, 7, 4})
 * ============================================================================
 * | Step | Sorted Array | Alternate Distribution | String Values | Sum Output |
 * | :--- | :----------- | :--------------------- | :------------ | :--------- |
 * | 1    | {0, 3, 4, 5, 7} | num1 gets 0,4,7     | num1 = "47"   | -          |
 * | 2    |              | num2 gets 3,5         | num2 = "35"   | -          |
 * | 3    | Add strings  | 47 + 35               | 82            | "82"       |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "Dealing Cards into Two Hands"
 * To build two small numbers from sorted digit cards:
 * Deal card 1 to Player A (highest place value), card 2 to Player B,
 * card 3 to Player A (next place value), card 4 to Player B...
 * Add the two hands together!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Sort array of digits ascending.
 * - Distribute alternately: even index to `num1`, odd index to `num2`.
 * - Add `num1` and `num2` as strings to prevent overflow.
 * - Trim leading zeroes.
 * - Time: O(N log N), Space: O(N).
 */
