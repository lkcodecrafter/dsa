/*
 * QUESTION: The Knight’s tour problem
 * Link: https://www.geeksforgeeks.org/the-knights-tour-problem-backtracking-1/
 * 
 * Input: 8x8 Chessboard
 * Output: 8x8 grid filled with values 0 to 63 showing the sequence of moves.
 */

#include <iostream>
#include <vector>
#include <iomanip>

// Dimensions of the chessboard
#define N 8

// Checks if the next move is valid (within board and not visited yet)
bool isKnightMoveSafe(int r, int c, const std::vector<std::vector<int>>& board) {
    return (r >= 0 && r < N && c >= 0 && c < N && board[r][c] == -1);
}

// Helper backtracking function to solve the Knight's Tour
bool solveKnightTourHelper(int r, int c, int move_idx, std::vector<std::vector<int>>& board,
                           const int dr[], const int dc[]) {
    // Base Case: Visited all cells
    if (move_idx == N * N) {
        return true;
    }
    
    // Try all 8 possible moves for the knight
    for (int i = 0; i < 8; i++) {
        int next_r = r + dr[i];
        int next_c = c + dc[i];
        
        if (isKnightMoveSafe(next_r, next_c, board)) {
            board[next_r][next_c] = move_idx; // Record move step
            
            if (solveKnightTourHelper(next_r, next_c, move_idx + 1, board, dr, dc)) {
                return true;
            }
            
            board[next_r][next_c] = -1; // Backtrack: undo move
        }
    }
    
    return false;
}

// Solves the Knight's Tour problem and prints the board configuration
bool solveKnightTour() {
    std::vector<std::vector<int>> board(N, std::vector<int>(N, -1));
    
    // Define the 8 possible move jumps for a knight
    int dr[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    
    // Place the knight at the starting cell (0, 0)
    board[0][0] = 0;
    
    if (!solveKnightTourHelper(0, 0, 1, board, dr, dc)) {
        std::cout << "Solution does not exist\n";
        return false;
    }
    
    // Print the grid representation
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << std::setw(2) << board[i][j] << " ";
        }
        std::cout << "\n";
    }
    return true;
}

/*
 * DRY RUN (Partial demonstration of 1st step from cell (0, 0)):
 * Board initialized with all -1. Start board[0][0] = 0.
 * dr = {2, 1, -1, -2, -2, -1, 1, 2}, dc = {1, 2, 2, 1, -1, -2, -2, -1}
 * 
 * | Step | Current Cell | Tried Jump i | next_r | next_c | Safe? | Action                                      | Board Update        |
 * | :--- | :----------- | :----------- | :----- | :----- | :---- | :------------------------------------------ | :------------------ |
 * | 1    | (0, 0)       | 0            | 2      | 1      | Yes   | board[2][1] = 1; recurse with move_idx = 2  | board[2][1] = 1     |
 * | 2    | (2, 1)       | 0            | 4      | 2      | Yes   | board[4][2] = 2; recurse with move_idx = 3  | board[4][2] = 2     |
 * | ...  | ...          | ...          | ...    | ...    | ...   | If sub-calls fail, board[2][1] reset to -1 | Backtrack           |
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine a horse jumping on a stepping stone field. 
 * The horse has 8 specific jump patterns. 
 * Every time the horse lands on an unvisited stone, it paints the stone with its move sequence number. 
 * If it gets boxed in without visiting every stone, it hops backward (backtracks) to repaint and take a different route.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize an N x N board with `-1`. Set `board[0][0] = 0`.
 * - Define knight coordinate offsets: `dr = {2, 1, -1, -2, -2, -1, 1, 2}`, `dc = {1, 2, 2, 1, -1, -2, -2, -1}`.
 * - Call recursive helper `solveKnightTourHelper(r, c, move_idx)`.
 * - Base Case: If `move_idx == N * N`, return `true`.
 * - Iterate 8 moves. If destination `(next_r, next_c)` is on board and equal to `-1`:
 *   - Mark `board[next_r][next_c] = move_idx`.
 *   - Recurse. If successful, propagate `true`.
 *   - Otherwise: backtrack `board[next_r][next_c] = -1`.
 * - Time Complexity: O(8^(N^2)) worst case.
 * - Space Complexity: O(N^2) recursive call stack.
 */
