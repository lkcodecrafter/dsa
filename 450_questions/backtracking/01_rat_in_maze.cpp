/*
    MY YOUTUBE VIDEO ON THIS Qn : https://www.youtube.com/watch?v=wXwZSytYrIs
    Company Tags                : Amazon, Microsoft, Expedia
    GfG Link                    :
   https://www.geeksforgeeks.org/problems/rat-in-a-maze-problem/1
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ (Approach 1:
 * Explicit 4 Calls)
 * ************************************************************/
// T.C : O(3^(n^2)) - At each cell, at most 3 directions to explore (cannot go
// back immediately) S.C : O(L * X)   - L = Length of path, X = number of paths
// (recursion stack + result storage)
class Solution {
public:
  vector<string> result;

  // Boundary check helper function
  bool isSafe(int i, int j, int n) {
    return i >= 0 && i < n && j >= 0 && j < n;
  }

  // Backtracking DFS Function
  void solve(int i, int j, vector<vector<int>> &m, int n, string &temp) {
    // Base Condition: Out of bounds or hit an obstacle/already visited cell (0)
    if (!isSafe(i, j, n) || m[i][j] == 0) {
      return;
    }
    // Destination reached at bottom-right cell (n-1, n-1)
    if (i == n - 1 && j == n - 1) {
      result.push_back(temp);
      return;
    }

    // 1. Choose: Mark cell as visited in-place (0) to avoid extra visited
    // matrix
    m[i][j] = 0;

    // Explore in Alphabetical Order: 'D' -> 'L' -> 'R' -> 'U' for sorted output
    // Down
    temp.push_back('D');
    solve(i + 1, j, m, n, temp);
    temp.pop_back();

    // Left
    temp.push_back('L');
    solve(i, j - 1, m, n, temp);
    temp.pop_back();

    // Right
    temp.push_back('R');
    solve(i, j + 1, m, n, temp);
    temp.pop_back();

    // Up
    temp.push_back('U');
    solve(i - 1, j, m, n, temp);
    temp.pop_back();

    // 3. Backtrack / Unchoose: Restore cell value to 1 for other path
    // explorations
    m[i][j] = 1;
  }

  vector<string> findPath(vector<vector<int>> &m, int n) {
    result.clear();
    if (n == 0 || m[0][0] == 0 || m[n - 1][n - 1] == 0) {
      return result;
    }
    string temp = "";
    solve(0, 0, m, n, temp);
    return result;
  }
};

/************************************************************ C++ (Approach 2:
 * Clean Loop with Direction Vectors)
 * ************************************************************/
// T.C : O(3^(n^2))
// S.C : O(L * X)
class SolutionOptimized {
private:
  // Direction offsets and characters in alphabetical order ('D', 'L', 'R', 'U')
  int di[4] = {1, 0, 0, -1};
  int dj[4] = {0, -1, 1, 0};
  string dir = "DLRU";

  void solve(int i, int j, vector<vector<int>> &m, int n, string &temp,
             vector<string> &result) {
    if (i == n - 1 && j == n - 1) {
      result.push_back(temp);
      return;
    }

    m[i][j] = 0; // Mark visited in-place

    for (int k = 0; k < 4; k++) {
      int next_i = i + di[k];
      int next_j = j + dj[k];

      if (next_i >= 0 && next_i < n && next_j >= 0 && next_j < n &&
          m[next_i][next_j] == 1) {
        temp.push_back(dir[k]);
        solve(next_i, next_j, m, n, temp, result);
        temp.pop_back(); // Backtrack
      }
    }

    m[i][j] = 1; // Restore cell
  }

public:
  vector<string> findPath(vector<vector<int>> &m, int n) {
    vector<string> result;
    if (n == 0 || m[0][0] == 0 || m[n - 1][n - 1] == 0) {
      return result;
    }
    string temp = "";
    solve(0, 0, m, n, temp, result);
    return result;
  }
};

/*
 * ============================================================================
 * JAVA IMPLEMENTATION (Reference)
 * ============================================================================
 * class Solution {
 *     private static int[] di = {+1, 0, 0, -1};
 *     private static int[] dj = {0, -1, +1, 0};
 *
 *     public static void solve(int[][] m, int n, int[][] vis, int i, int j,
 * ArrayList<String> ars, String ref) { if (i == n - 1 && j == n - 1) {
 *             ars.add(ref);
 *             return;
 *         }
 *
 *         String st = "DLRU";
 *
 *         for (int l = 0; l < 4; l++) {
 *             int dc = i + di[l];
 *             int dd = j + dj[l];
 *
 *             if (dc >= 0 && dd >= 0 && dc < n && dd < n && vis[dc][dd] == 0 &&
 * m[dc][dd] == 1) { vis[i][j] = 1; solve(m, n, vis, dc, dd, ars, ref +
 * st.charAt(l));
 *                 // backtracking
 *                 vis[i][j] = 0;
 *             }
 *         }
 *     }
 *
 *     public static ArrayList<String> findPath(int[][] m, int n) {
 *         ArrayList<String> ars = new ArrayList<>();
 *         int[][] visited = new int[n][n];
 *         String ref = "";
 *
 *         if (m[0][0] == 1) {
 *             solve(m, n, visited, 0, 0, ars, ref);
 *         }
 *
 *         if (ars.isEmpty()) {
 *             ars.add("-1");
 *         }
 *
 *         return ars;
 *     }
 * }
 */

/*
 * ============================================================================
 * VISUALIZATION OF GRID & DIRECTIONS
 * ============================================================================
 *
 *               (i-1, j) [U] (Up)
 *                  ^
 *                  |
 *  (i, j-1) <--- (i, j) ---> (i, j+1) [R] (Right)
 *   [L] (Left)     |
 *                  v
 *               (i+1, j) [D] (Down)
 *
 * Direction Exploration Priority (Alphabetical Order for GFG):
 * 1. Down  ('D') -> (i + 1, j + 0)
 * 2. Left  ('L') -> (i + 0, j - 1)
 * 3. Right ('R') -> (i + 0, j + 1)
 * 4. Up    ('U') -> (i - 1, j + 0)
 *
 * Example 4x4 Maze Topology:
 * [ S ] [ 0 ] [ 0 ] [ 0 ]    (S = Start at 0,0)
 * [ 1 ] [ 1 ] [ 0 ] [ 1 ]
 * [ 1 ] [ 1 ] [ 0 ] [ 0 ]
 * [ 0 ] [ 1 ] [ 1 ] [ E ]    (E = Exit / Destination at 3,3)
 *
 * ============================================================================
 * LINE-BY-LINE EXECUTION TRACE (First 4 Steps on 3x3 Grid)
 * Grid: {{1, 0, 0}, {1, 1, 0}, {0, 1, 1}}, n = 3
 * ============================================================================
 * Step 0: solve(i=0, j=0, temp="")
 *         - isSafe(0, 0) == True && m[0][0] != 0
 *         - Destination check: (0,0) != (2,2) -> False
 *         - Mark m[0][0] = 0 (in-place visited)
 *         - Try 'D' -> temp="D" -> Recurse solve(i=1, j=0).
 *
 * Step 1: solve(i=1, j=0, temp="D")
 *         - Mark m[1][0] = 0
 *         - Try 'D' -> solve(2,0) -> m[2][0] == 0 (blocked). Return.
 *         - Try 'L' -> solve(1,-1) -> Out of bounds (j < 0). Return.
 *         - Try 'R' -> temp="DR" -> Recurse solve(i=1, j=1).
 *
 * Step 2: solve(i=1, j=1, temp="DR")
 *         - Mark m[1][1] = 0
 *         - Try 'D' -> temp="DRD" -> Recurse solve(i=2, j=1).
 *
 * Step 3: solve(i=2, j=1, temp="DRD")
 *         - Mark m[2][1] = 0
 *         - Try 'D' -> solve(3,1) -> Out of bounds (i >= 3). Return.
 *         - Try 'L' -> solve(2,0) -> m[2][0] == 0. Return.
 *         - Try 'R' -> temp="DRDR" -> Recurse solve(i=2, j=2).
 *
 * Step 4: solve(i=2, j=2, temp="DRDR")
 *         - Destination check: i==2 && j==2 -> True!
 *         - result.push_back("DRDR") -> Return and backtrack.
 *
 * ============================================================================
 * DRY RUN TABLE (3x3 Maze)
 * ============================================================================
 * | Step | Call Frame   | Cell (i, j) | Mat State (0=vis/wall) | Temp Path |
Direction / Action Evaluation                      |
 * | :--- | :----------- | :---------- | :--------------------- | :-------- |
:------------------------------------------------- |
 * | 1    | solve(0,0)   | (0, 0)      | m[0][0] = 0            | ""        |
Try 'D' -> (1,0) is open (1). Recurse.             |
 * | 2    | solve(1,0)   | (1, 0)      | m[1][0] = 0            | "D"       |
'D' blocked, 'L' OOB, 'R' -> (1,1) open. Recurse.  |
 * | 3    | solve(1,1)   | (1, 1)      | m[1][1] = 0            | "DR"      |
Try 'D' -> (2,1) is open (1). Recurse.             |
 * | 4    | solve(2,1)   | (2, 1)      | m[2][1] = 0            | "DRD"     |
'D' OOB, 'L' blocked, 'R' -> (2,2) open. Recurse.  |
 * | 5    | solve(2,2)   | (2, 2)      | Target reached         | "DRDR"    |
Reached (2,2)! Add "DRDR" to result. Return.       |
 * | 6    | Backtrack(4) | (2, 1)      | m[2][1] restored = 1   | "DRD"     |
Pop 'R' (path="DRD"), check 'U' -> (1,1) is 0. Done|
 * | 7    | Backtrack(3) | (1, 1)      | m[1][1] restored = 1   | "DR"      |
Pop 'D' (path="DR"), check 'U' -> (0,1) is 0. Done |
 * | 8    | Backtrack(2) | (1, 0)      | m[1][0] restored = 1   | "D"       |
Pop 'R' (path="D"), check 'U' -> (0,0) is 0. Done. |
 * | 9    | Backtrack(1) | (0, 0)      | m[0][0] restored = 1   | ""        |
Pop 'D' (path=""), check 'L','R','U'. Done.        |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Inks & Eraser Trail"
 * Imagine navigating a labyrinth. When you step on a tile, you stamp it with
 * black ink (m[i][j] = 0) so you never walk in a loop.
 * If you hit a dead-end or finish exploring all 4 paths from that tile, you
 * erase the ink (m[i][j] = 1) as you step backwards (backtracking), so
 * future alternative paths can explore through that tile if needed.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Core Technique: Backtracking DFS with 4-directional search.
 * - Direction Alphabetical Order: 'D' -> 'L' -> 'R' -> 'U' ensures output paths
 *   are naturally sorted in lexicographical order without calling std::sort().
 * - Standard Backtracking 3-Step Structure:
 *     1. Mark: m[i][j] = 0 (mark visited in-place to save space).
 *     2. Choose & Recurse: temp.push_back(ch) -> solve(...) -> temp.pop_back().
 *     3. Unmark: m[i][j] = 1 (restore original state on return).
 * - Base Case: When i == n - 1 && j == n - 1, push temp path to result.
 * - Time Complexity: O(3^(N^2)) — at each cell, we have at most 3 choices.
 * - Space Complexity: O(L * X) or O(N^2) recursion stack.

⚡ 1-Minute Quick Review
Core Pattern: Standard Backtracking DFS starting from (0, 0) to destination (n -
1, n - 1). In-Place Visited: Mark m[i][j] = 0 on entry and unmark m[i][j] = 1 on
backtrack to avoid extra $O(N^2)$ space. Lexicographical Order: Exploring in 'D'
-> 'L' -> 'R' -> 'U' alphabetical order directly guarantees sorted outputs
required by GfG without needing std::sort(). Backtrack Routine:
temp.push_back(dir) -> solve(...) -> temp.pop_back()
ensures $O(1)$ backtrack step per call. Complexity: Time: $O(3^{N^2})$ (maximum
3 branches per cell), Auxiliary Space: $O(L \times X)$ or $O(N^2)$ recursion
stack.


 */
