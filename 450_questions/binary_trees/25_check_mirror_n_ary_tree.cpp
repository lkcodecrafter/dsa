/*
    QUESTION    : Check Mirror in N-ary Tree
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/check-mirror-in-n-ary-tree/0
*/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N + E) - Hash map + Stack reversal verification
// S.C : O(N + E) - Hash map of stacks
class Solution {
public:
    int checkMirrorTree(int n, int e, int A[], int B[]) {
        // Map from parent node to stack of its children in Tree 1
        unordered_map<int, stack<int>> adjMap;

        // Tree 1: Push children in order
        for (int i = 0; i < 2 * e; i += 2) {
            int u = A[i];
            int v = A[i + 1];
            adjMap[u].push(v);
        }

        // Tree 2: Verify that children are traversed in reverse order (stack top matches)
        for (int i = 0; i < 2 * e; i += 2) {
            int u = B[i];
            int v = B[i + 1];

            if (adjMap[u].empty() || adjMap[u].top() != v) {
                return 0; // Not a mirror
            }
            adjMap[u].pop();
        }

        return 1; // Valid mirror
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF N-ARY MIRROR VERIFICATION
 * ============================================================================
 *
 * Tree 1: 1 -> [2, 3]  (Stack for 1 has top = 3, bottom = 2)
 * Tree 2: 1 -> [3, 2]
 *
 * Match:
 * - In Tree 2, first child of 1 is 3 (matches stack top 3!). Pop 3.
 * - Next child of 1 is 2 (matches stack top 2!). Pop 2.
 * Valid Mirror!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Store children of Tree 1 in `unordered_map<int, stack<int>>`.
 * - For each child in Tree 2, check `if (map[u].top() != v) return 0; map[u].pop();`.
 * - Time: O(E), Space: O(E).
 */
