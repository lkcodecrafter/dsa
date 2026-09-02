/*
 * QUESTION: Given an array of size n and a number k, find all elements that appear more than " n/k " times.
 * Link: https://leetcode.com/problems/majority-element-ii/ (For k=3)
 * 
 * Input: arr[] = {3, 1, 2, 2, 1, 2, 3, 3}, k = 4
 * Output: {2, 3}
 * Explanation: n = 8, k = 4. We want elements appearing > 8/4 = 2 times. 
 * Frequency of 3 is 3, 2 is 3, 1 is 2. Elements appearing > 2 times are 2 and 3.
 */

#include <iostream>
#include <vector>
#include <unordered_map>

// Returns all elements that appear more than n/k times.
std::vector<int> majorityElementNK(const std::vector<int>& arr, int k) {
    int n = arr.size();
    std::vector<int> result;
    
    if (k <= 0) return result;
    
    int threshold = n / k;
    std::unordered_map<int, int> freq_map;
    
    // Count frequencies of each element
    for (int num : arr) {
        freq_map[num]++;
    }
    
    // Collect elements whose frequencies are strictly greater than threshold
    for (auto const& [num, count] : freq_map) {
        if (count > threshold) {
            result.push_back(num);
        }
    }
    
    return result;
}

/*
 * DRY RUN (arr = {3, 1, 2, 2, 1, 2, 3, 3}, k = 4):
 * n = 8, threshold = 8 / 4 = 2.
 * 
 * Frequency map built:
 * {
 *   3: 3,
 *   1: 2,
 *   2: 3
 * }
 * 
 * | Element | Count | Count > 2? | Action             | Result State |
 * | :------ | :---- | :--------- | :----------------- | :----------- |
 * | 3       | 3     | Yes        | Push to result     | {3}          |
 * | 1       | 2     | No         | Skip               | {3}          |
 * | 2       | 3     | Yes        | Push to result     | {3, 2}       |
 * 
 * Result: {3, 2}
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine a voting booth where we count the total ballots. 
 * We record every vote in our registry (the map). 
 * At the end of the day, we calculate the winning quota (`n / k`). 
 * Any candidate whose count exceeds this quota is declared a winner.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Calculate the threshold = `n / k`.
 * - Use an `unordered_map` to count frequencies of each element in the array.
 * - Iterate through the map and add keys to the result vector if their value (frequency) is strictly greater than `threshold`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(N)
 */
