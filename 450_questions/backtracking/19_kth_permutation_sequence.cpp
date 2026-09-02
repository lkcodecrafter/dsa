/*
 * QUESTION: Find the K-th Permutation Sequence of first N natural numbers
 * Link: https://www.geeksforgeeks.org/find-the-k-th-permutation-sequence-of-first-n-natural-numbers/
 * 
 * Input: N = 3, K = 3
 * Output: "213"
 */

#include <iostream>
#include <vector>
#include <string>

// Returns the Kth permutation sequence of numbers from 1 to N
std::string getKthPermutation(int n, int k) {
    int fact = 1;
    std::vector<int> numbers;
    
    // Step 1: Compute (n-1)! and populate the number list {1, 2, ..., n}
    for (int i = 1; i < n; i++) {
        fact *= i;
        numbers.push_back(i);
    }
    numbers.push_back(n);
    
    std::string ans = "";
    
    // Convert K to 0-based index
    k = k - 1;
    
    // Step 2: Mathematically determine each digit of the permutation
    while (true) {
        // The index of the number to select is k / (n-1)!
        int number_idx = k / fact;
        ans += std::to_string(numbers[number_idx]);
        
        // Remove the selected number from the list
        numbers.erase(numbers.begin() + number_idx);
        
        // Base Case: No more numbers left
        if (numbers.empty()) {
            break;
        }
        
        // Update k and the factorial block size for the next iteration
        k = k % fact;
        fact = fact / numbers.size();
    }
    
    return ans;
}

/*
 * DRY RUN (N = 3, K = 3):
 * Initial numbers = {1, 2, 3}, fact = 2! = 2, k = 3 - 1 = 2
 * 
 * | Step | k | fact | numbers remaining | selected index = k / fact | Selected Number | ans State | k Update = k % fact | fact Update = fact / size |
 * | :--- | :-| :--- | :---------------- | :------------------------ | :-------------- | :-------- | :------------------ | :------------------------ |
 * | Init | 2 | 2    | {1, 2, 3}         | -                         | -               | ""        | -                   | -                         |
 * | 1    | 2 | 2    | {1, 2, 3}         | 2 / 2 = 1                 | numbers[1] = 2  | "2"       | 2 % 2 = 0           | 2 / 2 = 1                 |
 * | 2    | 0 | 1    | {1, 3}            | 0 / 1 = 0                 | numbers[0] = 1  | "21"      | 0 % 1 = 0           | 1 / 1 = 1                 |
 * | 3    | 0 | 1    | {3}               | 0 / 1 = 0                 | numbers[0] = 3  | "213"     | (numbers empty)     | -                         |
 * 
 * Result: "213"
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine you want to find a book in a sorted multi-volume library. 
 * Instead of searching page-by-page (generating all permutations), 
 * you calculate the shelf block size using factorials. 
 * Divide your index `K` by the shelf capacity to identify the volume you need. 
 * Take that volume (digit), remove it from the catalog list, update your index to the remaining pages inside that volume, and repeat.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Calculate `(N-1)!` and store in `fact`. Store `{1, 2, ..., N}` in a list `numbers`.
 * - Convert `K` to 0-based: `k = K - 1`.
 * - Loop:
 *   - Find digit index: `number_idx = k / fact`.
 *   - Append `numbers[number_idx]` to result string and erase it from list.
 *   - If list is empty, break.
 *   - Update `k = k % fact`.
 *   - Update `fact = fact / numbers.size()`.
 * - Time Complexity: O(N^2) (due to list element erasure).
 * - Space Complexity: O(N) auxiliary space.
 */
