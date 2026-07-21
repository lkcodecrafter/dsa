# Module 4: Recursion & Backtracking (Lectures 51–69, 142)

## 📋 Syllabus
*   **Basics:** Factorial, Fibonacci, Recursion on Arrays/Strings, Recursive Binary Search.
*   **Divide & Conquer:** Merge Sort, Quick Sort.
*   **Permutations & Subsequences:** Print Subsequences, Generate Parentheses, Subset Sum, Permutations of Arrays/Strings, Tower of Hanoi, Josephus Problem.
*   **Backtracking:** Rat in a Maze, N-Queens, Sudoku Solver, M-Coloring.

---

## 🟢 Section 1: Basics

### 🎯 Solution 4.1: Recursion Basics
*   **Concept:** Recursion is when a function calls itself to solve smaller subproblems of the same problem. A base case is essential to stop infinite calling.
*   **C++ Code:**
```cpp
#include <iostream>
#include <vector>

// 1. Recursive Factorial
int factorial(int n) {
    if (n <= 1) return 1; // Base case
    return n * factorial(n - 1);
}

// 2. Recursive Fibonacci
int fibonacci(int n) {
    if (n <= 1) return n; // Base case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 3. Recursive Binary Search
int recursiveBS(const std::vector<int>& arr, int start, int end, int target) {
    if (start > end) return -1; // Base case (not found)
    int mid = start + (end - start) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] > target) {
        return recursiveBS(arr, start, mid - 1, target);
    }
    return recursiveBS(arr, mid + 1, end, target);
}
```
*   **🔍 Dry Run (Factorial of 3):**
    *   `factorial(3)` calls `3 * factorial(2)`
    *   `factorial(2)` calls `2 * factorial(1)`
    *   `factorial(1)` returns `1` (Base case)
    *   Resolves to `2 * 1 = 2`, then `3 * 2 = 6`.
*   **Complexity:**
    *   Factorial: Time $O(N)$, Space $O(N)$ (recursion stack).
    *   Fibonacci: Time $O(2^N)$, Space $O(N)$.
    *   Binary Search: Time $O(\log N)$, Space $O(\log N)$.

---

## 🟢 Section 2: Divide & Conquer

### 🎯 Solution 4.2: Merge Sort & Quick Sort
*   **Problem:** Sort an array using Divide & Conquer sorting algorithms.
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>
 void merge(vector<int>& arr, int left, int mid, int right) {

    vector<int> temp;

    int i = left;
    int j = mid + 1;

    // Compare both halves
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        } else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    // Copy remaining elements from left half
    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }

    // Copy remaining elements from right half
    while (j <= right) {
        temp.push_back(arr[j]);
        j++;
    }

    // Copy sorted elements back to original array
    for (int k = left; k <= right; k++) {
        arr[k] = temp[k - left];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {

    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

/*
Complexity
Time: O(n log n)
Space: O(n)
*/

// 2. Quick Sort (Lomuto Partition Scheme)
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
```
*   **🔍 Dry Run (Merge Sort on `{4, 1, 3}`):**
    *   Split into `{4}` and `{1, 3}`.
    *   Split `{1, 3}` into `{1}` and `{3}`, merge to `{1, 3}`.
    *   Merge `{4}` and `{1, 3}` -> `{1, 3, 4}`.
*   **Complexity:**
    *   Merge Sort: Time $O(N \log N)$ in all cases, Space $O(N)$.
    *   Quick Sort: Time Average $O(N \log N)$, Worst $O(N^2)$, Space $O(\log N)$ stack space.

---

## 🟢 Section 3: Permutations & Subsequences

### 🎯 Solution 4.3: Permutations & Print Subsequences
*   **Problem:** Generate all permutations of an array and subsequences of a string.
*   **C++ Code:**
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// 1. Permutations of Array
void permuteHelper(std::vector<int>& nums, int start, std::vector<std::vector<int>>& res) {
    if (start == nums.size()) {
        res.push_back(nums);
        return;
    }
    for (int i = start; i < nums.size(); i++) {
        std::swap(nums[start], nums[i]);
        permuteHelper(nums, start + 1, res);
        std::swap(nums[start], nums[i]); // backtrack
    }
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    permuteHelper(nums, 0, res);
    return res;
}

// 2. Print Subsequences of a String
void printSubsequences(const std::string& input, int index, std::string output) {
    if (index == input.length()) {
        std::cout << "\"" << output << "\" ";
        return;
    }
    // Exclude current character
    printSubsequences(input, index + 1, output);
    // Include current character
    printSubsequences(input, index + 1, output + input[index]);
}
```
*   **🔍 Dry Run (Subsequences of `"ab"`):**
    *   Call `index = 0`.
    *   Exclude 'a' -> Call `index = 1`. Exclude 'b' -> Output `""`. Include 'b' -> Output `"b"`.
    *   Include 'a' -> Call `index = 1`. Exclude 'b' -> Output `"a"`. Include 'b' -> Output `"ab"`.
    *   Subsequences: `""`, `"b"`, `"a"`, `"ab"`.
*   **Complexity:**
    *   Permutations: Time $O(N \cdot N!)$, Space $O(N)$ recursion depth.
    *   Subsequences: Time $O(2^N)$, Space $O(N)$.

### 🎯 Solution 4.4: Generate Parentheses, Subset Sum, Tower of Hanoi & Josephus
*   **C++ Code:**
```cpp
#include <vector>
#include <string>
#include <iostream>

// 1. Generate Parentheses
void generateParenthesisHelper(int open, int close, int n, std::string current, std::vector<std::string>& result) {
    if (current.length() == 2 * n) {
        result.push_back(current);
        return;
    }
    if (open < n) {
        generateParenthesisHelper(open + 1, close, n, current + "(", result);
    }
    if (close < open) {
        generateParenthesisHelper(open, close + 1, n, current + ")", result);
    }
}

// 2. Subset Sum (Count subsets with sum K)
int countSubsetsWithSum(const std::vector<int>& arr, int i, int sum) {
    if (sum == 0) return 1;
    if (i == arr.size() || sum < 0) return 0;
    return countSubsetsWithSum(arr, i + 1, sum - arr[i]) + 
           countSubsetsWithSum(arr, i + 1, sum);
}

// 3. Tower of Hanoi
void towerOfHanoi(int n, char from, char to, char aux) {
    if (n == 0) return;
    towerOfHanoi(n - 1, from, aux, to);
    std::cout << "Move disk " << n << " from " << from << " to " << to << "\n";
    towerOfHanoi(n - 1, aux, to, from);
}

// 4. Josephus Problem (Returns 0-indexed position)
int josephus(int n, int k) {
    if (n == 1) return 0;
    return (josephus(n - 1, k) + k) % n;
}
```
*   **Complexity:**
    *   Parentheses: Time $O(\frac{4^N}{\sqrt{N}})$ (Catalan number), Space $O(N)$.
    *   Tower of Hanoi: Time $O(2^N)$, Space $O(N)$.
    *   Josephus: Time $O(N)$, Space $O(N)$.

---

## 🟢 Section 4: Backtracking

### 🎯 Solution 4.5: N-Queens Problem
*   **Problem:** Place $N$ queens on an $N \times N$ chessboard such that no two queens attack each other.
*   **C++ Code:**
```cpp
#include <vector>
#include <string>

bool isSafe(int row, int col, const std::vector<std::string>& board, int n) {
    // Check column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }
    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }
    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }
    return true;
}

void solveNQueens(int row, std::vector<std::string>& board, std::vector<std::vector<std::string>>& ans, int n) {
    if (row == n) {
        ans.push_back(board);
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, board, n)) {
            board[row][col] = 'Q';
            solveNQueens(row + 1, board, ans, n);
            board[row][col] = '.'; // backtrack
        }
    }
}
```
*   **🔍 Dry Run:**
    *   Placing Queens row by row from `row = 0`.
    *   In `row = 0`, put Queen at index `(0, 0)`.
    *   For `row = 1`, `col = 0` and `col = 1` are attacked. Try `(1, 2)`.
    *   Recursion continues. If block is hit where no column is safe, it returns and triggers backtracking (re-setting `board[row][col] = '.'`).
*   **Complexity:** Time: $O(N!)$, Space: $O(N^2)$ board space.

### 🎯 Solution 4.6: Rat in a Maze, Sudoku Solver & M-Coloring
*   **C++ Code:**
```cpp
#include <vector>
#include <string>

// 1. Rat in a Maze
void solveMaze(int r, int c, std::vector<std::vector<int>>& maze, int n, std::string path, std::vector<std::string>& ans, std::vector<std::vector<bool>>& visited) {
    if (r == n - 1 && c == n - 1) {
        ans.push_back(path);
        return;
    }
    int dr[] = {1, 0, 0, -1};
    int dc[] = {0, -1, 1, 0};
    char dir[] = {'D', 'L', 'R', 'U'};
    
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr >= 0 && nr < n && nc >= 0 && nc < n && maze[nr][nc] == 1 && !visited[nr][nc]) {
            visited[nr][nc] = true;
            solveMaze(nr, nc, maze, n, path + dir[i], ans, visited);
            visited[nr][nc] = false; // backtrack
        }
    }
}

// 2. Sudoku Solver
bool isSudokuSafe(const std::vector<std::vector<char>>& board, int row, int col, char val) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == val) return false;
        if (board[i][col] == val) return false;
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == val) return false;
    }
    return true;
}

bool solveSudoku(std::vector<std::vector<char>>& board) {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == '.') {
                for (char val = '1'; val <= '9'; val++) {
                    if (isSudokuSafe(board, r, c, val)) {
                        board[r][c] = val;
                        if (solveSudoku(board)) return true;
                        board[r][c] = '.'; // backtrack
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// 3. M-Coloring
bool isColorSafe(int node, const std::vector<std::vector<int>>& graph, const std::vector<int>& color, int c) {
    for (size_t i = 0; i < graph.size(); i++) {
        if (graph[node][i] && color[i] == c) return false;
    }
    return true;
}

bool graphColoring(int node, const std::vector<std::vector<int>>& graph, std::vector<int>& color, int m, int n) {
    if (node == n) return true;
    for (int c = 1; c <= m; c++) {
        if (isColorSafe(node, graph, color, c)) {
            color[node] = c;
            if (graphColoring(node + 1, graph, color, m, n)) return true;
            color[node] = 0; // backtrack
        }
    }
    return false;
}
```
*   **Complexity:**
    *   Rat in a Maze: Time $O(4^{N^2})$, Space $O(N^2)$.
    *   Sudoku Solver: Time $O(9^{N^2})$, Space $O(N^2)$.
    *   M-Coloring: Time $O(M^N)$, Space $O(N)$.
