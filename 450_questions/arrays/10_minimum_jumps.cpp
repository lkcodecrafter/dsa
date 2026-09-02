/*
 * QUESTION: Minimum number of jumps to reach end of an array
 * Link: https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps/0
 * 
 * Input: arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9}
 * Output: Min Jumps = 3
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Returns the minimum number of jumps to reach the end of the array. Returns -1 if unreachable.
int minJumps(const std::vector<int>& arr) {
    int n = arr.size();
    
    // If the array has only 1 element, we are already at the end
    if (n <= 1) return 0;
    
    // If the first element is 0, we can't move anywhere
    if (arr[0] == 0) return -1;
    
    int max_reach = arr[0]; // Stores the maximum index we can reach
    int steps = arr[0];     // Stores the steps we can still take in the current jump range
    int jumps = 1;          // Number of jumps taken so far
    
    for (int i = 1; i < n; i++) {
        // If we have reached the last element
        if (i == n - 1) return jumps;
        
        // Update the maximum reach
        max_reach = std::max(max_reach, i + arr[i]);
        
        // Use a step to move to the current index
        steps--;
        
        // If no more steps are left
        if (steps == 0) {
            // We must take a jump
            jumps++;
            
            // Check if we can move further from this point
            if (i >= max_reach) {
                return -1;
            }
            
            // Re-initialize the steps for the new jump range
            steps = max_reach - i;
        }
    }
    
    return -1;
}

/*
 * DRY RUN (arr = {1, 3, 5, 8, 9}, n = 5):
 * Initial: max_reach = 1, steps = 1, jumps = 1
 * 
 * | Step | i | arr[i] | max_reach = max(max_reach, i+arr[i]) | steps | jumps | Action / Condition                       |
 * | :--- | :-| :----- | :----------------------------------- | :---- | :---- | :--------------------------------------- |
 * | Init | - | -      | 1                                    | 1     | 1     | Start loop at index 1                    |
 * | 1    | 1 | 3      | max(1, 1+3) = 4                      | 0     | 1     | steps--; steps becomes 0 -> jumps++, steps=max_reach-i = 3 |
 * |      |   |        |                                      | 3     | 2     |                                          |
 * | 2    | 2 | 5      | max(4, 2+5) = 7                      | 2     | 2     | steps--; steps becomes 2                 |
 * | 3    | 3 | 8      | max(7, 3+8) = 11                     | 1     | 2     | steps--; steps becomes 1                 |
 * | 4    | 4 | 9      | -                                    | -     | 2     | i == n - 1 -> return jumps (2)           |
 * 
 * Min Jumps: 2
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Think of it as driving a car. `max_reach` is the maximum distance we can travel with the fuel stations we've seen.
 * `steps` is the fuel left in our tank. When the fuel runs out (`steps == 0`), we must make a stop (increment jump) 
 * and fill up to the max capacity we've seen (`steps = max_reach - i`). If we run out of fuel and have seen no new stations, we get stranded (-1).
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize: `max_reach = arr[0]`, `steps = arr[0]`, `jumps = 1`.
 * - Loop from `i = 1` to `n-2`:
 *   - Update `max_reach = max(max_reach, i + arr[i])`.
 *   - Decrement `steps`.
 *   - If `steps == 0`: Increment `jumps`. If `i >= max_reach`, return `-1`. Set `steps = max_reach - i`.
 * - If `i == n-1`, return `jumps`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1)
 */
