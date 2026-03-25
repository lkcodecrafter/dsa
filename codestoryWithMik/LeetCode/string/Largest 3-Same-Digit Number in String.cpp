#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string largestGoodInteger(string num) {
        
        char maxChar = ' ';
        for(int i=2;i<num.length();i++){
            if(num[i]==num[i-1] && num[i]==num[i-2]){
                maxChar = max(maxChar, num[i]);
            }
        }
        if(maxChar == ' '){
            return "";
        }

        return string(3, maxChar);
    }
};


int main(){

    string num = "2300019";
    Solution sol;
    cout<<sol.largestGoodInteger(num);
    
    return 0;
}