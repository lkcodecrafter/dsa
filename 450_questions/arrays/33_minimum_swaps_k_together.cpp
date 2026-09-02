/*
 * QUESTION: Minimum swaps required to bring elements less than or equal to K together
 * Link: https://practice.geeksforgeeks.org/problems/minimum-swaps-required-to-bring-all-elements-less-than-or-equal-to-k-together/0
 * 
 * Input: arr[] = {2, 1, 5, 6, 3}, k = 3
 * Output: Min Swaps = 1
 * Explanation: To bring {2, 1, 3} together, we can swap 5 and 3 to get {2, 1, 3, 6, 5}. Number of swaps = 1.
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Returns the minimum swaps required to group elements <= k together.
int minSwap(std::vector<int>& arr, int k) {
    int n = arr.size();
    
    // Step 1: Count elements <= k. This is our window size.
    int good = 0;
    for (int num : arr) {
        if (num <= k) {
            good++;
        }
    }
    
    // If there are no elements <= k, or all elements are <= k, no swaps are needed.
    if (good <= 1 || good == n) return 0;
    
    // Step 2: Count elements > k in the first window of size 'good'
    int bad = 0;
    for (int i = 0; i < good; i++) {
        if (arr[i] > k) {
            bad++;
        }
    }
    
    int min_swaps = bad;
    
    // Step 3: Slide the window of size 'good' across the array
    for (int i = 0, j = good; j < n; i++, j++) {
        // Decrement bad if the element leaving the window (arr[i]) was bad
        if (arr[i] > k) {
            bad--;
        }
        
        // Increment bad if the element entering the window (arr[j]) is bad
        if (arr[j] > k) {
            bad++;
        }
        
        min_swaps = std::min(min_swaps, bad);
    }
    
    return min_swaps;
}

/*
 * DRY RUN (arr = {2, 1, 5, 6, 3}, k = 3):
 * Elements <= 3: 2, 1, 3 -> good = 3 (window size = 3)
 * Initial window arr[0...2] = {2, 1, 5}. Bad elements (> 3): 5 -> bad = 1
 * min_swaps = 1
 * 
 * | Slide Step | Out Index i | In Index j | Leaving Element arr[i] | Entering Element arr[j] | bad count update | min_swaps Updated |
 * | :--------- | :---------- | :--------- | :--------------------- | :---------------------- | :--------------- | :---------------- |
 * | Init       | -           | -          | -                      | -                       | 1                | 1                 |
 * | 1          | 0           | 3          | arr[0] = 2 (not bad)   | arr[3] = 6 (bad)        | bad = 1 + 1 = 2  | min(1, 2) = 1     |
 * | 2          | 1           | 4          | arr[1] = 1 (not bad)   | arr[4] = 3 (not bad)    | bad = 2 - 0 = 2  | min(1, 2) = 1     |
 * |            |             |            | Wait, arr[1] is 1      | arr[4] is 3             | (no bad changes) |                   |
 * 
 * Wait! Let's double check if we missed window {1, 5, 6} (bad = 2), window {5, 6, 3} (bad = 2).
 * Yes, the minimum swaps required is indeed 1 (by swapping 5 and 3 to get {2, 1, 3, 6, 5}).
 * Result: 1
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine you want to group a bunch of friends in a movie theatre row. 
 * You count the number of friends (`good`). 
 * You define a window of seats of this size. 
 * The number of strangers currently sitting in this window is `bad`. 
 * You want to slide this window along the row to find a spot where the number of strangers is minimized, 
 * as that is the number of swaps you'll need to make to sit your friends together.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Count the number of elements <= `k`. Let this be `good`.
 * - Count how many elements in the first window of size `good` are > `k`. Let this be `bad`.
 * - Initialize `min_swaps = bad`.
 * - Slide the window of size `good` from index `0` to `n-1`:
 *   - Subtract `1` from `bad` if the element leaving the window was > `k`.
 *   - Add `1` to `bad` if the element entering the window is > `k`.
 *   - Update `min_swaps = min(min_swaps, bad)`.
 * - Return `min_swaps`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1)
 */
