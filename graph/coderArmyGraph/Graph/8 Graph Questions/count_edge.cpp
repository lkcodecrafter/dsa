/*
https://www.geeksforgeeks.org/problems/shortest-path-from-1-to-n0156/1
Given a positive integer n, find the minimum number of steps to reach from 1 to n
You can perform any of the following 3 steps:
1. Increment the current number by 1 (i.e., x = x + 1
2. Decrement the current number by 1 (i.e., x = x - 1)
3. Double the current number (i.e., x = 2 * x)
Example 1:
Input: n = 3
Output: 2
Explanation: We can reach 3 from 1 in 2 steps as follows:
1 -> 3
Example 2:
Input: n = 10
Output: 4
Explanation: We can reach 10 from 1 in 4 steps as follows:
1 -> 3 -> 9 -> 10

*/
// User function Template for C++

class Solution {
  public:
  // Below function counts the minimum steps to reach from 1 to n
    int minimumStep(int n) {
        int edgeCount =0;
        while(n>=3){
            edgeCount += n%3;
            n = n/3;
            edgeCount++;
        }
        // When n is 1 or 2
        // we need n-1 steps to reach from 1 to n
        edgeCount+=n;
        edgeCount--;
        return edgeCount;
    }
};
// DRY RUN
// n=9
// edgeCount=0
// n>=3 true
// edgeCount+=9%3=0
// n=9/3=3
// edgeCount=0+1=1
// n>=3 true
// edgeCount+=3%3=0
// n=3/3=1
// edgeCount=1+1=2
// n>=3 false
// edgeCount+=1=3 // doubt here jpw 1=3?
// edgeCount--=2
// return 2
// TC: O(log n)
// SC: O(1)
// how egeCount+=1=3?
// when n is 1 or 2
// we need n-1 steps to reach from 1 to n
// so when n=1 edgeCount+=1-1=0
// so when n=2 edgeCount+=2-1=1
