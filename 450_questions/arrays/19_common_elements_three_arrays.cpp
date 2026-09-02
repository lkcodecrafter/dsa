/*
 * QUESTION: Find common elements in 3 sorted arrays
 * Link: https://practice.geeksforgeeks.org/problems/common-elements1132/1
 * 
 * Input: A[] = {1, 5, 10, 20, 40, 80}, B[] = {6, 7, 20, 80, 100}, C[] = {3, 4, 15, 20, 30, 70, 80, 120}
 * Output: {20, 80}
 */

#include <iostream>
#include <vector>

// Returns a vector containing elements common to all three sorted vectors.
std::vector<int> commonElements(const std::vector<int>& A, const std::vector<int>& B, const std::vector<int>& C) {
    std::vector<int> result;
    size_t i = 0, j = 0, k = 0;
    
    while (i < A.size() && j < B.size() && k < C.size()) {
        // If we find a common element
        if (A[i] == B[j] && B[j] == C[k]) {
            // Avoid adding duplicates to the result
            if (result.empty() || result.back() != A[i]) {
                result.push_back(A[i]);
            }
            i++;
            j++;
            k++;
        }
        // Increment the pointer pointing to the smaller element
        else if (A[i] < B[j]) {
            i++;
        } else if (B[j] < C[k]) {
            j++;
        } else {
            k++;
        }
    }
    
    return result;
}

/*
 * DRY RUN (A = {1, 5, 20}, B = {5, 20}, C = {5, 20}):
 * Pointers: i = 0, j = 0, k = 0
 * 
 * | Step | i | j | k | A[i] | B[j] | C[k] | Comparison / Action          | Result State |
 * | :--- | :-| :-| :-| :--- | :--- | :--- | :--------------------------- | :----------- |
 * | Init | 0 | 0 | 0 | 1    | 5    | 5    | A[i] < B[j] (1 < 5) -> i++   | {}           |
 * | 1    | 1 | 0 | 0 | 5    | 5    | 5    | A[1] == B[0] == C[0] -> push | {5}          |
 * |      |   |   |   |      |      |      | increment all pointers       |              |
 * | 2    | 2 | 1 | 1 | 20   | 20   | 20   | A[2] == B[1] == C[1] -> push | {5, 20}      |
 * |      |   |   |   |      |      |      | increment all pointers       |              |
 * | 3    | 3 | 2 | 2 | -    | -    | -    | Loop ends (i == A.size())    | {5, 20}      |
 * 
 * Common Elements: {5, 20}
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine three friends walking up three separate sorted hills. 
 * They want to meet at the exact same elevation. 
 * If they are at the same height, they cheer (note the common element) and all step forward. 
 * If not, the friend at the lowest elevation walks up.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize three pointers: `i = 0`, `j = 0`, `k = 0`.
 * - While `i < n1 && j < n2 && k < n3`:
 *   - If `A[i] == B[j] && B[j] == C[k]`, push `A[i]` (if not duplicate), then increment all pointers.
 *   - Else if `A[i] < B[j]`, increment `i`.
 *   - Else if `B[j] < C[k]`, increment `j`.
 *   - Else, increment `k`.
 * - Time Complexity: O(N1 + N2 + N3)
 * - Space Complexity: O(1) auxiliary space (excluding result).
 */
