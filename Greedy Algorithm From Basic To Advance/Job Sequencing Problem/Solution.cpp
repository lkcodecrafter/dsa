/*
geekforgeeks: https://practice.geeksforgeeks.org/problems/job-sequencing-problem-1587115620
Job Sequencing Problem
Medium Accuracy: 49.66% Submissions: 100k+ Points: 4
Given N jobs where every job is represented by following three elements of it.
1. Job ID
2. Deadline
3. Profit
Find the number of jobs done and the maximum profit that can be earned by the jobs that are done.
Note: Each job takes a single unit of time, so the minimum possible deadline for any job is 1.
Also, only one job can be scheduled at a time.
Example 1:
Input:  N = 4
Jobs = {(1,4,20),(2,1,10),(3,1,40),(4,1,30)}
Output: 2 60
Explanation: 2 jobs can be done with
maximum profit of 60 (20+40).
Example 2:
Input: N = 5    
Jobs = {(1,2,100),(2,1,19),(3,2,27),(4,1,25),(5,1,15)}
Output: 2 127
Explanation: 2 jobs can be done with
maximum profit of 127 (100+27).
Your Task:
You don't need to read input or print anything. Your task is to complete the function jobSequencing() which takes the array of deadlines and profits and returns a vector of size 2 denoting the number of jobs done and the maximum profit.
Expected Time Complexity: O(NlogN)
Expected Auxiliary Space: O(N)
Constraints: 1 <= N <= 10^5
1 <= Deadline[i] <= 10^5
1 <= Profit[i] <= 10^5
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// A structure to represent a job 
struct Job {
   int id; // Job Id 
   int dead; // Deadline of job 
   int profit; // Profit if job is over before or on deadline 
};

// custom comparator function to sort the jobs based on their profit
// in descending order
bool comp(Job a, Job b) {
    return a.profit > b.profit;
}

class Solution {
  public:
    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit) {
        // code here
        int n = deadline.size();
        vector<Job> jobs(n);
        for (int i = 0; i < n; i++) {
            jobs[i] = {i + 1, deadline[i], profit[i]};
        }
        sort(jobs.begin(), jobs.end(), comp);
        vector<int> result;
        vector<bool> slot(n, false);
        for (auto &[id, d, p] : jobs) {
            for (int j = min(n, d) - 1; j >= 0; j--) {
                if (!slot[j]) {
                    slot[j] = true;
                    result.push_back(p);
                    break;
                }
            }
        }
        return result;
    }
};
 
 
    }
}; 