#include<iostream>
#include<thread>

using namespace std;

void greet(){
    cout<<"Hello"<<endl;
}

int main(){
    thread t1(greet); // What is this? This is how we create a thread in C++. 
    //We pass the function greet to the thread constructor. 
    //This will create a new thread that will execute the greet function.
    t1.join(); // do we require this? Yes, we do. This is how we wait for the thread to finish.
    // without this, the main thread will finish before the greet thread has a chance to execute, and we may not see the output "Hello".
    return 0;

}