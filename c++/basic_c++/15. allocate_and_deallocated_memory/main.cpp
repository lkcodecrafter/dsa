#include<iostream>
#include<vector>
using namespace std;

int main(){
    int* a = new int(5);
    delete a;

    int *arr = new int[10];
    delete[] arr;
    return 0;


    
    cout<< "---- malloc example ----" << endl;
    // malloc example
    int* malloc_arr = (int*)malloc(5 * sizeof(int));
    free(malloc_arr);

    // vector example using malloc 
    vector<int>* vec = (vector<int>*)malloc(sizeof(vector<int>));
    // Note: malloc does not call the constructor, so we must use placement new if we want to use the vector
    new (vec) vector<int>(); 
    
    vec->push_back(10);
    cout << "Vector element: " << (*vec)[0] << endl;

    // Must manually call destructor before free because malloc/free don't handle object lifecycle
    vec->~vector();
    free(vec);
    

    return 0;




}
