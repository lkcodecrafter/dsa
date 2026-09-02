/*
    QUESTION    : Reorganize String (No two adjacent characters are the same)
    Company Tags: Amazon, Google, Facebook
    GfG Link    : https://practice.geeksforgeeks.org/problems/rearrange-characters/0
    LeetCode    : https://leetcode.com/problems/reorganize-string/
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log(Alphabet)) = O(N) since alphabet size <= 26
// S.C : O(26) = O(1)       - Frequency map and Max-Heap storage
class Solution {
public:
    string reorganizeString(string s) {
        int n = s.length();
        unordered_map<char, int> freq;

        // 1. Count character frequencies
        for (char ch : s) {
            freq[ch]++;
            // If any character appears more than (n + 1) / 2 times, it's impossible
            if (freq[ch] > (n + 1) / 2) {
                return "";
            }
        }

        // 2. Max-Heap ordered by highest frequency: pair<frequency, char>
        priority_queue<pair<int, char>> maxHeap;
        for (auto &entry : freq) {
            maxHeap.push({entry.second, entry.first});
        }

        string result = "";

        // 3. Greedily pick two distinct most frequent characters at a time
        while (maxHeap.size() >= 2) {
            auto first = maxHeap.top(); maxHeap.pop();
            auto second = maxHeap.top(); maxHeap.pop();

            result.push_back(first.second);
            result.push_back(second.second);

            if (--first.first > 0) {
                maxHeap.push(first);
            }
            if (--second.first > 0) {
                maxHeap.push(second);
            }
        }

        // 4. If one character is remaining
        if (!maxHeap.empty()) {
            result.push_back(maxHeap.top().second);
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF GREEDY TWO-CHARACTER CONSUMPTION
 * ============================================================================
 *
 * Input: "aaabbc"
 * Frequencies: 'a': 3, 'b': 2, 'c': 1
 * Max-Heap: [ (3, 'a'), (2, 'b'), (1, 'c') ]
 *
 * Step 1: Pop top 2 -> 'a' and 'b' -> Result: "ab"
 *   Remaining: [ (2, 'a'), (1, 'c'), (1, 'b') ]
 * Step 2: Pop top 2 -> 'a' and 'c' -> Result: "abac"
 *   Remaining: [ (1, 'a'), (1, 'b') ]
 * Step 3: Pop top 2 -> 'a' and 'b' -> Result: "abacab"
 *   Heap empty!
 *
 * Valid Reorganized String: "abacab"
 *
 * ============================================================================
 * DRY RUN (s = "aab")
 * ============================================================================
 * | Step | Heap State            | Popped Pair | Appended to Result | Re-inserted Pair | Result State |
 * | :--- | :-------------------- | :---------- | :----------------- | :--------------- | :----------- |
 * | 1    | {(2, 'a'), (1, 'b')}  | 'a' and 'b' | "ab"               | (1, 'a')         | "ab"         |
 * | 2    | {(1, 'a')}            | 'a' (Last)  | 'a'                | -                | "aba"        |
 *
 * Output = "aba".
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Rival School Dance Pairing"
 * You have students from different rival schools. To prevent fights (adjacent same characters),
 * always pair up the two most populated schools at each turn.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Feasibility Check: If `max_frequency > (N + 1) / 2`, return `""`.
 * - Max-Heap stores `{freq, char}`.
 * - While `maxHeap.size() >= 2`: pop top 2 most frequent, append both, decrement counts, re-insert.
 * - Time: O(N), Space: O(1).
 */
