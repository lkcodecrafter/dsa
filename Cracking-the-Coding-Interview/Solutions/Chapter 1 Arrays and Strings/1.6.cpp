/*
 *Q1.6 Given an image represented by an N*N matrix,where each pixel int image is 4 bytes,write a
  method to rotate the image by90 degrees.
 *Can you do this in place?
 *
 *    1   2   3   4                   4   8   12  16
 *    5   6   7   8        -->        3   7   11  15
 *    9   10  11  12                  2   6   10  14
 *    13  14  15  16                  1   5   9   13
 *
 */

#include <iostream>
#include <cstring>
using namespace std;

void rotateMatrix(int matrix[][4], int N) {
    for (int layer = 0; layer < N / 2; ++layer) {
        int first = layer;
        int last = N - 1 - layer;
        for (int i = first; i < last; ++i) {
            int offset = i - first;
            // Save top
            int top = matrix[first][i];

            // left -> top
            matrix[first][i] = matrix[last - offset][first]; // what was on left goes to top
            // example: matrix[0][1] = matrix[2][0]

            // bottom -> left
            matrix[last - offset][first] = matrix[last][last - offset]; // what was on bottom goes to left

            // right -> bottom
            matrix[last][last - offset] = matrix[i][last];

            // top -> right
            matrix[i][last] = top; // right <- saved top
        }
    }
}// time complexity: O(n^2)
 // space complexity: O(1)



void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

void transpose(int a[][4], int n)
{
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			swap(a[i][j], a[j][i]);
	for (int i = 0; i < n / 2; ++i)
		for (int j = 0; j < n; ++j)
			swap(a[i][j], a[n - 1 - i][j]);
} // time complexity: O(n^2)
  // space complexity: O(1)


int main()
{
    int matrix[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    rotateMatrix(matrix, 4);

    cout << "Rotated Matrix:" << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    int a[4][4] = 
	{
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16}
	};
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	transpose(a, 4);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			cout << a[i][j] << " ";
		cout << endl;
	}


    return 0;
}

