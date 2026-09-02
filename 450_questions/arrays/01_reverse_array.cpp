/*
 * QUESTION: Reverse the array
 * Link: https://www.geeksforgeeks.org/write-a-program-to-reverse-an-array-or-string/
 * 
 * Input: arr[] = {1, 2, 3, 4, 5}
 * Output: arr[] = {5, 4, 3, 2, 1}
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Reverses the given vector in-place.
void reverseArray(std::vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
    // Move pointers towards each other, swapping elements
    while (left < right) {
        std::swap(arr[left], arr[right]);
        left++;
        right--;
    }
}

/*
 * DRY RUN:
 * Initial Array: {1, 2, 3, 4, 5}
 * 
 * | Step | left | right | arr[left] | arr[right] | Action           | Array State       |
 * | :--- | :--- | :---- | :-------- | :--------- | :--------------- | :---------------- |
 * | Init | 0    | 4     | 1         | 5          | Swap & increment | {5, 2, 3, 4, 1}   |
 * | 1    | 1    | 3     | 2         | 4          | Swap & increment | {5, 4, 3, 2, 1}   |
 * | 2    | 2    | 2     | 3         | 3          | Loop ends        | {5, 4, 3, 2, 1}   |
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine two people at the ends of a line swapping seats. 
 * They walk towards each other and meet in the middle. 
 * Once they cross or meet, the entire line is reversed.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Use two pointers: `left = 0`, `right = n - 1`.
 * - While `left < right`, swap `arr[left]` and `arr[right]`, then increment `left` and decrement `right`.
 * - Time Complexity: O(N) since we visit each element once.
 * - Space Complexity: O(1) auxiliary space as we do it in-place.
 */
