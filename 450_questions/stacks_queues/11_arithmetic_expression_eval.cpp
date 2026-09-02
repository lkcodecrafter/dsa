/*
    QUESTION    : Arithmetic Expression Evaluation (Infix Expression Evaluation)
    Company Tags: Amazon, Google, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/arithmetic-expression-evalution/
    LeetCode    : https://leetcode.com/problems/basic-calculator-ii/
*/

#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Evaluates infix arithmetic expression with operator precedence
// S.C : O(N) - Stacks for values and operators
class Solution {
private:
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    int applyOp(int a, int b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
        }
        return 0;
    }

public:
    int evaluate(string tokens) {
        stack<int> values;
        stack<char> ops;

        for (int i = 0; i < tokens.length(); i++) {
            if (tokens[i] == ' ') continue;

            // 1. Current token is an opening brace
            if (tokens[i] == '(') {
                ops.push(tokens[i]);
            }
            // 2. Current token is a number
            else if (isdigit(tokens[i])) {
                int val = 0;
                while (i < tokens.length() && isdigit(tokens[i])) {
                    val = (val * 10) + (tokens[i] - '0');
                    i++;
                }
                values.push(val);
                i--; // Step back to balance loop increment
            }
            // 3. Closing brace: solve entire bracket
            else if (tokens[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    int val2 = values.top(); values.pop();
                    int val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                if (!ops.empty()) ops.pop(); // Pop '('
            }
            // 4. Operator encountered
            else {
                while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                    int val2 = values.top(); values.pop();
                    int val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                ops.push(tokens[i]);
            }
        }

        // Apply remaining operators to remaining values
        while (!ops.empty()) {
            int val2 = values.top(); values.pop();
            int val1 = values.top(); values.pop();
            char op = ops.top(); ops.pop();
            values.push(applyOp(val1, val2, op));
        }

        return values.top();
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `values` stack and `ops` stack.
 * - While `precedence(ops.top()) >= precedence(curr)`: pop 2 values, 1 op, apply and push result.
 * - Time: O(N), Space: O(N).
 */
