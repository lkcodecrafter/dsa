/*
    QUESTION    : Sum of minimum and maximum elements of all subarrays of size k
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/sum-minimum-maximum-elements-subarrays-size-k/
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Dual monotonic deques maintain running min and max for sliding window of size K
// S.C : O(K) - Deques of size at most K
class Solution {
public:
    long long sumOfMinAndMax(vector<int> &arr, int n, int k) {
        deque<int> minDq; // Monotonic Increasing Deque (Min at front)
        deque<int> maxDq; // Monotonic Decreasing Deque (Max at front)
        long long totalSum = 0;

        for (int i = 0; i < n; i++) {
            // Remove out-of-window elements
            if (!minDq.empty() && minDq.front() <= i - k) minDq.pop_front();
            if (!maxDq.empty() && maxDq.front() <= i - k) maxDq.pop_front();

            // Maintain monotonic increasing order for min
            while (!minDq.empty() && arr[minDq.back()] >= arr[i]) {
                minDq.pop_back();
            }

            // Maintain monotonic decreasing order for max
            while (!maxDq.empty() && arr[maxDq.back()] <= arr[i]) {
                maxDq.pop_back();
            }

            minDq.push_back(i);
            maxDq.push_back(i);

            // Add min + max to total sum once window reaches size k
            if (i >= k - 1) {
                totalSum += (arr[minDq.front()] + arr[maxDq.front()]);
            }
        }

        return totalSum;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `minDq` (increasing) gives running minimum; `maxDq` (decreasing) gives running maximum.
 * - If `i >= k - 1`: `totalSum += (arr[minDq.front()] + arr[maxDq.front()])`.
 * - Time: O(N), Space: O(K).
 */
