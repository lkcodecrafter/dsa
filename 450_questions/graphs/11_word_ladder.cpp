/*
    QUESTION    : Word Ladder (Shortest Transformation Sequence Length)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/word-ladder/1
    LeetCode    : https://leetcode.com/problems/word-ladder/
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * L * 26) where L = word length - BFS for shortest path in transformation graph
// S.C : O(N * L)      - Hash set of dictionary words and BFS queue
class Solution {
public:
    int wordLadderLength(string startWord, string targetWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());

        if (dict.find(targetWord) == dict.end()) {
            return 0;
        }

        queue<pair<string, int>> q;
        q.push({startWord, 1});

        if (dict.find(startWord) != dict.end()) {
            dict.erase(startWord);
        }

        while (!q.empty()) {
            string word = q.front().first;
            int steps = q.front().second;
            q.pop();

            if (word == targetWord) {
                return steps;
            }

            // Try changing each character from 'a' to 'z'
            for (int i = 0; i < word.length(); i++) {
                char original = word[i];

                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;

                    if (dict.find(word) != dict.end()) {
                        dict.erase(word); // Prevent revisiting
                        q.push({word, steps + 1});
                    }
                }

                word[i] = original; // Restore
            }
        }

        return 0;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - BFS on word dictionary with queue `{word, steps}`.
 * - Change each character from 'a' to 'z'; if in `dict`, erase from `dict` and push `{new_word, steps + 1}`.
 * - Time: O(N * L * 26), Space: O(N * L).
 */
