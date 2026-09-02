/*
    QUESTION    : Print unique rows in a given boolean matrix
    Company Tags: Amazon, Microsoft, Zoho
    GfG Link    : https://practice.geeksforgeeks.org/problems/unique-rows-in-boolean-matrix/1
*/

#include <iostream>
#include <vector>

using namespace std;

#define MAX 1000

/************************************************************ C++ ************************************************************/
// T.C : O(R * C) - Each row of length C is inserted into a Binary Trie in O(C) time
// S.C : O(R * C) - Binary Trie nodes (branching factor 2 instead of 26)
struct BinaryTrieNode {
    BinaryTrieNode* children[2]; // 0 and 1
    bool isEndOfRow;

    BinaryTrieNode() {
        isEndOfRow = false;
        children[0] = nullptr;
        children[1] = nullptr;
    }
};

class Solution {
private:
    BinaryTrieNode* root;

    // Inserts a row into the Binary Trie. Returns true if row is newly inserted (unique)
    bool insertRow(int M[MAX][MAX], int row, int col) {
        BinaryTrieNode* crawl = root;
        bool isNewRow = false;

        for (int j = 0; j < col; j++) {
            int bit = M[row][j];
            if (crawl->children[bit] == nullptr) {
                crawl->children[bit] = new BinaryTrieNode();
                isNewRow = true;
            }
            crawl = crawl->children[bit];
        }

        if (isNewRow || !crawl->isEndOfRow) {
            crawl->isEndOfRow = true;
            return true;
        }

        return false;
    }

public:
    vector<vector<int>> uniqueRow(int M[MAX][MAX], int row, int col) {
        root = new BinaryTrieNode();
        vector<vector<int>> result;

        for (int i = 0; i < row; i++) {
            // If row has not been seen before, add it to result
            if (insertRow(M, i, col)) {
                vector<int> currentRow;
                for (int j = 0; j < col; j++) {
                    currentRow.push_back(M[i][j]);
                }
                result.push_back(currentRow);
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BINARY TRIE FOR BOOLEAN ROWS
 * ============================================================================
 *
 * Rows:
 * Row 0: [ 1, 1, 0, 1 ] -> (New)  -> Inserted
 * Row 1: [ 1, 0, 0, 1 ] -> (New)  -> Inserted
 * Row 2: [ 1, 1, 0, 1 ] -> (Duplicate of Row 0) -> Skipped!
 *
 * Binary Trie:
 *                (Root)
 *                  |
 *                 '1'
 *                /   \
 *              '1'   '0'
 *               |      |
 *              '0'    '0'
 *               |      |
 *              '1'*   '1'*
 *
 * ============================================================================
 * DRY RUN (3 rows x 2 cols)
 * M = {{0, 1}, {1, 0}, {0, 1}}
 * ============================================================================
 * | Row | Bits   | Trie Path Traversed | Is New Row? | Action                          |
 * | :-- | :----- | :------------------ | :---------- | :------------------------------ |
 * | 0   | {0, 1} | Root -> 0 -> 1      | Yes         | Add {0, 1} to result            |
 * | 1   | {1, 0} | Root -> 1 -> 0      | Yes         | Add {1, 0} to result            |
 * | 2   | {0, 1} | Root -> 0 -> 1      | No (Exists) | Duplicate! Skip row             |
 *
 * Result: { {0, 1}, {1, 0} }
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Binary Fork in the Road"
 * Build a 2-way tree (0 = left, 1 = right).
 * Walk the path for each row. If you ever have to construct a new path,
 * it is a unique row; if the path already ends with a flag (`isEndOfRow`), it is a duplicate!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Use a Binary Trie with `children[2]` (for `0` and `1`).
 * - For each row, traverse bit-by-bit:
 *     - If any node in the path is created newly, mark `isNewRow = true`.
 *     - If unique, add row to `result`.
 * - Time Complexity: O(R * C), Space Complexity: O(R * C).
 */
