#include<stdlib.h>
#include <iostream>

using namespace std;

int  climb(int n){

    if(n<=0){
        return n;
    }
    if(n<=1 || n<=2){
        return n;
    }

    return climb(n-1) + climb(n-2);
}

int memClimb(int n, int mem[]){
        if(n<=0){
        return n;
    }
    if(n<=1 || n<=2){
        return n;
    }
    if(mem[n]==-1){
        return n;
    }

        return memClimb(n-1, mem) + memClimb(n-2,mem);
}

int optClimb(int n){
    int step1 =1, step2= 2;
    int result = 0;
    if(n<=0){
        return n;
    }

    if(n<=1 || n<=2){
        return n;
    }
    for(int i=2;i<n;i++){
        result = step1  + step2;
        step1 = step2;
        step2= result;
    }

    return result;
}

int main(int argc, char const *argv[])
{
    /* code */
    int n= 5;
    int mem[n+1];
    //cout<<climb(6);

    //cout<<memClimb(n, mem);

    cout<<optClimb(n);
    return 0;
}

