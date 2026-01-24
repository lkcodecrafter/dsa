// Program 01: Find unique element
#include <iostream>
#include<vector>
using namespace std;

vector<int> getUnique(int nums[], int n) {
    vector<int> res(n);
    int m = 0;

    // XOR all elements and store the intermediate results
    for (int i = 0; i < n; i++) {
        m ^= nums[i];
        res[i] = m;  // Store XOR result at each step
    }

    return res;
}

int main(){
    int arr[] = {2, 10, 11, 13, 10, 2, 16, 13, 16, 1};  // Array with 10 elements
    int n = 10;  // Corrected array size to match the number of elements

    // Calling method
    vector<int> finalAns = getUnique(arr, n);

    // Print the XOR results at each step
    for (size_t i = 0; i < finalAns.size(); i++) {
        cout << finalAns[i] << " ";
    }
    

    return 0;
}