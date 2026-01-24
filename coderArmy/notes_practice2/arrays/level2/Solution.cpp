#include <iostream>
using namespace std;

//Array level 2 (class notes 8)

//Q1. Program to find unique element
void findUniqueElement(int arr[], int raw)
{

    int count = 0;
    for (int i = 0; i < raw; i++)
    {
        count ^= arr[i];   
    }
    cout<<count;
}

// Q2. print all pairs
void printAllPairs(int arr[], int size)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout<<arr[i] <<" " << arr[j]<<endl;
        }
        
    }
}

// Q3. print all triples
void printAllPairsTriples(int arr[], int size)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
        {
                cout<<arr[i] <<", "<<arr[j] << ", "<<arr[k]<<endl;
        }
        }
    }
}

//Q4. Counting 0's and 1's Brute force
void countZeroAndOne(int arr[], int size)
{
    int countZero = 0;
    int countOne  = 0;
    for (int i = 0; i < size; i++)
    {
        if(arr[i]==0){
            countZero++;
        }
        if(arr[i]==1){
            countOne++;
        }   
    }
    cout<<"Count zero is "<<countZero<< " -> count one is " << countOne<<endl;

    for(int i =0;i<countZero;i++){
        arr[i]=0;
    }
    for(int i=countZero;i<countOne;i++){
        arr[i]=1;
    }

    for(int i = 0;i<6;i++){
        cout<<arr[i]<< " ";
    }
    cout<<endl;
}

// Q5. Optimization of count zero and count one.
void countZeroAndOneOptimize(int arr[], int size)
{
    int s=0;
    int e = 6-1;
    while(s<e){
        while(s<e && arr[s]==0){
            s++;
        }
        while( s<e && arr[e]==1){
            e--;
        }
        s++;
        e--;

        if(s<e && arr[s] == 1 && arr[e] == 0){
            swap(arr[s], arr[e]);
            s++;
            e--;
        }
    }

    for(int i = 0;i<6;i++){
        cout<<arr[i]<< " ";
    }
    cout<<endl;
}

// Linear search in 2d array
bool linearSearch2d(int arr[][3], int target, int raw, int col)
{

    for (int i = 0; i < raw; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (arr[i][j] == target)
            {
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char const *argv[])
{
    int arr[3][3] = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90}};
    
    int nums[] = {1,2,2,3,4,4,1};
    findUniqueElement(nums,7);
    cout<<endl;

    int arr1[] = {10,20,30};
    printAllPairs(arr1, 3);

    cout<<endl;
    printAllPairsTriples(arr1, 3);

    cout<<endl;
    int arr2[]={1,1,0,0,1,1};
    countZeroAndOne(arr2,6);

    countZeroAndOneOptimize(arr2, 6);

    bool isPresent = linearSearch2d(arr, 20, 3, 3);
    cout << "is present " << isPresent<<endl;
    return 0;
}
