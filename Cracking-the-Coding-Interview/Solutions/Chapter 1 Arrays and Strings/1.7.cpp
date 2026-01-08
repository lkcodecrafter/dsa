/*
 *Q1.7 Write an algorithm such that if an element in an M*N matrix is 0,its entire row and column is set to 0.
 */

#include <iostream>
#include <cstring>
using namespace std;

void zeroMatrix(int matrix[][4], int M, int N) {
    bool row[M];
    bool col[N];
    memset(row, false, sizeof(row));
    memset(col, false, sizeof(col));

    // First pass to find all rows and columns that need to be zeroed
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 0) {
                row[i] = true;
                col[j] = true;
            }
        }
    }

    // Second pass to set the rows to zero
    for (int i = 0; i < M; i++) {
        if (row[i]) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    // Third pass to set the columns to zero
    for (int j = 0; j < N; j++) {
        if (col[j]) {
            for (int i = 0; i < M; i++) {
                matrix[i][j] = 0;
            }
        }
    }
}

int main() {
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 0, 7, 8},
        {9, 10, 11, 12}
    };

    int M = 3;
    int N = 4;

    zeroMatrix(matrix, M, N);

    // Print the modified matrix
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

