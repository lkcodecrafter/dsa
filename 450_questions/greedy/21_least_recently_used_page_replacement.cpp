/*
    QUESTION    : Page Faults in LRU (Least Recently Used Page Replacement Algorithm)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/page-faults-in-lru5603/1
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <climits>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * C) where C = capacity - LRU cache simulation
// S.C : O(C)     - Memory frame hash set and last used index map
class Solution {
public:
    int pageFaults(int N, int C, int pages[]) {
        unordered_set<int> memory;
        unordered_map<int, int> lastUsed;
        int pageFaultCount = 0;

        for (int i = 0; i < N; i++) {
            int page = pages[i];

            // If page is not in memory -> Page Fault occurs!
            if (memory.find(page) == memory.end()) {
                pageFaultCount++;

                // If frames are full, evict least recently used page
                if (memory.size() == C) {
                    int lruPage = -1;
                    int minLastUsed = INT_MAX;

                    for (int p : memory) {
                        if (lastUsed[p] < minLastUsed) {
                            minLastUsed = lastUsed[p];
                            lruPage = p;
                        }
                    }

                    memory.erase(lruPage);
                }

                memory.insert(page);
            }

            // Update last used timestamp for current page
            lastUsed[page] = i;
        }

        return pageFaultCount;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If page missing: `pageFaults++`; if memory full, evict page with smallest `lastUsed[p]`.
 * - `lastUsed[page] = i;`
 * - Time: O(N * C), Space: O(C).
 */
