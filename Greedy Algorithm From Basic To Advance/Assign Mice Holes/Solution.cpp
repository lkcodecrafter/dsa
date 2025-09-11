/*
https://www.geeksforgeeks.org/problems/assign-mice-holes3053/0

You are given two arrays mices[] and holes[] of the same size. The array mices[] represents the positions of the mice on a straight line, while the array holes[] represents the positions of the holes on the same line. Each hole can accommodate exactly one mouse. A mouse can either stay in its current position, move one step to the right, or move one step to the left, and each move takes one minute. The task is to assign each mouse to a distinct hole in such a way that the time taken by the last mouse to reach its hole is minimized.

Examples:

Input: mices[] = [4, -4, 2], holes[] = [4, 0, 5] 
Output: 4
Explanation: Assign the mouse at position 4 to the hole at position 4, so the time taken is 0 minutes. Assign the mouse at position −4 to the hole at position 0, so the time taken is 4 minutes. Assign the mouse at position 2 to the hole at position 5, so the time taken is 3 minutes. Hence, the maximum time required by any mouse is 4 minutes.
Input: mices[] = [1, 2], holes[] = [20, 10] 
Output: 18 
Explanation: Assign the mouse at position 1 to the hole at position 10, so the time taken is 9 minutes. Assign the mouse at position 2 to the hole at position 20, so the time taken is 18 minutes. Hence, the maximum time required by any mouse is 18 minutes.

Constraints:
1 ≤ mices.size() = holes.size() ≤ 105
-105 ≤ mices[i] , holes[i] ≤ 105

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
  public:
    int assignHole(vector<int>& mices, vector<int>& holes) {
        // code here
        // Explanation: To minimize the time taken by the last mouse to reach its hole,
        // we can sort both the mices and holes arrays. Then, we can assign each mouse to the hole at the same index in the sorted arrays.
        // This way, each mouse will be assigned to the closest available hole, minimizing the maximum distance any mouse has to travel.
        // Dry run for mices = [4, -4, 2], holes = [4, 0, 5]
        // After sorting, mices = [-4, 2, 4], holes = [0, 4, 5]
        // Assign mouse at -4 to hole at 0 -> time = 4
        // Assign mouse at 2 to hole at 4 -> time = 2
        // Assign mouse at 4 to hole at 5 -> time = 1
        // Maximum time = 4
        // This approach ensures that the maximum time taken by any mouse to reach its hole is minimized.
        // Time Complexity: O(n log n) due to sorting
        // Space Complexity: O(1) if we ignore the input space
        // where n is the number of mice (or holes)
        sort(mices.begin(), mices.end());
        sort(holes.begin(), holes.end());
        int maxTime = 0;
        for (int i = 0; i < mices.size(); i++) {
            maxTime = max(maxTime, abs(mices[i] - holes[i]));
        }
        return maxTime;
    }
};