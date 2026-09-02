/*
    QUESTION    : Alien Dictionary (Find Order of Characters)
    Company Tags: Amazon, Microsoft, Google, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/alien-dictionary/1
    LeetCode    : https://leetcode.com/problems/alien-dictionary/
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * L + K) - Graph construction from adjacent word diffs + Kahn's Topological Sort
// S.C : O(K)         - In-degree array and adjacency list
class Solution {
public:
    string findOrder(string dict[], int N, int K) {
        vector<vector<int>> adj(K);
        vector<int> inDegree(K, 0);

        // Step 1: Compare adjacent words in dictionary to find character precedence
        for (int i = 0; i < N - 1; i++) {
            string w1 = dict[i];
            string w2 = dict[i + 1];
            int len = min(w1.length(), w2.length());

            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    adj[w1[j] - 'a'].push_back(w2[j] - 'a');
                    inDegree[w2[j] - 'a']++;
                    break; // Only first mismatch determines order
                }
            }
        }

        // Step 2: Kahn's Topological Sort
        queue<int> q;
        for (int i = 0; i < K; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        string order = "";

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            order.push_back((char)('a' + u));

            for (int v : adj[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        return order;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Compare adjacent words `w1` & `w2`; first differing char creates edge `w1[j] -> w2[j]`.
 * - Run Kahn's Algorithm on $K$ letters.
 * - Time: O(N * L + K), Space: O(K).
 */
