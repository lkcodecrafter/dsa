/*
QUESTION:-
Given an m x n matrix board containing 'X' and 'O', capture all regions that are
4-directionally surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

The Surrounded Regions problem is a common grid problem (for example, on
LeetCode #130).

Problem

Given an m × n board containing 'X' and 'O':

Capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's.
Any 'O' connected to the border (directly or indirectly) should not be flipped.
Example

Input:

X X X X
X O O X
X X O X
X O X X

Output:

X X X X
X X X X
X X X X
X O X X

The bottom 'O' remains because it is connected to the border.

Approach (DFS/BFS)

Instead of finding surrounded regions, find the safe regions.

Traverse all border cells.
Whenever a border 'O' is found, perform DFS/BFS and mark all connected 'O's as
temporary (say '#'). Traverse the board: Convert remaining 'O' → 'X' (they are
surrounded). Convert '#' back → 'O'. Time Complexity O(m × n) Space Complexity
O(m × n) in the worst case due to recursion/queue.
C++ DFS Solution
*/

#include <vector>
using namespace std;

class Solution {
public:
  int m, n;

  void dfs(vector<vector<char>> &board, int i, int j) {
    if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] != 'O')
      return;

    board[i][j] = '#';

    dfs(board, i + 1, j);
    dfs(board, i - 1, j);
    dfs(board, i, j + 1);
    dfs(board, i, j - 1);
  }

  void solve(vector<vector<char>> &board) {
    if (board.empty())
      return;

    m = board.size();
    n = board[0].size();

    // First and last column
    for (int i = 0; i < m; i++) {
      if (board[i][0] == 'O')
        dfs(board, i, 0);
      if (board[i][n - 1] == 'O')
        dfs(board, i, n - 1);
    }

    // First and last row
    for (int j = 0; j < n; j++) {
      if (board[0][j] == 'O')
        dfs(board, 0, j);
      if (board[m - 1][j] == 'O')
        dfs(board, m - 1, j);
    }

    // Flip surrounded regions
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (board[i][j] == 'O')
          board[i][j] = 'X';
        else if (board[i][j] == '#')
          board[i][j] = 'O';
      }
    }
  }
};

/* Why start from the border?

Any 'O' connected to a border cannot be surrounded by 'X'. By marking all
border-connected 'O's first, every remaining 'O' is guaranteed to be enclosed
and can safely be flipped. This avoids checking each region individually and
ensures an O(m × n) solution.
*/