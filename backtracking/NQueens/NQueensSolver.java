
import java.util.*;

public class NQueensSolver {

    public static void solveNQueens(int n) {
        char[][] board = new char[n][n];
        for (char[] row : board)
            Arrays.fill(row, '.');

        placeQueens(board, 0);
    }

    private static void placeQueens(char[][] board, int row) {
        int n = board.length;

        if (row == n) {
            printBoard(board);
            System.out.println();
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isSafe(board, row, col)) {
                board[row][col] = 'Q';         // Place queen
                placeQueens(board, row + 1);   // Recurse for next row
                board[row][col] = '.';         // Backtrack
            }
        }
    }

    private static boolean isSafe(char[][] board, int row, int col) {
        // Check column
        for (int i = 0; i < row; i++)
            if (board[i][col] == 'Q') return false;

        // Check upper-left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            if (board[i][j] == 'Q') return false;

        // Check upper-right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < board.length; i--, j++)
            if (board[i][j] == 'Q') return false;

        return true;
    }

    private static void printBoard(char[][] board) {
        for (char[] row : board) {
            for (char c : row) {
                System.out.print(c + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int n = 4; // Change to any N
        solveNQueens(n);
    }
}
