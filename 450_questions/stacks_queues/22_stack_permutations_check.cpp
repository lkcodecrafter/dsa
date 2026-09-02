/*
    QUESTION    : Stack Permutations (Check if an array is stack permutation of other)
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/stack-permutations-check-if-an-array-is-stack-permutation-of-other/
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Elements pushed and popped from stack at most once
// S.C : O(N) - Stack
class Solution {
public:
    int isStackPermutation(int N, vector<int> &A, vector<int> &B) {
        stack<int> st;
        int j = 0; // Pointer for target permutation array B

        for (int i = 0; i < N; i++) {
            st.push(A[i]);

            // While top of stack matches next expected element in B
            while (!st.empty() && st.top() == B[j]) {
                st.pop();
                j++;
            }
        }

        // If stack is completely emptied, array B is a valid stack permutation
        return (st.empty() && j == N) ? 1 : 0;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `j = 0;`
 * - For each `x` in `A`:
 *     - `st.push(x);`
 *     - `while (!st.empty() && st.top() == B[j]) { st.pop(); j++; }`
 * - Return `st.empty() && j == N`.
 * - Time: O(N), Space: O(N).
 */
