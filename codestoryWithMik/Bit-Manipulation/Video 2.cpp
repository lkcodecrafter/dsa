#include <bits/stdc++.h>
using namespace std;


//Problem Name : Single Number II
//Company Tags  : GOOGLE, AMAZON


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result =0;
        for(int i=0;i<=31;i++){
            int temp = 1<<i;
            int countOne = 0;
            for(int& num : nums){
                if((num & temp) == 0){

                }else{
                    countOne++;
                }
            }

            if(countOne %3 == 1){
                result|=temp;
            }
        }
        return result;      
    }
};
