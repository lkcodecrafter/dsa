#include <iostream>
using namespace std;

// Linear search in 2d array
void linearSearch2d(int arr[][3] , int raw, int col)
{

for(int i=0;i<raw;i++){
    for(int j=0;j<col;j++){

 
    }
}
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
    bool isPresent = linearSearch2d(arr, 20, 3, 3);
    cout << "is present " << isPresent;
    return 0;
}
