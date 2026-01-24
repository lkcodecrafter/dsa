#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        vector<int> st;
        for(auto token : tokens){
            if(token == "+" || token == "-" || token == "*" || token == "/"){
                int b = st.back(); st.pop_back(); // st.back() gives the last element example : if st = [2,3,4]
                // then st.back() = 4
                // than again st.pop_back() will remove the last element from stack
                // so after st.pop_back() st = [2,3]
                // similarly
                // a = st.back(); st.pop_back(); will give a = 3 and st = [2]
                int a = st.back(); st.pop_back();
                if(token == "+"){
                    st.push_back(a + b); // push the result of a+b to stack result is 2+3 = 5
                } else if(token == "-"){
                    st.push_back(a - b);
                } else if(token == "*"){
                    st.push_back(a * b);
                } else if(token == "/"){
                    st.push_back(a / b);
                }
            } else {
                st.push_back(stoi(token)); // convert string to integer and push to stack 
                // example : token = "123" then stoi(token) = 123
                // One more example : token = "-45" then stoi(token) = -45
            }
        }
        return st.back(); // return the last element in stack which is the result
    }
};