#include<iostream>
#include<vector>
using namespace std;

int main(){
    
    vector<int>v={1,2,3,4,5};
    vector<int>v1=move(v); // move semantics, moves the contents of v to v1, 
    //  leaving v in a valid but unspecified state. This is more efficient than copying the contents of v to v1, especially for large vectors, because it avoids the overhead of copying each element.
   // cout<<v[0]<<endl; // 1 // v is left in a valid but unspecified state means that the contents of v are still accessible, but they may not be the same as they were before the move operation. In this case, v still contains the value 1 at index 0, but the other elements may have been moved to v1 or may be in an unspecified state.

    // v[0] giving me segmentation fault, because v is in a valid but unspecified state after the move operation. 
    // This means that the contents of v may have been moved to v1 or may be in an unspecified state, 
    // and accessing v[0] may result in undefined behavior. In this case, v[0] is still accessible and contains the value 1, but it is not guaranteed to be valid or meaningful.

    cout<<v1[0]<<endl; // 2

}