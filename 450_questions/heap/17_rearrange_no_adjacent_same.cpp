/*
    QUESTION    : Rearrange characters in a string such that no two adjacent are same
    Company Tags: Amazon, Microsoft, Goldman Sachs
    GfG Link    : https://practice.geeksforgeeks.org/problems/rearrange-characters/0
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log(Alphabet_Size)) = O(N) since alphabet size <= 26
// S.C : O(26) = O(1)            - Priority queue and frequency map storage
class Solution {
public:
    string rearrangeString(string str) {
        int n = str.length();
        unordered_map<char, int> freq;

        for (char ch : str) {
            freq[ch]++;
            if (freq[ch] > (n + 1) / 2) {
                return "-1"; // Impossible to rearrange
            }
        }

        // Max-Heap: pair<frequency, char>
        priority_queue<pair<int, char>> maxHeap;
        for (auto &entry : freq) {
            maxHeap.push({entry.second, entry.first});
        }

        string result = "";
        pair<int, char> prev = {-1, '#'}; // Tracks previously placed character to avoid back-to-back placement

        while (!maxHeap.empty()) {
            auto curr = maxHeap.top();
            maxHeap.pop();

            result.push_back(curr.second);
            curr.first--;

            // If the previously placed character still has remaining frequency, push it back to heap
            if (prev.first > 0) {
                maxHeap.push(prev);
            }

            // Update prev to be the current character
            prev = curr;
        }

        return (result.length() == n) ? result : "-1";
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF PREV-POINTER DELAYED RE-INSERTION
 * ============================================================================
 *
 * String: "aaabc", n = 5
 * Max-Heap: [ (3, 'a'), (1, 'b'), (1, 'c') ]
 *
 * 1. Pop (3, 'a') -> Result: "a", prev = (2, 'a'). Heap: [ (1, 'b'), (1, 'c') ]
 * 2. Pop (1, 'b') -> Result: "ab", Push prev (2, 'a'), prev = (0, 'b'). Heap: [ (2, 'a'), (1, 'c') ]
 * 3. Pop (2, 'a') -> Result: "aba", prev = (1, 'a'). Heap: [ (1, 'c') ]
 * 4. Pop (1, 'c') -> Result: "abac", Push prev (1, 'a'), prev = (0, 'c'). Heap: [ (1, 'a') ]
 * 5. Pop (1, 'a') -> Result: "abaca", prev = (0, 'a'). Heap: [ ]
 *
 * Final Result: "abaca"
 *
 * ============================================================================
 * DRY RUN (str = "bbbaa")
 * ============================================================================
 * | Step | Popped Character | Result String | Delayed `prev` Character Held | Re-inserted to Heap |
 * | :--- | :--------------- | :------------ | :---------------------------- | :------------------ |
 * | 1    | 'b' (freq 3->2)   | "b"           | (2, 'b')                      | -                   |
 * | 2    | 'a' (freq 2->1)   | "ba"          | (1, 'a')                      | Re-insert (2, 'b')  |
 * | 3    | 'b' (freq 2->1)   | "bab"         | (1, 'b')                      | Re-insert (1, 'a')  |
 * | 4    | 'a' (freq 1->0)   | "baba"        | (0, 'a')                      | Re-insert (1, 'b')  |
 * | 5    | 'b' (freq 1->0)   | "babab"       | (0, 'b')                      | None                |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Cooldown Bench"
 * When a character plays a turn (`result.push_back`), it sits on the cooldown bench (`prev`).
 * Only after a different character plays next does the benched character get allowed back
 * into the priority queue (`maxHeap.push(prev)`).
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `freq[ch] > (n + 1) / 2`, return `"-1"`.
 * - Pop most frequent `curr` from Max-Heap, append to `result`, decrement `curr.first`.
 * - If `prev.first > 0`: `maxHeap.push(prev)`.
 * - Update `prev = curr`.
 * - Time: O(N), Space: O(1).
 */
