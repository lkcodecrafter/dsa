/*
    QUESTION    : Find first and last positions of an element in a sorted array
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/first-and-last-occurrences-of-x3116/1
    LeetCode    : https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(log N) - Two binary searches for first and last occurrences
// S.C : O(1)     - Constant space
class Solution {
private:
    int findFirst(int arr[], int n, int x) {
        int low = 0, high = n - 1, first = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] == x) {
                first = mid;
                high = mid - 1; // Continue searching on left side
            } else if (arr[mid] < x) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return first;
    }

    int findLast(int arr[], int n, int x) {
        int low = 0, high = n - 1, last = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] == x) {
                last = mid;
                low = mid + 1; // Continue searching on right side
            } else if (arr[mid] < x) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return last;
    }

public:
    vector<int> find(int arr[], int n, int x) {
        return {findFirst(arr, n, x), findLast(arr, n, x)};
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - First occurrence: if `arr[mid] == x`, `first = mid; high = mid - 1;`
 * - Last occurrence: if `arr[mid] == x`, `last = mid; low = mid + 1;`
 * - Time: O(log N), Space: O(1).
 */
