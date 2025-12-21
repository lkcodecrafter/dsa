#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>>result(n, vector<int>(m));

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                result[j][i]=matrix[i][j];
            }
        }

        return result;
    }


//Follow up question    
    vector<vector<int>> transposeFollowUp(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>>result(n, vector<int>(m));

        for(int i=0;i<m;i++){
            for(int j=i+1;j<n;j++){
                swap(matrix[i][j], matrix[i][j]);
            }
        }

        return result;
    }
    
};




int main(){    
    Solution sol;
    return 0;
}