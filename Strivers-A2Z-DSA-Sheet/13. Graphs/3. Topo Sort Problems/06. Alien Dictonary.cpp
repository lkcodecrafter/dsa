/*
QUESTION:
Given a sorted dictionary of an alien language having N words and K starting
alphabets of the standard dictionary. Find the order of characters in the alien
language.

APPROACH:
- The dictionary is sorted lexicographically according to the rules of the alien
language.
- By comparing adjacent words in the dictionary, we can find the relative order
of characters.
- Specifically, for any two adjacent words, the first character position where
they differ gives us a directed dependency: the character in the first word must
come before the character in the second word (e.g., if "baa" comes before
"abcd", then 'b' comes before 'a').
- We model this as a Directed Acyclic Graph (DAG) where:
  - Vertices are the K characters (mapped to integers 0 to K-1).
  - A directed edge u -> v means character u comes before character v.
- We then find the topological sort of this graph using Kahn's Algorithm (BFS):
  1. Calculate the indegree of all vertices.
  2. Push all vertices with an indegree of 0 (no prerequisites) into a queue.
  3. Dequeue a node, append it to our result string, and decrement the indegree
of its neighbors.
  4. If a neighbor's indegree drops to 0, push it to the queue.
  5. Repeat until the queue is empty.

COMPLEXITY ANALYSIS:
- Time Complexity: O(N * L + K), where N is the number of words, L is the
maximum length of a word, and K is the number of characters. We scan the words
to build the graph, and Kahn's algorithm processes K vertices and at most N-1
edges.
- Space Complexity: O(K + E), where E is the number of unique character
relationship edges (E <= N-1). This space is used by the adjacency list,
indegree array, and the BFS queue.

DRY RUN:

Input: dict = {"baa", "abcd", "abca", "cab", "cad"}, N = 5, K = 4
Characters to order: 'a', 'b', 'c', 'd' (mapped to 0, 1, 2, 3)

1. Graph Construction (Comparing adjacent words):
   - Compare "baa" and "abcd":
     First difference at index 0: 'b' != 'a'.
     Edge: 'b' -> 'a' (1 -> 0). Increment indegree[0].
   - Compare "abcd" and "abca":
     First difference at index 3: 'd' != 'a'.
     Edge: 'd' -> 'a' (3 -> 0). Increment indegree[0].
   - Compare "abca" and "cab":
     First difference at index 0: 'a' != 'c'.
     Edge: 'a' -> 'c' (0 -> 2). Increment indegree[2].
   - Compare "cab" and "cad":
     First difference at index 2: 'b' != 'd'.
     Edge: 'b' -> 'd' (1 -> 3). Increment indegree[3].

   Adjacency List:
   0 ('a') -> [2 ('c')]
   1 ('b') -> [0 ('a'), 3 ('d')]
   2 ('c') -> []
   3 ('d') -> [0 ('a')]

   Indegrees:
   indegree[0] ('a') = 2 (from 1, 3)
   indegree[1] ('b') = 0
   indegree[2] ('c') = 1 (from 0)
   indegree[3] ('d') = 1 (from 1)

2. Kahn's Algorithm (BFS):
   - Initial Queue:
     indegree[1] ('b') == 0 -> Push 1. Queue q = [1]

   - Iteration 1:
     - Pop 1. Output char: 1 + 'a' = 'b'. Result ans = "b".
     - Neighbors of 1: [0, 3].
       - Neighbor 0: indegree[0] becomes 1.
       - Neighbor 3: indegree[3] becomes 0. Push 3. Queue q = [3]

   - Iteration 2:
     - Pop 3. Output char: 3 + 'a' = 'd'. Result ans = "bd".
     - Neighbors of 3: [0].
       - Neighbor 0: indegree[0] becomes 0. Push 0. Queue q = [0]

   - Iteration 3:
     - Pop 0. Output char: 0 + 'a' = 'a'. Result ans = "bda".
     - Neighbors of 0: [2].
       - Neighbor 2: indegree[2] becomes 0. Push 2. Queue q = [2]

   - Iteration 4:
     - Pop 2. Output char: 2 + 'a' = 'c'. Result ans = "bdac".
     - Neighbors of 2: None.

   - Queue is empty. Return ans = "bdac".
*/

#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Helper function to build the adjacency list and compute indegrees from the
// dictionary
void buildGraph(string dict[], int N, vector<vector<int>> &adj,
                vector<int> &indegree) {
  for (int i = 0; i < N - 1; i++) {
    string word1 = dict[i];
    string word2 = dict[i + 1];

    int minLength = min(word1.length(), word2.length());
    for (int j = 0; j < minLength; j++) {
      if (word1[j] != word2[j]) {
        int u = word1[j] - 'a';
        int v = word2[j] - 'a';

        adj[u].push_back(v);
        indegree[v]++;
        break; // Only the first differing character determines the sorted order
      }
    }
  }
}

// Function to find the ordering of characters in the alien language
string findOrder(string dict[], int N, int K) {
  vector<vector<int>> adj(K);
  vector<int> indegree(K, 0);

  // 1. Build the graph representing character order rules
  buildGraph(dict, N, adj, indegree);

  // 2. Queue all starting characters (indegree == 0)
  queue<int> q;
  for (int i = 0; i < K; i++) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }

  string orderOfChars = "";

  // 3. BFS (Topological Sort / Kahn's Algorithm)
  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    // Convert current node integer back to character
    orderOfChars += (curr + 'a');

    for (auto neighbor : adj[curr]) {
      indegree[neighbor]--;

      // If all dependency characters are processed, push to queue
      if (indegree[neighbor] == 0) {
        q.push(neighbor);
      }
    }
  }

  return orderOfChars;
}
