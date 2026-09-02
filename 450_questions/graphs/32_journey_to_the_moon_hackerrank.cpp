/*
    QUESTION    : Journey to the Moon (Number of Astronaut Pairs from Different Countries)
    Company Tags: Amazon, Directi
    Link        : https://www.hackerrank.com/challenges/journey-to-the-moon/problem
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - DFS to find country component sizes + suffix sum pair multiplication
// S.C : O(V + E) - Adjacency list and visited array
class Solution {
private:
    int dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        int count = 1;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                count += dfs(neighbor, adj, visited);
            }
        }

        return count;
    }

public:
    long long journeyToMoon(int n, vector<vector<int>> astronaut) {
        vector<vector<int>> adj(n);
        for (auto& pair : astronaut) {
            adj[pair[0]].push_back(pair[1]);
            adj[pair[1]].push_back(pair[0]);
        }

        vector<bool> visited(n, false);
        vector<int> countrySizes;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                countrySizes.push_back(dfs(i, adj, visited));
            }
        }

        // Total pairs from different countries = sum(size[i] * remaining_astronauts)
        long long totalPairs = 0;
        long long remainingAstronauts = n;

        for (int size : countrySizes) {
            remainingAstronauts -= size;
            totalPairs += (long long)size * remainingAstronauts;
        }

        return totalPairs;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Find connected component sizes `countrySizes`.
 * - For each `size`: `remaining -= size; totalPairs += size * remaining;`
 * - Time: O(V + E), Space: O(V + E).
 */
