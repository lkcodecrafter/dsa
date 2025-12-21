#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numberOfMatches(int n) {

        int matches = 0;
        while (n > 1) {

            if (n % 2 == 0) {
                matches += n / 2;
                n /= 2;
            } else {
                matches += (n - 1) / 2;
                n = (n - 1) / 2 + 1;
            }
        }

        return matches;
    }
};




int main(){

    int num = 7;
    Solution sol;
    cout<<sol.numberOfMatches(num);
    return 0;
}