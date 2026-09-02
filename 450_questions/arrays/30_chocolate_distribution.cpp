/*
 * QUESTION: Chocolate Distribution Problem
 * Link: https://practice.geeksforgeeks.org/problems/chocolate-distribution-problem/0
 * 
 * Input: packets[] = {7, 3, 2, 4, 9, 12, 56}, m = 3
 * Output: Min Difference = 2
 * Explanation: We choose packets {3, 2, 4}. Diff is 4 - 2 = 2.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// Returns the minimum difference between maximum and minimum chocolates given to students.
long long findMinDiff(std::vector<long long>& packets, long long m) {
    long long n = packets.size();
    
    // If there are no chocolates or number of students is 0
    if (m == 0 || n == 0) return 0;
    
    // Number of packets cannot be less than number of students
    if (n < m) return -1;
    
    // Step 1: Sort the packets
    std::sort(packets.begin(), packets.end());
    
    long long min_diff = LLONG_MAX;
    
    // Step 2: Slide a window of size m and find the minimum difference
    for (size_t i = 0; i + m - 1 < n; i++) {
        long long current_diff = packets[i + m - 1] - packets[i];
        min_diff = std::min(min_diff, current_diff);
    }
    
    return min_diff;
}

/*
 * DRY RUN (packets = {7, 3, 2, 4, 9, 12, 56}, m = 3):
 * Sorted packets: {2, 3, 4, 7, 9, 12, 56}, n = 7
 * 
 * | Step i | Window Range [i, i+m-1] | Packets in Window | Diff = packets[i+m-1] - packets[i] | min_diff Updated |
 * | :----- | :---------------------- | :---------------- | :--------------------------------- | :--------------- |
 * | Init   | -                       | -                 | -                                  | LLONG_MAX        |
 * | 0      | [0, 2]                  | {2, 3, 4}         | 4 - 2 = 2                          | min(MAX, 2) = 2  |
 * | 1      | [1, 3]                  | {3, 4, 7}         | 7 - 3 = 4                          | min(2, 4) = 2    |
 * | 2      | [2, 4]                  | {4, 7, 9}         | 9 - 4 = 5                          | min(2, 5) = 2    |
 * | 3      | [3, 5]                  | {7, 9, 12}        | 12 - 7 = 5                         | min(2, 5) = 2    |
 * | 4      | [4, 6]                  | {9, 12, 56}       | 56 - 9 = 47                        | min(2, 47) = 2   |
 * 
 * Result: 2
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine you want to distribute bags of candy to a group of friends. 
 * To ensure fairness, you line up all candy bags in order of weight (sorting). 
 * You then pick a group of contiguous bags of size `m` and measure the difference between the heaviest and lightest. 
 * Slide this selection window across the line to find the fairest match.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Sort the array.
 * - Loop from `i = 0` to `n - m`:
 *   - Calculate difference between the last and first element of the window: `diff = arr[i + m - 1] - arr[i]`.
 *   - Update `min_diff = min(min_diff, diff)`.
 * - Return `min_diff`.
 * - Time Complexity: O(N log N)
 * - Space Complexity: O(1) auxiliary space.
 */
