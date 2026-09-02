/*
    QUESTION    : Rasta and Kheshtak (Largest Common Subgrid)
    Company Tags: Google, Directi
    Link        : https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/rasta-and-kheshtak/
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M * log(min(N, M))) - 2D Rolling Hash (Rabin-Karp) + Binary Search on subgrid size
// S.C : O(N * M)                  - Hash set for subgrid fingerprints
class Solution {
private:
    const long long BASE1 = 313;
    const long long MOD = 1000000007;

    bool check(int k, const vector<vector<int>>& A, const vector<vector<int>>& B) {
        if (k == 0) return true;
        int n1 = A.size(), m1 = A[0].size();
        int n2 = B.size(), m2 = B[0].size();
        if (k > min(n1, m1) || k > min(n2, m2)) return false;

        unordered_set<long long> hashes;

        // Compute 2D polynomial hashes for all k x k subgrids in A
        for (int i = 0; i <= n1 - k; i++) {
            for (int j = 0; j <= m1 - k; j++) {
                long long h = 0;
                for (int r = 0; r < k; r++) {
                    for (int c = 0; c < k; c++) {
                        h = (h * BASE1 + A[i + r][j + c]) % MOD;
                    }
                }
                hashes.insert(h);
            }
        }

        // Match against 2D hashes in B
        for (int i = 0; i <= n2 - k; i++) {
            for (int j = 0; j <= m2 - k; j++) {
                long long h = 0;
                for (int r = 0; r < k; r++) {
                    for (int c = 0; c < k; c++) {
                        h = (h * BASE1 + B[i + r][j + c]) % MOD;
                    }
                }
                if (hashes.find(h) != hashes.end()) {
                    return true;
                }
            }
        }

        return false;
    }

public:
    int largestCommonSquare(const vector<vector<int>>& A, const vector<vector<int>>& B) {
        int limit1 = min((int)A.size(), (int)A[0].size());
        int limit2 = min((int)B.size(), (int)B[0].size());
        int high = min(limit1, limit2);
        int low = 0;
        int ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid, A, B)) {
                ans = mid;
                low = mid + 1; // Try larger square
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Monotonic property on square size $k$ $\rightarrow$ Binary Search on answer $[0, \min(N, M)]$.
 * - 2D Rolling Hash for $k \times k$ subgrid verification.
 * - Time: O(N * M * log(min(N, M))), Space: O(N * M).
 */
