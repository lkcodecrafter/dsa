/*
    QUESTION    : Snake and Ladder Problem (Minimum dice throws to reach cell 30 / 100)
    Company Tags: Amazon, Microsoft, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/snake-and-ladder-problem4816/1
    LeetCode    : https://leetcode.com/problems/snakes-and-ladders/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) where N = 30 board cells - BFS finds shortest dice throw path
// S.C : O(N) - Visited array and queue
class Solution {
public:
    int minThrow(int N, int arr[]) {
        vector<int> board(31, -1);

        // Populate ladder/snake destination cells
        for (int i = 0; i < 2 * N; i += 2) {
            board[arr[i]] = arr[i + 1];
        }

        vector<bool> visited(31, false);
        queue<pair<int, int>> q; // {cell, dice_throws}

        q.push({1, 0});
        visited[1] = true;

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            int cell = curr.first;
            int throws = curr.second;

            if (cell == 30) {
                return throws;
            }

            // Try all 6 dice outcomes
            for (int dice = 1; dice <= 6; dice++) {
                int nextCell = cell + dice;

                if (nextCell <= 30) {
                    // Check if ladder or snake exists at nextCell
                    int dest = (board[nextCell] != -1) ? board[nextCell] : nextCell;

                    if (!visited[dest]) {
                        visited[dest] = true;
                        q.push({dest, throws + 1});
                    }
                }
            }
        }

        return -1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - BFS on board cells `1..30`.
 * - Roll dice 1..6: `dest = (board[cell+dice] != -1) ? board[cell+dice] : cell+dice`.
 * - Time: O(N), Space: O(N).
 */
