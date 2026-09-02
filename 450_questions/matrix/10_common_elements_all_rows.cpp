/*
    QUESTION    : Common elements in all rows of a given matrix
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/common-elements-in-all-rows-of-a-given-matrix/
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(R * C) - One pass over all elements of the matrix
// S.C : O(C)     - Hash map storing unique elements of row 0
class Solution {
public:
    vector<int> findCommonElements(vector<vector<int>> &mat) {
        vector<int> result;
        int R = mat.size();
        if (R == 0) return result;
        int C = mat[0].size();

        // Map stores element -> count of consecutive rows it appeared in
        unordered_map<int, int> mp;

        // 1. Initialize map with elements of the first row
        for (int j = 0; j < C; j++) {
            mp[mat[0][j]] = 1;
        }

        // 2. Traverse the remaining rows
        for (int i = 1; i < R; i++) {
            for (int j = 0; j < C; j++) {
                // If element was present in all previous `i` rows
                if (mp[mat[i][j]] == i) {
                    mp[mat[i][j]] = i + 1; // Mark present up to row `i`

                    // If we reached the last row, this element is common to all rows
                    if (i == R - 1) {
                        result.push_back(mat[i][j]);
                    }
                }
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF ROW OCCURRENCE TRACKING
 * ============================================================================
 *
 * Matrix (4 rows x 5 cols):
 * Row 0: [ 1, 2, 1, 4, 8 ]  -> Map: {1: 1, 2: 1, 4: 1, 8: 1}
 * Row 1: [ 3, 7, 8, 5, 1 ]  -> At 8: mp[8]==1 -> mp[8]=2. At 1: mp[1]==1 -> mp[1]=2.
 * Row 2: [ 8, 7, 7, 3, 1 ]  -> At 8: mp[8]==2 -> mp[8]=3. At 1: mp[1]==2 -> mp[1]=3.
 * Row 3: [ 8, 1, 2, 7, 9 ]  -> At 8: mp[8]==3 -> mp[8]=4 -> ADD 8! At 1: mp[1]==3 -> mp[1]=4 -> ADD 1!
 *
 * Common Elements: [8, 1]
 *
 * ============================================================================
 * DRY RUN (3 rows x 3 cols)
 * mat = {{1, 2, 3}, {2, 3, 5}, {3, 2, 7}}
 * ============================================================================
 * | Row | Col | Element | mp[element] before | Check mp == i | mp[element] after | Added to Result? |
 * | :-- | :-- | :------ | :----------------- | :------------ | :---------------- | :--------------- |
 * | 0   | All | 1, 2, 3 | 0                  | -             | 1: 1, 2: 1, 3: 1  | -                |
 * | 1   | 0   | 2       | 1                  | 1 == 1 (Yes)  | 2: 2              | -                |
 * | 1   | 1   | 3       | 1                  | 1 == 1 (Yes)  | 3: 2              | -                |
 * | 1   | 2   | 5       | 0                  | 0 == 1 (No)   | 5: 0              | -                |
 * | 2   | 0   | 3       | 2                  | 2 == 2 (Yes)  | 3: 3              | Added 3! (i=R-1) |
 * | 2   | 1   | 2       | 2                  | 2 == 2 (Yes)  | 2: 3              | Added 2! (i=R-1) |
 * | 2   | 2   | 7       | 0                  | 0 == 2 (No)   | 7: 0              | -                |
 *
 * Result: {3, 2}
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Attendance Stamp"
 * Every element gets stamped with the row number it attends.
 * An element can only get stamp `i+1` if it already possesses stamp `i`.
 * If it collects all stamps up to the last row (`R`), it earns a spot on the common list.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Store elements of first row in hash map: `mp[mat[0][j]] = 1`.
 * - For each row `i` from `1` to `R - 1`:
 *     - If `mp[mat[i][j]] == i`: update `mp[mat[i][j]] = i + 1`.
 *     - If `i == R - 1`, append `mat[i][j]` to results.
 * - Prevents duplicate counts in the same row automatically because `mp` is only incremented when `mp == i`.
 * - Time: O(R * C), Space: O(C).
 */
