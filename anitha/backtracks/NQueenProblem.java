package backtracks;

import java.util.ArrayList;
import java.util.List;

public class NQueenProblem {

    /*
     * Given a chess board of size N x N, determine how many ways N queens can be placed on this board
     * so that no two queens attack each other.
     *
     *
     * A queen can move horizontally, vertically and diagonally on a chess board.
     * One queen can be attacked by another queen if it is present in the same row, column, or diagonal
     * of that queen.
     *
     * Step 1: Place a queen in the first column of the first row
     * Step 2: Now place a queen in first such column of 2nd row where placement is permissible i.e.
     * current queen is not being attacked by any queen already on board. If no such column is found,
     * backtrack to the previous row and try to place the queen in next column of that row.
     * Step 3: Continue this until we reach the last row of the board.
     * Step 4: When a queen is placed in the last row, that is a solution.
     * After finding a solution, backtrack to the previous row to find the next solution.
     * Try to find another column in the previous row where placement is permissible.
     *
     *
     * Runtime Complexity:
     * Factorial, O(n!).
     *
     * Memory Complexity:
     * Exponential
     * */

    private static boolean isValidMove(int proposed_row,
                                       int proposed_col,
                                       List<Integer> solution) {

        for (int i = 0; i < proposed_row; ++i) {
            int old_row = i;
            int old_col = solution.get(i);

            int diagonal_offset = proposed_row - old_row;
            if (old_col == proposed_col ||
                    old_col == proposed_col - diagonal_offset ||
                    old_col == proposed_col + diagonal_offset) {
                return false;
            }
        }

        return true;
    }

    protected static void solveNQueensRec(int n,
                                          List<Integer> solution,
                                          int row,
                                          List<List<Integer>> results) {

        if (row == n) {
            results.add(new ArrayList<>(solution));
            return;
        }

        for (int i = 0; i < n; ++i) {
            if (isValidMove(row, i, solution)) {
                solution.set(row, i);
                solveNQueensRec(n, solution, row + 1, results);
            }
        }
    }

    private static void solveNQueens(int n,
                                     List<List<Integer>> results) {

        List<Integer> solution = new ArrayList<>(n);
        for (int i = 0; i < n; ++i) {
            solution.add(-1);
        }
        solveNQueensRec(n, solution, 0, results);
    }

    public static void main(String[] args) {
        List<List<Integer>> results = new ArrayList<>();

        solveNQueens(8, results);
        System.out.println("Total Solutions Count: " + results.size());
        for (List<Integer> result : results) {
            for (Integer r : result) {
                System.out.print(r + " ");
            }
            System.out.println();
        }
        System.out.println("Total Solutions Count = " + results.size());
    }

}


/*

import java.util.*;

public class NQueenSimple {

    public static void solve(int n) {
        List<List<Integer>> result = new ArrayList<>();
        int[] board = new int[n]; // board[row] = col

        backtrack(0, n, board, result);

        System.out.println("Total solutions: " + result.size());
        for (List<Integer> sol : result) {
            System.out.println(sol);
        }
    }

    private static void backtrack(int row, int n, int[] board, List<List<Integer>> result) {
        if (row == n) {
            List<Integer> sol = new ArrayList<>();
            for (int col : board) sol.add(col);
            result.add(sol);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isSafe(row, col, board)) {
                board[row] = col;
                backtrack(row + 1, n, board, result);
            }
        }
    }

    private static boolean isSafe(int row, int col, int[] board) {
        for (int prevRow = 0; prevRow < row; prevRow++) {
            int prevCol = board[prevRow];

            // same column or diagonal
            if (prevCol == col || Math.abs(prevCol - col) == Math.abs(prevRow - row)) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        solve(4);
    }
}

🔍 Mini Dry Run (n = 4)

We try row by row:

Row 0:
place at col 0 → [0, -, -, -]
Row 1:
col 0 ❌ (same column)
col 1 ❌ (diagonal)
col 2 ✅ → [0, 2, -, -]
Row 2:
try all → none works ❌ → backtrack
Row 1:
try col 3 → [0, 3, -, -]

…and so on until solutions:

[1, 3, 0, 2]
[2, 0, 3, 1]
🧠 Key Insight (super important)

Instead of thinking:

“where can I place queens?”

Think:

“for this row, which columns are safe?”

That shift makes backtracking much easier.


🧠 What does [1, 3, 0, 2] mean?

Each index = row
Each value = column where the queen is placed

So:

[1, 3, 0, 2]

means:

Row 0 → Column 1
Row 1 → Column 3
Row 2 → Column 0
Row 3 → Column 2
♟️ Visual Board (for [1, 3, 0, 2])
. Q . .
. . . Q
Q . . .
. . Q .
Q = Queen
. = Empty
Second Solution [2, 0, 3, 1]
Meaning:
Row 0 → Column 2
Row 1 → Column 0
Row 2 → Column 3
Row 3 → Column 1
Board:
. . Q .
Q . . .
. . . Q
. Q . .
💡 Why this format is used

Instead of storing full board:

[
 [., Q, ., .],
 [., ., ., Q],
 ...
]

We store:

[row → column]

This is:

faster
memory efficient
easier to compute
🔑 Key takeaway

Each array represents a valid placement of N queens such that:

no same column ❌
no same diagonal ❌
(row is automatically unique)


*/


