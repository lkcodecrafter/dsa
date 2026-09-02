/*
 * QUESTION: Write a program to cyclically rotate an array by one.
 * Link: https://practice.geeksforgeeks.org/problems/cyclically-rotate-an-array-by-one/0
 * 
 * Input: arr[] = {1, 2, 3, 4, 5}
 * Output: arr[] = {5, 1, 2, 3, 4}
 */

#include <iostream>
#include <vector>

// Cyclically rotates the vector right by one position.
void rotateByOne(std::vector<int>& arr) {
    if (arr.empty()) return;
    
    int last_element = arr.back();
    
    // Shift elements one position to the right, from back to front
    for (int i = arr.size() - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    
    arr[0] = last_element;
}

/*
 * DRY RUN:
 * Initial Array: {1, 2, 3, 4, 5}
 * last_element = 5
 * 
 * | Step | Index i | arr[i] = arr[i - 1]           | Array State       |
 * | :--- | :------ | :---------------------------- | :---------------- |
 * | Init | -       | last_element = arr[4] = 5     | {1, 2, 3, 4, 5}   |
 * | 1    | 3       | arr[4] = arr[3] -> arr[4] = 4 | {1, 2, 3, 4, 4}   |
 * | 2    | 2       | arr[3] = arr[2] -> arr[3] = 3 | {1, 2, 3, 3, 4}   |
 * | 3    | 1       | arr[2] = arr[1] -> arr[2] = 2 | {1, 2, 2, 3, 4}   |
 * | 4    | 0       | arr[1] = arr[0] -> arr[1] = 1 | {1, 1, 2, 3, 4}   |
 * | End  | -       | arr[0] = last_element = 5     | {5, 1, 2, 3, 4}   |
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine a line of people holding hands. 
 * The person at the very end steps out of the line, walks to the very front, and joins. 
 * Everyone else takes a step to the right to make room.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Store the last element: `last_element = arr[n - 1]`.
 * - Shift elements: run a loop from `i = n - 1` down to `1` and set `arr[i] = arr[i - 1]`.
 * - Place the last element: `arr[0] = last_element`.
 * - Time Complexity: O(N) since we perform N-1 shifts.
 * - Space Complexity: O(1) as it is in-place.
 */
