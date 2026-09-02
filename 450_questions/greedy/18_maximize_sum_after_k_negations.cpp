/*
    QUESTION    : Maximize sum after K negations
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximize-sum-after-k-negations1149/1
    LeetCode    : https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/
*/

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N + K log N) - Min-Heap greedily negates smallest element K times
// S.C : O(N)           - Min-Heap storage
class Solution {
public:
    long long int maximizeSum(long long int a[], int n, int k) {
        priority_queue<long long, vector<long long>, greater<long long>> minHeap;

        for (int i = 0; i < n; i++) {
            minHeap.push(a[i]);
        }

        // Negate the smallest element k times
        while (k > 0) {
            long long smallest = minHeap.top();
            minHeap.pop();

            minHeap.push(-smallest);
            k--;
        }

        long long totalSum = 0;
        while (!minHeap.empty()) {
            totalSum += minHeap.top();
            minHeap.pop();
        }

        return totalSum;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Min-Heap. Pop smallest, negate (`-x`), push back, repeated `k` times.
 * - Return sum of all heap elements.
 * - Time: O(N + K log N), Space: O(N).
 */
