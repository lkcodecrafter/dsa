/*
 * QUESTION: Trapping Rain water problem
 * Link: https://practice.geeksforgeeks.org/problems/trapping-rain-water-1587115621/1
 * 
 * Input: arr[] = {3, 0, 0, 2, 0, 4}
 * Output: 10
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Returns the amount of water that can be trapped.
long long trappingWater(const std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 2) return 0;
    
    int left = 0;
    int right = n - 1;
    long long trapped_water = 0;
    int left_max = 0;
    int right_max = 0;
    
    while (left <= right) {
        if (arr[left] <= arr[right]) {
            if (arr[left] >= left_max) {
                left_max = arr[left]; // Update left max boundary
            } else {
                trapped_water += (left_max - arr[left]); // Water trapped above arr[left]
            }
            left++;
        } else {
            if (arr[right] >= right_max) {
                right_max = arr[right]; // Update right max boundary
            } else {
                trapped_water += (right_max - arr[right]); // Water trapped above arr[right]
            }
            right--;
        }
    }
    
    return trapped_water;
}

/*
 * DRY RUN (arr = {3, 0, 2, 0, 4}):
 * Initial: left = 0, right = 4, left_max = 0, right_max = 0, trapped = 0
 * 
 * | Step | left | right | Comparison (arr[left] <= arr[right]) | Boundary Update / Water Calculation                      | left/right Update | trapped |
 * | :--- | :--- | :---- | :----------------------------------- | :------------------------------------------------------- | :---------------- | :------ |
 * | 1    | 0    | 4     | arr[0] <= arr[4] (3 <= 4) -> True    | arr[0] (3) >= left_max (0) -> left_max = 3               | left++ (1)        | 0       |
 * | 2    | 1    | 4     | arr[1] <= arr[4] (0 <= 4) -> True    | arr[1] (0) < left_max (3)  -> trapped += 3 - 0 = 3       | left++ (2)        | 3       |
 * | 3    | 2    | 4     | arr[2] <= arr[4] (2 <= 4) -> True    | arr[2] (2) < left_max (3)  -> trapped += 3 - 2 = 1       | left++ (3)        | 4       |
 * | 4    | 3    | 4     | arr[3] <= arr[4] (0 <= 4) -> True    | arr[3] (0) < left_max (3)  -> trapped += 3 - 0 = 3       | left++ (4)        | 7       |
 * | 5    | 4    | 4     | arr[4] <= arr[4] (4 <= 4) -> True    | arr[4] (4) >= left_max (3) -> left_max = 4               | left++ (5)        | 7       |
 * 
 * Loop ends since left (5) > right (4).
 * Result: 7 (Note: for input {3, 0, 2, 0, 4}, we trap 3 at index 1, 1 at index 2, and 3 at index 3, total 7).
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine a valley with two walls at both ends. 
 * Rainwater is trapped between them. 
 * The lower wall determines the maximum height water can reach. 
 * You process elements from the lower wall side inward, 
 * updating the local wall peak (`left_max` or `right_max`) and summing the difference.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize `left = 0`, `right = n-1`, `left_max = 0`, `right_max = 0`, `trapped_water = 0`.
 * - While `left <= right`:
 *   - If `arr[left] <= arr[right]`:
 *     - If `arr[left] >= left_max`, set `left_max = arr[left]`.
 *     - Else, add `left_max - arr[left]` to `trapped_water`.
 *     - Increment `left`.
 *   - Else (if `arr[left] > arr[right]`):
 *     - If `arr[right] >= right_max`, set `right_max = arr[right]`.
 *     - Else, add `right_max - arr[right]` to `trapped_water`.
 *     - Decrement `right`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1)
 */
