#include<iostream>
#include<vector>
using namespace std;

template<typename T>

T add(T a, T b){
    return a+b;
}

class template_example{
    public:
    template<typename T>
    T add(T a, T b){
        return a+b;
    }
};

// Example of a template class
// systax: template <typename T> class ClassName { /* class definition */ }; 
//template<typename T>
// class Stack{

template<typename T>
class Stack{

    private:
    vector<T> elements;
    
    public:
    void push(T value){
        elements.push_back(value);
    }
};

int main(){
    cout << add(5, 10) << endl; // Output: 15
    cout << add(3.5, 2.5) << endl; // Output: 6.0
    cout << add(string("Hello, "), string("World!")) << endl; // Output: Hello, World!

    template_example te;
    cout << te.add(5, 10) << endl; // Output: 15
    cout << te.add(3.5, 2.5) << endl; // Output: 6.0
    cout << te.add(string("Hello, "), string("World!")) << endl; // Output: Hello, World!

    cout<< "Stack of integers:" << endl;
    Stack<int> st;
    st.push(1);
    st.push(2);
    

    return 0;
}
