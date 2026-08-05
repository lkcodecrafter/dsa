// Leetcode 127. Word Ladder

/*Here is a concrete, step-by-step demo using the exact file you have open right
now:

08. Word Ladder.cpp
.

This is exactly how you should study and practice each topic to fit the 20-hour
budget:

Step 1: Watch the Video (Time: ~12 Mins)
Open the video "G-29. Word Ladder - I | BFS" on YouTube.
Set the speed to 1.25x or 1.5x.
Focus on the "Why": Listen to Striver explain why we use BFS instead of DFS (BFS
searches level-by-level, making it perfect for finding the shortest
transformation sequence). Do not copy code yet. Just watch him explain the set
and queue logic. Step 2: The 3-Minute Dry Run Grab a notepad/paper (or open a
scratchpad file) and trace a tiny example yourself before coding:

Input: beginWord = "der", endWord = "dfs", wordList = ["der", "dfr", "dfs"]
Trace:
Add {"der", 1} to Queue. Put all words in a Set.
Pop {"der", 1}. Change character by character:
aer, ber, ... dfr (exists in set!). Push {"dfr", 2} to Queue, erase "dfr" from
Set to mark as visited. Pop {"dfr", 2}. Change character by character: dfs
(exists in set!). Push {"dfs", 3} to Queue. Pop {"dfs", 3}. Since dfs ==
endWord, return 3. Step 3: Write the Code (Time: ~7 Mins) Write the clean,
optimized C++ implementation. Focus on leveraging the standard BFS pattern
(Queue + Visited state) optimized for string mutation:

cpp
*/

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;
int wordLadderLength(string beginWord, string endWord,
                     vector<string> &wordList) {
  // 1. Put all words into a set for O(1) lookup and deletion
  unordered_set<string> st(wordList.begin(), wordList.end());

  // 2. Queue stores {word, step_count}
  queue<pair<string, int>> q;
  q.push({beginWord, 1});

  // If the beginWord is in the set, erase it to avoid visiting it again
  st.erase(beginWord);

  // 3. BFS Traversal
  while (!q.empty()) {
    string word = q.front().first;
    int steps = q.front().second;
    q.pop();

    // If we reach the target word, return the step count
    if (word == endWord)
      return steps;

    // Try changing each character from 'a' to 'z'
    for (int i = 0; i < word.length(); i++) {
      char original = word[i];

      for (char ch = 'a'; ch <= 'z'; ch++) {
        word[i] = ch;

        // If the mutated word exists in the set (i.e., not visited yet)
        if (st.find(word) != st.end()) {
          st.erase(word); // mark as visited
          q.push({word, steps + 1});
        }
      }
      // Restore original character for next index mutation
      word[i] = original;
    }
  }

  return 0; // Return 0 if no transformation sequence is possible
}

/*
Step 4: Verify and Move On
Test your code on LeetCode/GeeksforGeeks (using the links in Striver's sheet).
If it passes, move on immediately. Do not waste time writing redundant comments
or formatting. If it fails, check your dry run logic vs your code logic to find
the bug quickly.
*/