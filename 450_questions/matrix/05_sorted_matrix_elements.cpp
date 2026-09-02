/*
    QUESTION    : Print elements in sorted order using row-column wise sorted matrix
    Company Tags: Amazon, MakeMyTrip
    GfG Link    : https://practice.geeksforgeeks.org/problems/sorted-matrix/0
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2 * log(N^2)) or O(N^2 log N) - Flattening and sorting (or Min-Heap K-way merge)
// S.C : O(N^2)                           - Space to store flattened elements
class Solution {
public:
    vector<vector<int>> sortedMatrix(int N, vector<vector<int>> Mat) {
        vector<int> flattened;
        flattened.reserve(N * N);

        // 1. Flatten the 2D matrix into a 1D vector
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                flattened.push_back(Mat[i][j]);
            }
        }

        // 2. Sort all N*N elements
        sort(flattened.begin(), flattened.end());

        // 3. Put elements back into the 2D matrix in sorted order
        int idx = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                Mat[i][j] = flattened[idx++];
            }
        }

        return Mat;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF MATRIX FLATTENING & SORTING
 * ============================================================================
 *
 * Input Mat (3x3):
 * [ 10, 20, 30 ]
 * [  5, 15, 25 ]
 * [  2,  4,  6 ]
 *
 * Flattened -> [ 10, 20, 30, 5, 15, 25, 2, 4, 6 ]
 * Sorted    -> [  2,  4,  5, 6, 10, 15, 20, 25, 30 ]
 *
 * Replaced in Matrix:
 * [  2,  4,  5 ]
 * [  6, 10, 15 ]
 * [ 20, 25, 30 ]
 *
 * ============================================================================
 * DRY RUN (2x2 Matrix)
 * Mat = {{10, 20}, {5, 15}}
 * ============================================================================
 * | Step | Operation            | State / Data Structure                                 |
 * | :--- | :------------------- | :----------------------------------------------------- |
 * | 1    | Flattening (2 loops) | flattened = {10, 20, 5, 15}                            |
 * | 2    | Sort 1D vector       | flattened = {5, 10, 15, 20}                            |
 * | 3    | Fill back into Mat   | Mat[0][0]=5, Mat[0][1]=10, Mat[1][0]=15, Mat[1][1]=20  |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Deck of Cards Deal"
 * Pick up all cards across the grid into a single deck (`flattened`),
 * sort the deck using standard quicksort (`std::sort`),
 * and deal them back row-by-row into the grid slots.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Flatten the $N \times N$ matrix into an array of size $N^2$.
 * - Sort the array using `std::sort()` in $O(N^2 \log(N^2))$.
 * - Reconstruct the $N \times N$ matrix by copying elements sequentially.
 * - Time Complexity: O(N^2 log N), Space Complexity: O(N^2).
 */
