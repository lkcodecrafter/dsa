/*
 * QUESTION: Find all pairs in an integer array whose sum is equal to a given number
 * Link: https://practice.geeksforgeeks.org/problems/count-pairs-with-given-sum5022/1
 * 
 * Input: arr[] = {1, 5, 7, 1}, sum = 6
 * Output: Pair Count = 2
 * Explanation: Pairs are (1, 5) and (5, 1) at indexes 0,1 and 1,3.
 */

#include <iostream>
#include <vector>
#include <unordered_map>

// Returns the number of pairs with the given sum.
int getPairsCount(const std::vector<int>& arr, int target) {
    std::unordered_map<int, int> freq_map;
    int pair_count = 0;
    
    for (int num : arr) {
        int complement = target - num;
        
        // If complement exists in map, add its frequency to pair_count
        if (freq_map.find(complement) != freq_map.end()) {
            pair_count += freq_map[complement];
        }
        
        // Increment frequency of current number
        freq_map[num]++;
    }
    
    return pair_count;
}

/*
 * DRY RUN (arr = {1, 5, 7, 1}, target = 6):
 * 
 * | Step | Element | Complement = 6 - Element | Complement in Map? (Frequency) | pair_count | Freq Map State                |
 * | :--- | :------ | :----------------------- | :----------------------------- | :--------- | :----------------------------- |
 * | Init | -       | -                        | -                              | 0          | {}                             |
 * | 1    | 1       | 5                        | No                             | 0          | {1: 1}                         |
 * | 2    | 5       | 1                        | Yes (freq = 1)                 | 1          | {1: 1, 5: 1}                   |
 * | 3    | 7       | -1                       | No                             | 1          | {1: 1, 5: 1, 7: 1}             |
 * | 4    | 1       | 5                        | Yes (freq = 1)                 | 2          | {1: 2, 5: 1, 7: 1}             |
 * 
 * Total Pair Count = 2
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine a matchmaking dance. Each person enters, calculates their perfect partner's size (`target - size`), 
 * looks at the room (the map) to see how many matching partners are waiting, adds that count to the total match registry, 
 * and then joins the waiting room.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Use an `unordered_map<int, int>` to store the frequency of elements visited.
 * - Iterate through the array:
 *   - Calculate `complement = target - arr[i]`.
 *   - If `complement` is in the map, add `map[complement]` to the answer.
 *   - Increment the frequency of `arr[i]` in the map.
 * - Time Complexity: O(N) average time complexity.
 * - Space Complexity: O(N) for the frequency map.
 */
