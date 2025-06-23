
# 👑 N-Queens Problem using Backtracking in Java

## 📘 Problem Statement

Place **N queens** on an **N×N chessboard** such that no two queens attack each other.

Queens can move:
- Vertically
- Horizontally
- Diagonally

Goal: Print all valid arrangements.

---

## ✅ Example (N = 4)

One valid board:
```
. Q . .
. . . Q
Q . . .
. . Q .
```

---

## 🧠 Backtracking Approach

1. Try placing a queen in **each column of a row**.
2. If safe, recurse for the **next row**.
3. If a placement fails → **undo (backtrack)** and try next column.
4. If `row == N`, a valid board is found.

---

## 🔁 Dry Run (N = 4)

```
Row 0 → place at col 1
Row 1 → place at col 3
Row 2 → place at col 0
Row 3 → place at col 2 ✅ solution found

Backtrack...
Row 3 → try other cols → fail
Backtrack...
Row 2 → try next cols → fail
Backtrack...
...
```

Final solution prints all possible board configurations.

---

## 💻 Java Code

```java
public class NQueensSolver {
    public static void solveNQueens(int n) {
        char[][] board = new char[n][n];
        for (char[] row : board) Arrays.fill(row, '.');
        placeQueens(board, 0);
    }

    private static void placeQueens(char[][] board, int row) {
        if (row == board.length) {
            printBoard(board);
            System.out.println();
            return;
        }
        for (int col = 0; col < board.length; col++) {
            if (isSafe(board, row, col)) {
                board[row][col] = 'Q';
                placeQueens(board, row + 1);
                board[row][col] = '.';
            }
        }
    }

    private static boolean isSafe(char[][] board, int row, int col) {
        for (int i = 0; i < row; i++) if (board[i][col] == 'Q') return false;
        for (int i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--) if (board[i][j] == 'Q') return false;
        for (int i = row-1, j = col+1; i >= 0 && j < board.length; i--, j++) if (board[i][j] == 'Q') return false;
        return true;
    }

    private static void printBoard(char[][] board) {
        for (char[] row : board) {
            for (char c : row) System.out.print(c + " ");
            System.out.println();
        }
    }

    public static void main(String[] args) {
        solveNQueens(4);
    }
}
```

---

## ⏱ Time & Space Complexity

- **Time Complexity:** O(N!) – due to N choices at each row
- **Space Complexity:** O(N²) – for the board

---

This is one of the best examples to master backtracking!
