/*
geekforgeeks link: https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1
You are given N meetings with their start and end times. Your task is to find the maximum
number of meetings that can be performed in a meeting room.
Note: Start time of one chosen meeting can't be equal to the end time of the other chosen meeting.
Example 1:
Input: start = [1, 2, 3], end = [2, 3, 4]
Output: 2
Explanation: The meetings will be performed in the following manner:
1st meeting at time (1, 2) and 3rd
meeting at (3, 4).
Example 2:
Input: start = [1, 2, 3], end = [2, 3, 5]
Output: 2
Explanation: The meetings will be performed in the following manner:
1st meeting at time (1, 2) and 2nd
meeting at (2, 3).
Your Task:
You don't need to read input or print anything. Your task is to complete the function maxMeetings() which takes two lists start[] and end[] as input parameters and returns the maximum number of meetings that can be performed in a meeting room.
Expected Time Complexity: O(N*LogN)
Expected Auxiliary Space: O(N)
Constraints:    
1 ≤ N ≤ 10^5
1 ≤ start[i] < end[i] ≤ 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// custom comparator function to sort the meetings based on their end time
// in ascending order
// if end time is same then sort based on start time
// in ascending order
bool comp(pair<int, int>& a, pair<int, int>& b) {
    return a.second < b.second;
}

class Solution {
  public:
    // Function to find the maximum number of meetings that can
    // be performed in a meeting room.
    int maxMeetings(vector<int>& start, vector<int>& end) {
        vector<pair<int, int>> meetings;
        int n = start.size();
        // store the start and end time of each meeting in a pair
        // and push it into a vector
        // then sort the vector based on the end time of the meetings
        // using the custom comparator function
        // finally, iterate through the sorted vector and count the number of
        // meetings that can be performed in the meeting room
        // by checking if the start time of the current meeting is greater
        // than the end time of the last meeting that was performed
        // if yes, then increment the count and update the end time
        // of the last meeting that was performed
        // else, move to the next meeting
        for (int i = 0; i < n; i++) {
            meetings.push_back({start[i], end[i]});
        }
        sort(meetings.begin(), meetings.end(), comp);
        int total = 0;
        int ending_time = -1;
        for (auto m : meetings) {
            if (m.first > ending_time) {
                total++;
                ending_time = m.second;
            }
        }
        return total;
    }
};
// dry run
// start = [1, 2, 3], end = [2, 3, 4]
// meetings = [(1, 2), (2, 3), (3, 4)]
// sorted meetings = [(1, 2), (2, 3), (3, 4)]
// total = 0, ending_time = -1
// m = (1, 2) -> 1 > -1 -> total = 1, ending_time = 2
// m = (2, 3) -> 2 > 2 -> total = 1, ending_time = 2
// m = (3, 4) -> 3 > 2 -> total = 2, ending_time = 4
// return total = 2
// time complexity: O(nlogn) + O(n) = O(nlogn)
// space complexity: O(n) for the meetings vector