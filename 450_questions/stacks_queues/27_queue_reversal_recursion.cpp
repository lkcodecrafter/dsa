/*
    QUESTION    : Queue Reversal using Recursion
    Company Tags: Amazon, Microsoft, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/queue-reversal/1
*/

#include <iostream>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Recursion empties queue and pushes back in reversed order
// S.C : O(N) - Recursion call stack
class Solution {
public:
    queue<int> rev(queue<int> q) {
        if (q.empty()) {
            return q;
        }

        int val = q.front();
        q.pop();

        // Recursively reverse remaining queue
        q = rev(q);

        // Enqueue the stored front element at the back
        q.push(val);

        return q;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Base `q.empty()`: `return q;`
 * - `val = q.front(); q.pop(); q = rev(q); q.push(val); return q;`
 * - Time: O(N), Space: O(N).
 */
