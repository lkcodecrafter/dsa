#include<iostream>
#include<vector>
using namespace std;

class MinStack {
public:
    
    vector<int>stack;
    MinStack() {
    
    }
    
    void push(int val) {
        stack.push_back(val);
    }
    
    void pop() {
        stack.pop_back();
    }
    
    int top() {
        return stack.back();
    }
    
    int getMin() {
        
        int minVal = stack[0];
        for(int i=1;i<stack.size();i++){
            if(stack[i]<minVal){
                minVal = stack[i];
            }
        }
        return minVal;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */