#include <iostream>
using namespace std;

//Q1 moving all neg number to left side of array
void moveToleft(int arr[],int size){
    int i=0;
    int j = 0;
    while(i<size){
        if(arr[i]>0){
            i++;
        }else{
            swap(arr[i],arr[j]);
            i++;
            j++;
        }
    }
}

void print(int arr[], int size){
    for(int i=0;i<size;i++){
        cout<<arr[i]<< " ";
    }
}

int main(int argc, char const *argv[])
{
    int arr[]={23,-7,12,-10,-11,40,-60};
    int size=7;
    moveToleft(arr, size);
    print(arr, size);
    return 0;
}
