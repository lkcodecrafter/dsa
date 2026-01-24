#include <iostream>
#include <vector>
using namespace std;

// Array level 3 (class notes 9)

// Print 2d array row wise
void printArrayrow(int arr[][3], int row, int col)
{

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Print 2d array col wise
void printArrayCol(int arr[][3], int row, int col)
{

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            cout << arr[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Print 2d array row wise
void takingInputFromUser(int arr[][3], int row, int col)
{

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << "Row index = " << i << " Column Index = " << j << endl;
            cin >> arr[i][j];
        }
        cout << endl;
    }
    cout << endl;
    printArrayrow(arr, 3, 3);
}

// Linear search in 2d array
bool linearSearch2d(int arr[][3], int target, int row, int col)
{

    for (int i = 0; i < row; i++)
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

// Find min and max in 2d Array
void findMinMax(int arr[][3], int row, int col)
{
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (arr[i][j] < min)
            {
                min = arr[i][j];
            }
            if (arr[i][j] > max)
            {
                max = arr[i][j];
            }
        }
    }

    cout << endl;
    cout << "The max value is " << max << " The min value is " << min;
}

// Linear search in 2d array
void printRowWisesum(int arr[][3], int row, int col)
{
    for (int i = 0; i < row; i++)
    {

        int sum = 0;
        for (int j = 0; j < col; j++)
        {
            sum += arr[i][j];
        }

        cout << "The sum is " << sum << endl;
    }
}

// Linear search in 2d array
void printClowWisesum(int arr[][3], int row, int col)
{
    for (int i = 0; i < col; i++)
    {

        int sum = 0;
        for (int j = 0; j < row; j++)
        {
            sum += arr[j][i];
        }

        cout << "The sum is " << sum << endl;
    }
}

// print sum of diagonal in matrix
void printDiagonalSum(int arr[][3], int row, int col)
{
    int sum = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == j)
            {
                sum += arr[i][j];
            }
        }
    }
    cout << sum;
}

// print col sum of diagonal in matrix
void printColDiagonalSum(int arr[][3], int row, int col)
{
    int sum = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i + j == (col - 1))
            {
                sum += arr[i][j];
            }
        }
    }
    cout << sum;
}

void transposMatrix(int arr[][3], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = i; j < col; j++)
        {
            swap(arr[i][j], arr[j][i]);
        }
    }
}

// Introduction to vector array
//  dynamic size
void initialize1DVector()
{
    vector<int> arr3; // declare of vector

    // insert element into vector
    arr3.push_back(1); // capacity 1, size 1
    arr3.push_back(2); // capacity 2, size 2
    arr3.push_back(3); // capacity 4, size 3
    arr3.push_back(4); // capacity 4, size 4
    arr3.push_back(5); // capacity 8, size 5

    cout << "Array capacity " << arr3.capacity() << " Array size " << arr3.size() << endl;
    // above output is  Array capacity 8 Array size 5

    // Access 1D's vector

    for (int i = 0; i < arr3.size(); i++)
    {
        cout << arr3[i]; // 1,2,3,4,5
    }
    cout << endl;
    // Delete element from 1D's vector array
    arr3.pop_back(); // last element will be removed 1,2,3,4 now array has these element

    // Taking input from user in 1D vector array
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int element = 0;
        cin >> element;
        arr3.push_back(element); // 1,2,3,4,10,20
    }

    // clear the array
    cout << endl;
    arr3.clear();

    // initialize vector with size and specific data
    int size = 5;
    int data = 1;
    vector<int> arr4(size, data); // output -> 1 1 1 1 1

    // //initialize vector array with data only
    vector<int> arr5 = {1, 2, 3, 4, 5};

    // //copy one array to other
    vector<int> arr6(arr5); // {1,2,3,4,5}

    // //print vector
    for (int i = 0; i < arr6.size(); i++)
    {
        cout << arr6[i] << " ";
    }
}

void initialize2DVector()
{
    vector<vector<int>> arr; // declare

    // name            row size initialize of row items
    vector<vector<int>> arr2(5, vector<int>(10, 0));

    // Access
    int rowSize = arr2.size();    // 5
    int colSize = arr2[0].size(); // 10

    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            cout << arr2[i][j] << " ";
        }
        cout << endl;
    }


    //Array into array
    vector<int>item1(5,5);
    vector<int>item2(5,4);
    vector<int>item3(5,3);
    vector<int>item4(5,2);
    vector<int>item5(5,1);
    vector<vector<int>>list;
    list.push_back(item1);
    list.push_back(item2);
    list.push_back(item3);
    list.push_back(item4); 
    list.push_back(item5);

    for (int i = 0; i < list.size(); i++)
    {
        for (int j = 0; j < list[0].size(); j++)
        {
            cout << list[i][j] << " ";
        }
        cout << endl;
    }

}

int main(int argc, char const *argv[])
{
    int arr[3][3] = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90}};

    printArrayrow(arr, 3, 3);
    cout << endl;

    printArrayCol(arr, 3, 3);

    int arr1[3][3];
    // takingInputFromUser(arr1,3,3);

    bool isPresent = linearSearch2d(arr, 20, 3, 3);
    if (isPresent)
    {
        cout << "Target found";
    }
    else
    {
        cout << "Target not found";
    }

    findMinMax(arr, 3, 3);
    cout << endl;

    int arr2[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    printRowWisesum(arr2, 3, 3);
    cout << endl;
    printClowWisesum(arr2, 3, 3);
    cout << endl;

    printDiagonalSum(arr2, 3, 3);
    cout << endl;
    printColDiagonalSum(arr2, 3, 3);
    cout << endl;
    transposMatrix(arr2, 3, 3);
    printArrayrow(arr2, 3, 3);
    cout << "Starting of vector " << endl;

    initialize1DVector();
    cout<<endl;
    initialize2DVector();
    return 0;
}
