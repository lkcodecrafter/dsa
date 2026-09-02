/*
 * QUESTION: Minimum number of merge operations required to make an array palindrome
 * Link: https://practice.geeksforgeeks.org/problems/palindromic-array/0 (Referenced for palindromes)
 * 
 * Input: arr[] = {1, 4, 5, 9, 1}
 * Output: Min Operations = 1
 * Explanation: Merge 4 and 5 to get 9. The array becomes {1, 9, 9, 1}, which is a palindrome.
 */

#include <iostream>
#include <vector>

// Returns the minimum number of merge operations to make the array a palindrome.
int minMergeOpsToPalindrome(std::vector<int>& arr) {
    int n = arr.size();
    int ops = 0;
    
    int left = 0;
    int right = n - 1;
    
    while (left < right) {
        // If corner elements are equal, move inward
        if (arr[left] == arr[right]) {
            left++;
            right--;
        }
        // If left element is smaller, merge it with its right neighbor
        else if (arr[left] < arr[right]) {
            arr[left + 1] += arr[left];
            left++;
            ops++;
        }
        // If right element is smaller, merge it with its left neighbor
        else {
            arr[right - 1] += arr[right];
            right--;
            ops++;
        }
    }
    
    return ops;
}

/*
 * DRY RUN (arr = {1, 4, 5, 9, 1}):
 * Initial: left = 0, right = 4, ops = 0
 * 
 * | Step | left | right | arr[left] | arr[right] | Comparison                 | Action (Merge & update pointer)           | ops Updated | Array State       |
 * | :--- | :--- | :---- | :-------- | :--------- | :------------------------- | :---------------------------------------- | :---------- | :---------------- |
 * | Init | 0    | 4     | 1         | 1          | arr[0] == arr[4] (1 == 1)  | left++, right--                           | 0           | {1, 4, 5, 9, 1}   |
 * | 1    | 1    | 3     | 4         | 9          | arr[1] < arr[3] (4 < 9)    | arr[2] += arr[1] (5+4=9), left++          | 1           | {1, 4, 9, 9, 1}   |
 * | 2    | 2    | 3     | 9         | 9          | arr[2] == arr[3] (9 == 9)  | left++, right--                           | 1           | {1, 4, 9, 9, 1}   |
 * | End  | 3    | 2     | -         | -          | left >= right -> Loop ends | Return ops (1)                            | 1           | {1, 4, 9, 9, 1}   |
 * 
 * Total Operations = 1
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Think of two heaps of blocks on both ends of a scale. 
 * You want the scale to be symmetric. 
 * If they are equal, leave them be. 
 * If one side is lighter, you must combine it with its immediate inner neighbor to make it heavier (merge), 
 * incrementing your merge counter. 
 * Repeat until the pointers meet in the center.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize two pointers: `left = 0`, `right = n - 1`.
 * - While `left < right`:
 *   - If `arr[left] == arr[right]`, increment `left` and decrement `right`.
 *   - Else if `arr[left] < arr[right]`, set `arr[left+1] += arr[left]`, increment `left`, increment `ops`.
 *   - Else, set `arr[right-1] += arr[right]`, decrement `right`, increment `ops`.
 * - Return `ops`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1)
 */
