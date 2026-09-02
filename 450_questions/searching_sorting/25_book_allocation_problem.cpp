/*
    QUESTION    : Allocate minimum number of pages (Book Allocation Problem)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1
    LeetCode    : https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
*/

#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * log(Sum_Pages - Max_Page)) - Binary Search on answer space
// S.C : O(1)                             - Constant auxiliary space
class Solution {
private:
    bool isPossible(int A[], int N, int M, long long maxPagesPerStudent) {
        int studentsCount = 1;
        long long currentPagesAllocated = 0;

        for (int i = 0; i < N; i++) {
            if (A[i] > maxPagesPerStudent) {
                return false; // Single book exceeds limit
            }

            if (currentPagesAllocated + A[i] > maxPagesPerStudent) {
                studentsCount++;
                currentPagesAllocated = A[i];
                if (studentsCount > M) return false;
            } else {
                currentPagesAllocated += A[i];
            }
        }

        return true;
    }

public:
    long long findPages(int n, int arr[], int m) {
        if (m > n) return -1; // More students than books

        long long low = *max_element(arr, arr + n);
        long long high = 0;
        for (int i = 0; i < n; i++) high += arr[i];

        long long ans = -1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (isPossible(arr, n, m, mid)) {
                ans = mid;
                high = mid - 1; // Try minimizing max pages
            } else {
                low = mid + 1;  // Increase page limit
            }
        }

        return ans;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Binary Search range: `low = max(arr)`, `high = sum(arr)`.
 * - Greedy check: allocate books sequentially; if sum exceeds `mid`, `studentsCount++`.
 * - If `isPossible`: `ans = mid; high = mid - 1;` else `low = mid + 1;`.
 * - Time: O(N log(sum)), Space: O(1).
 */
