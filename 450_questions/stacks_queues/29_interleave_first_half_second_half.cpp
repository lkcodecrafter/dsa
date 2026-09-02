/*
    QUESTION    : Interleave the first half of the queue with second half
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/interleave-first-half-queue-second-half/
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Interleaving using queue and stack
// S.C : O(N) - Stack storing first half
class Solution {
public:
    vector<int> rearrangeQueue(queue<int> &q) {
        int n = q.size();
        int half = n / 2;
        queue<int> firstHalf;

        // Push first half of elements into auxiliary queue
        for (int i = 0; i < half; i++) {
            firstHalf.push(q.front());
            q.pop();
        }

        vector<int> result;

        // Interleave elements: 1 from firstHalf, 1 from q (secondHalf)
        while (!firstHalf.empty()) {
            result.push_back(firstHalf.front());
            firstHalf.pop();

            result.push_back(q.front());
            q.pop();
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Dequeue first `N/2` elements into `firstHalf` queue.
 * - Alternately take elements from `firstHalf` and `q`.
 * - Time: O(N), Space: O(N).
 */
