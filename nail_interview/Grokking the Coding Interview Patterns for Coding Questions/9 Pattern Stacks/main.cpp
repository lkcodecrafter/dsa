#include<iostream>
#include<stdlib.h>
#include<stack>
using namespace std;

//# 8️⃣ Problem 5: Sorting a Stack (Easy)

void sortingStack(stack<int> &s) {
    stack<int> tempStack;

    while (!s.empty()) {
        int temp = s.top();
        s.pop();

        while (!tempStack.empty() && tempStack.top() > temp) {
            s.push(tempStack.top());
            tempStack.pop();
        }
        tempStack.push(temp);
    }

    // Transfer sorted elements back to the original stack
    while (!tempStack.empty()) {
        s.push(tempStack.top());
        tempStack.pop();
    }
}

string simplifyPath(string path){
    stack<string>st;
    string curr="";
    path+='/';
    string result;
    for(char c : path){
        if(c=='/'){

            if(curr ==".." && !st.empty()){
                st.pop();
            }else if(curr !="" && curr !="." && curr != ".."){
                st.push(curr);
            }
            curr="";

        }else{
            curr+=c;
        }
    }

    while (!st.empty())
    {
        result= "/" +st.top() + result;
        st.pop();
    }
    
    return result==""?"/": result;


}