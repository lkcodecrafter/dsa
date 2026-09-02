/*
    QUESTION    : Reverse first K elements of a Queue
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/reverse-first-k-elements-of-queue/1
*/

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Uses stack to reverse first K elements + queue rotation for remaining N - K
// S.C : O(K) - Stack storing first K elements
class Solution {
public:
    queue<int> modifyQueue(queue<int> q, int k) {
        if (q.empty() || k <= 0 || k > q.size()) return q;

        stack<int> st;

        // Step 1: Pop first K elements from queue and push to stack
        for (int i = 0; i < k; i++) {
            st.push(q.front());
            q.pop();
        }

        // Step 2: Pop from stack and push back to queue (first K are now reversed at the rear)
        while (!st.empty()) {
            q.push(st.top());
            st.pop();
        }

        // Step 3: Rotate remaining (N - K) elements to the rear to restore their order
        int remaining = q.size() - k;
        for (int i = 0; i < remaining; i++) {
            q.push(q.front());
            q.pop();
        }

        return q;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Push first `k` elements to `stack`.
 * - Pop stack and push back to `q`.
 * - Rotate remaining `N - k` elements: `q.push(q.front()); q.pop();`
 * - Time: O(N), Space: O(K).
 */
