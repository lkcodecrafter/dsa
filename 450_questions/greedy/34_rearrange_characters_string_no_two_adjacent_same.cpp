/*
    QUESTION    : Rearrange characters in a string such that no two adjacent are same (Max Heap Method)
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/rearrange-characters4649/1
    LeetCode    : https://leetcode.com/problems/reorganize-string/
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log(Alphabet)) = O(N) since alphabet <= 26
// S.C : O(26) = O(1) - Max-Heap
class Solution {
public:
    string rearrangeString(string str) {
        vector<int> freq(26, 0);
        for (char ch : str) freq[ch - 'a']++;

        priority_queue<pair<int, char>> maxHeap;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                if (freq[i] > (str.length() + 1) / 2) return "-1";
                maxHeap.push({freq[i], (char)('a' + i)});
            }
        }

        string result = "";
        pair<int, char> prev = {-1, '#'};

        while (!maxHeap.empty()) {
            auto cur = maxHeap.top();
            maxHeap.pop();

            result.push_back(cur.second);

            if (prev.first > 0) {
                maxHeap.push(prev);
            }

            cur.first--;
            prev = cur;
        }

        return (result.length() == str.length()) ? result : "-1";
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Max-Heap of character frequencies.
 * - Append top char, pop, hold in `prev`, re-insert on subsequent iteration.
 * - Time: O(N), Space: O(1).
 */
