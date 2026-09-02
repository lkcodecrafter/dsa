/*
    QUESTION    : Recursively print all sentences that can be formed from list of word lists
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/recursively-print-all-sentences-that-can-be-formed-from-list-of-word-lists/
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(C^R) where R = rows, C = columns - Backtracking across all sentence combinations
// S.C : O(R)   - Recursion call stack
class Solution {
private:
    void printSentencesRecur(const vector<vector<string>>& wordList, int row, vector<string>& current, vector<vector<string>>& result) {
        // Base case: sentence formed from every row
        if (row == wordList.size()) {
            result.push_back(current);
            return;
        }

        // Try each word in current row
        for (int col = 0; col < wordList[row].size(); col++) {
            if (!wordList[row][col].empty()) {
                current.push_back(wordList[row][col]);
                printSentencesRecur(wordList, row + 1, current, result);
                current.pop_back(); // Backtrack
            }
        }
    }

public:
    vector<vector<string>> sentences(vector<vector<string>>& list) {
        vector<vector<string>> result;
        vector<string> current;
        printSentencesRecur(list, 0, current, result);
        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Recurse row-by-row: `current.push_back(list[row][col]); recurse(row+1); current.pop_back();`
 * - Base case: `row == totalRows` $\rightarrow$ add sentence.
 * - Time: O(C^R), Space: O(R).
 */
