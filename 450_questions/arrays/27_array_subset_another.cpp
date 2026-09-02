/*
 * QUESTION: Find whether an array is a subset of another array
 * Link: https://practice.geeksforgeeks.org/problems/array-subset-of-another-array/0
 * 
 * Input: arr1[] = {11, 1, 13, 21, 3, 7}, arr2[] = {11, 3, 7, 1}
 * Output: Yes
 * 
 * Input: arr1[] = {1, 2, 3, 4, 4, 5}, arr2[] = {1, 4, 4, 4}
 * Output: No (arr1 doesn't have three 4s)
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

// Returns "Yes" if arr2 is a subset of arr1, else "No".
std::string isSubset(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    std::unordered_map<int, int> freq_map;
    
    // Store frequencies of elements of arr1
    for (int num : arr1) {
        freq_map[num]++;
    }
    
    // Check if elements of arr2 exist in freq_map with sufficient count
    for (int num : arr2) {
        if (freq_map[num] <= 0) {
            return "No";
        }
        freq_map[num]--;
    }
    
    return "Yes";
}

/*
 * DRY RUN (arr1 = {1, 2, 2, 3}, arr2 = {2, 2, 4}):
 * Freq Map after arr1: { 1:1, 2:2, 3:1 }
 * 
 * | Step | Element from arr2 | Count in freq_map | Condition (Count <= 0?) | Action / Result        | freq_map Updated State |
 * | :--- | :---------------- | :---------------- | :---------------------- | :--------------------- | :--------------------- |
 * | Init | -                 | -                 | -                       | Start verification     | { 1:1, 2:2, 3:1 }      |
 * | 1    | 2                 | 2                 | No (2 > 0)              | Count decremented      | { 1:1, 2:1, 3:1 }      |
 * | 2    | 2                 | 1                 | No (1 > 0)              | Count decremented      | { 1:1, 2:0, 3:1 }      |
 * | 3    | 4                 | 0                 | Yes (0 <= 0)            | Return "No"            | { 1:1, 2:0, 3:1 }      |
 * 
 * Result: "No"
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine a grocery store inventory (`arr1`). 
 * A customer brings a shopping list (`arr2`). 
 * For each item on the list, you check if the store has it in stock. 
 * If it is in stock, you take one off the shelf (decrement count). 
 * If you run out of any item, the list cannot be fulfilled ("No").
 * 
 * 1-MINUTE QUICK REVISION:
 * - Build a frequency map of elements in `arr1`.
 * - Iterate through elements in `arr2`:
 *   - If the element is not present or its count is `0`, return `"No"`.
 *   - Otherwise, decrement its count in the map.
 * - If the loop completes successfully, return `"Yes"`.
 * - Time Complexity: O(N + M)
 * - Space Complexity: O(N)
 */
