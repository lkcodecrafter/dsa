/*
 * QUESTION: Find the duplicate in an array of N+1 Integers
 * Link: https://leetcode.com/problems/find-the-duplicate-number/
 * 
 * Input: arr[] = {1, 3, 4, 2, 2}
 * Output: Duplicate = 2
 */

#include <iostream>
#include <vector>

// Finds the duplicate number in the array using Floyd's Cycle Detection (Tortoise and Hare).
int findDuplicate(const std::vector<int>& arr) {
    if (arr.size() <= 1) return -1;
    
    // Step 1: Detect cycle using slow and fast pointers
    int slow = arr[0];
    int fast = arr[0];
    
    do {
        slow = arr[slow];       // moves 1 step
        fast = arr[arr[fast]];  // moves 2 steps
    } while (slow != fast);
    
    // Step 2: Find the entry point of the cycle (the duplicate element)
    int ptr1 = arr[0];
    int ptr2 = slow;
    
    while (ptr1 != ptr2) {
        ptr1 = arr[ptr1];
        ptr2 = arr[ptr2];
    }
    
    return ptr1;
}

/*
 * VISUALIZATION OF CYCLE (for arr = {1, 3, 4, 2, 2}):
 * Value as pointer to next index:
 * Index:  0  1  2  3  4
 * Value: [1, 3, 4, 2, 2]
 * 
 * 0 -> 1 -> 3 -> 2 -> 4
 *                ^    |
 *                |____| (Cycle at value 2)
 * 
 * DRY RUN:
 * Step 1: Cycle Detection
 * - Start: slow = arr[0] = 1, fast = arr[0] = 1
 * - Iter 1: slow = arr[1] = 3, fast = arr[arr[1]] = arr[3] = 2
 * - Iter 2: slow = arr[3] = 2, fast = arr[arr[2]] = arr[4] = 2
 * - Meeting point: slow == fast == 2
 * 
 * Step 2: Find Cycle Entrance
 * - ptr1 = arr[0] = 1, ptr2 = 2
 * - Iter 1: ptr1 = arr[1] = 3, ptr2 = arr[2] = 4
 * - Iter 2: ptr1 = arr[3] = 2, ptr2 = arr[4] = 2
 * - Meeting point: ptr1 == ptr2 == 2 (Duplicate found!)
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine two runners on a circular track, one running twice as fast as the other. 
 * They must meet somewhere on the track. 
 * Once they meet, if one runner restarts from the beginning of the path and both run at the same speed, 
 * they will meet exactly at the entrance of the cycle.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize `slow = arr[0]` and `fast = arr[0]`.
 * - Run `do { slow = arr[slow]; fast = arr[arr[fast]]; } while (slow != fast);`
 * - Set `ptr1 = arr[0]` and `ptr2 = slow`.
 * - Loop `while (ptr1 != ptr2) { ptr1 = arr[ptr1]; ptr2 = arr[ptr2]; }`
 * - Return `ptr1`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1) without modifying the array.
 */
