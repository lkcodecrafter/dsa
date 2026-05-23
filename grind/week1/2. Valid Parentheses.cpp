#include<iostream>
using namespace std;


class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {

                st.push(c);

            } else {

                if (st.empty())
                    return false;

                char cc = st.top();
                if ((cc == '{' && c == '}') || (cc == '[' && c == ']') ||
                    (cc == '(' && c == ')')) {
                    st.pop();
                } else {
                    st.push(c);
                }
            }
        }

        return st.empty();
    }
};