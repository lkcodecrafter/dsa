/*
    QUESTION    : First negative integer in every window of size k
    Company Tags: Amazon, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/first-negative-integer-in-every-window-of-size-k3345/1
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Queue stores negative element indices within current sliding window
// S.C : O(K) - Queue storing indices
vector<long long> printFirstNegativeInteger(long long int A[], long long int N, long long int K) {
    vector<long long> result;
    deque<long long> dq; // Stores indices of negative numbers

    // Process first window of size K
    for (int i = 0; i < K; i++) {
        if (A[i] < 0) {
            dq.push_back(i);
        }
    }

    // Record answer for first window
    if (!dq.empty()) {
        result.push_back(A[dq.front()]);
    } else {
        result.push_back(0);
    }

    // Process subsequent sliding windows
    for (int i = K; i < N; i++) {
        // Remove indices outside window [i - K + 1, i]
        if (!dq.empty() && dq.front() <= i - K) {
            dq.pop_front();
        }

        // Add current element if negative
        if (A[i] < 0) {
            dq.push_back(i);
        }

        // Record answer for current window
        if (!dq.empty()) {
            result.push_back(A[dq.front()]);
        } else {
            result.push_back(0);
        }
    }

    return result;
}

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `deque<int> dq` stores indices of negative elements.
 * - If `dq.front() <= i - K`: `dq.pop_front()`.
 * - If `A[i] < 0`: `dq.push_back(i)`.
 * - Window answer is `dq.empty() ? 0 : A[dq.front()]`.
 * - Time: O(N), Space: O(K).
 */
