#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    
    int myAtoi(string s) {
        int i=0;
        int sign =1;
        int n = s.length();
        while(i<n && s[i]==' '){
            i++;
        }
        if(i==n){
            return 0;
        }
        if(i<n && (s[i]=='-' || s[i]=='+')){
            if(s[i]=='-') sign = -1;
            i++;
        }
        long long result = 0;
        while(i<n && s[i] >='0' && s[i] <='9'){
            int digit = s[i]-'0';
            result = result *  10 + digit;

            if(sign == 1 && result > INT_MAX){
                return INT_MAX;
            }
            if(sign ==-1 && -1* result < INT_MIN){
                return INT_MIN;
            }
            i++;
        }

        return sign * result;
    }
};