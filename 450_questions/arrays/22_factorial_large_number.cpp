/*
 * QUESTION: Find factorial of a large number
 * Link: https://practice.geeksforgeeks.org/problems/factorials-of-large-numbers/0
 * 
 * Input: N = 5
 * Output: 120
 * 
 * Input: N = 10
 * Output: 3628800
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Multiplies a single integer x with the large number stored in reverse order in digits.
void multiply(std::vector<int>& digits, int x) {
    int carry = 0;
    
    for (size_t i = 0; i < digits.size(); i++) {
        int prod = digits[i] * x + carry;
        digits[i] = prod % 10; // Store the last digit
        carry = prod / 10;     // Carry over the rest
    }
    
    // Put remaining carry into digits
    while (carry > 0) {
        digits.push_back(carry % 10);
        carry /= 10;
    }
}

// Calculates factorial of N and returns it as a vector of digits (most significant digit first).
std::vector<int> factorial(int N) {
    std::vector<int> digits;
    digits.push_back(1); // 0! or 1! starts with 1
    
    for (int x = 2; x <= N; x++) {
        multiply(digits, x);
    }
    
    // Reverse digits to get the most significant digit first
    std::reverse(digits.begin(), digits.end());
    return digits;
}

/*
 * DRY RUN (N = 4):
 * digits initialized: {1}
 * Loop x from 2 to 4:
 * 
 * | x | digits before | Calculation per digit & carry | digits after (reversed representation) |
 * | :-| :------------ | :---------------------------- | :------------------------------------- |
 * | 2 | {1}           | 1*2 + 0 = 2 -> digits[0]=2    | {2}                                    |
 * | 3 | {2}           | 2*3 + 0 = 6 -> digits[0]=6    | {6}                                    |
 * | 4 | {6}           | 6*4 + 0 = 24                  | {4, 2}                                 |
 * |   |               | digits[0]=4, carry=2          |                                        |
 * |   |               | carry > 0 -> push_back(2)     |                                        |
 * 
 * Final reversed digits before reversing: {4, 2}.
 * Reversing gives: {2, 4} (which is 24).
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Remember how we multiplied numbers on paper in grade school: 
 * Multiply the digit, write the unit digit at the bottom, and carry over the tens digit. 
 * Since the number is too big for a single variable, we use an array of digits to represent the paper.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Represent the big number as a vector of digits (stored in reverse order, i.e., units place first).
 * - Initialize the vector with `{1}`.
 * - Loop `x` from `2` to `N`:
 *   - For each digit: `prod = digit * x + carry`. Update `digit = prod % 10`, `carry = prod / 10`.
 *   - Append remaining `carry` digits to the end.
 * - Reverse the final vector and return.
 * - Time Complexity: O(N * (Number of digits in N!)), which is O(N^2 log N).
 * - Space Complexity: O(Number of digits in N!) which is O(N log N).
 */
