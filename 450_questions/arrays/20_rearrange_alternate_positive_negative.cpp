/*
 * QUESTION: Rearrange the array in alternating positive and negative items with O(1) extra space (stable order)
 * Link: https://www.geeksforgeeks.org/rearrange-array-alternating-positive-negative-items-o1-extra-space/
 * 
 * Input: arr[] = {1, 2, 3, -4, -1, 4}
 * Output: arr[] = {-4, 1, -1, 2, 3, 4} (Assuming negative starts at index 0, or positive at index 0)
 * Note: Let's arrange so that negative numbers are at even indices (0, 2, ...) and positive at odd indices (1, 3, ...).
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Rotates the subarray arr[start...end] right by one position, putting arr[end] at arr[start].
void rightRotate(std::vector<int>& arr, int start, int end) {
    int temp = arr[end];
    for (int i = end; i > start; i--) {
        arr[i] = arr[i - 1];
    }
    arr[start] = temp;
}

// Rearranges the array in alternating negative and positive items with O(1) extra space.
void rearrangeAlternate(std::vector<int>& arr) {
    int n = arr.size();
    int out_of_place = -1;
    
    for (int index = 0; index < n; index++) {
        if (out_of_place >= 0) {
            // Find the next element of opposite sign to swap with the out-of-place element
            if (((arr[index] >= 0) && (arr[out_of_place] < 0)) ||
                ((arr[index] < 0) && (arr[out_of_place] >= 0))) {
                
                rightRotate(arr, out_of_place, index);
                
                // The new out-of-place element will be shifted by 2
                if (index - out_of_place >= 2) {
                    out_of_place += 2;
                } else {
                    out_of_place = -1;
                }
            }
        }
        
        // Identify if current element is out of place
        if (out_of_place == -1) {
            // Even index should have negative, odd index should have positive (or vice-versa)
            // Let's expect: negative at even index, positive at odd index
            if ((index % 2 == 0 && arr[index] >= 0) || (index % 2 != 0 && arr[index] < 0)) {
                out_of_place = index;
            }
        }
    }
}

/*
 * DRY RUN (arr = {1, 2, 3, -4, -1, 4}):
 * Initial check: negative at even index, positive at odd index
 * 
 * | Step | Index | Val | out_of_place | Action/Rotation                                  | Array State          |
 * | :--- | :---- | :-- | :----------- | :----------------------------------------------- | :------------------- |
 * | Init | 0     | 1   | -1 -> 0      | Index 0 has positive (1) -> out_of_place = 0      | {1, 2, 3, -4, -1, 4} |
 * | 1    | 1     | 2   | 0            | 2 is positive (same sign) -> do nothing          | {1, 2, 3, -4, -1, 4} |
 * | 2    | 2     | 3   | 0            | 3 is positive (same sign) -> do nothing          | {1, 2, 3, -4, -1, 4} |
 * | 3    | 3     | -4  | 0            | -4 is negative (opposite) -> rotate(0,3)         | {-4, 1, 2, 3, -1, 4} |
 * |      |       |     | 0 -> 2       | out_of_place += 2 -> becomes 2                   |                      |
 * | 4    | 4     | -1  | 2            | -1 is negative (same sign as arr[2]=2 is pos) - no|                      |
 * |      |       |     |              | wait, arr[2]=2 (positive), arr[4]=-1 (negative)  |                      |
 * |      |       |     |              | opposite sign -> rotate(2, 4)                    | {-4, 1, -1, 2, 3, 4} |
 * |      |       |     | 2 -> 4       | out_of_place += 2 -> becomes 4                   |                      |
 * | 5    | 5     | 4   | 4            | arr[4]=3 (positive), arr[5]=4 (positive) - same  | {-4, 1, -1, 2, 3, 4} |
 * 
 * Final State: {-4, 1, -1, 2, 3, 4}
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine organizing a line of alternating boys and girls. 
 * You walk down the line. The first person out of position (e.g., a boy where a girl should be) is noted. 
 * You keep walking until you find someone of the correct gender. 
 * You pull them out, slide everyone else down to make room, and place them in the correct spot.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Define even indices as negative and odd indices as positive (or vice-versa).
 * - Traverse the array. Find the first index `out_of_place` that violates this rule.
 * - Once found, continue traversing to find the next element `index` with the opposite sign.
 * - Rotate the subarray `rightRotate(arr, out_of_place, index)`.
 * - If the distance swapped is >= 2, the next out of place element shifts by 2 (`out_of_place += 2`), otherwise reset it to `-1`.
 * - Time Complexity: O(N^2) in the worst case (rotation takes O(N)).
 * - Space Complexity: O(1) auxiliary space (in-place).
 */
