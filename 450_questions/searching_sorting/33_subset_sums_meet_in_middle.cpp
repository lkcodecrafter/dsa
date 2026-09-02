/*
    QUESTION    : SUBSUMS - Subset Sums (Meet in the Middle)
    Company Tags: Google
    Link        : https://www.spoj.com/problems/SUBSUMS/
    LeetCode    : https://leetcode.com/problems/closest-subsequence-sum/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(2^(N/2) * (N/2)) - Meet in the Middle splits N <= 34 into two halves of size N/2
// S.C : O(2^(N/2))        - Vectors storing subset sums of both halves
class Solution {
private:
    void generateSubsetSums(const vector<long long>& arr, int start, int end, vector<long long>& sums) {
        int n = end - start;
        for (int mask = 0; mask < (1 << n); mask++) {
            long long sum = 0;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    sum += arr[start + i];
                }
            }
            sums.push_back(sum);
        }
    }

public:
    long long countSubsetsInRange(vector<long long>& arr, int n, long long A, long long B) {
        vector<long long> leftSums, rightSums;

        // Step 1: Generate all 2^(N/2) subset sums for left and right halves
        generateSubsetSums(arr, 0, n / 2, leftSums);
        generateSubsetSums(arr, n / 2, n, rightSums);

        // Step 2: Sort right sums for binary search
        sort(rightSums.begin(), rightSums.end());

        long long count = 0;

        // Step 3: For each left sum, binary search valid right sums in range [A - l, B - l]
        for (long long l : leftSums) {
            auto low = lower_bound(rightSums.begin(), rightSums.end(), A - l);
            auto high = upper_bound(rightSums.begin(), rightSums.end(), B - l);
            count += (high - low);
        }

        return count;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Meet in the Middle: Split into 2 halves of size $N/2 \le 17 \rightarrow 2^{17} \approx 1.3 \times 10^5$ operations.
 * - Generate sums, sort right, binary search range $[A - l, B - l]$ with `upper_bound - lower_bound`.
 * - Time: O(2^(N/2) * log(2^(N/2))), Space: O(2^(N/2)).
 */
