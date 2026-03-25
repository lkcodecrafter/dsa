#include <bits/stdc++.h>
using namespace std;

//Minimum Flips to Make a OR b Equal to c  2 Approaches  Microsoft  Leetcode-1318  Explanation

class Solution {
public:
    int minFlips(int a, int b, int c) {
        int flips = 0;
        while (a != 0 || b != 0 || c != 0) {
            if ((c & 1) == 1) {
                if ((a & 1) == 0 && (b & 1) == 0) {
                    flips++;
                }
            } else {
                if ((a & 1) == 1)
                    flips++;
                if ((b & 1) == 1)
                    flips++;
            }

            a = a >> 1;
            b = b >> 1;
            c = c >> 1;
        }
        return flips;
    }

    //method 2
     int minFlips(int a, int b, int c) {
        int result = (a|b) ^c;
        __builtin_popcount(result) + __builtin_popcount(  (a & b) & (result));
    }
};