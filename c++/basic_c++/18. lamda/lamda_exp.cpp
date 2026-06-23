#include<iostream>
using namespace std;

/*

Basic syntax:

[capture](parameters) -> return_type { body }
Example:
auto add = [](int a, int b) {
   return a + b;
};


Capture clause controls how external variables are accessed.


*/


int main(){

     auto add =[](int a , int b){
        return a+b;
    };

    int x =10;
    auto val =[x](){
        return x;
    };

    int sum = add(10,20);
   cout<<"daksh "<<sum<<endl;


   auto passByref = [&x](){
    x = 20; // Modifies the original variable x in the main function
   };

   passByref();
   cout<<"x after modification: "<<x<<endl; // Output: x after modification:


//By default, value-captured variables cannot be modified. To allow modification, use mutable:

auto f = [x]() mutable { x++; };

f(); // Modifies the captured variable x within the lambda, but does not affect the original x in main
cout<<"x after mutable lambda: "<<x<<endl; // Output: x after mutable lambda: 20
 cout<<"x after mutable lambda: "<<x<<endl; // Output: x after mutable lambda: 20
 //why x is 20 and not 21? Because the lambda captures x by value, it creates a copy of x. When we call f(), it modifies the copy of x within the lambda, but the original x in main remains unchanged at 20.
// than how to modify x in main from the lambda? We can capture x by reference using [&x] instead of [x]:
// but what the use of mutable in this case? The mutable keyword allows us to modify the captured variable within the lambda, even if it is captured by value. However, in this case, since we are capturing x by reference using [&x], we do not need mutable to modify x within the lambda. 
//The mutable keyword is only necessary when we want to modify a variable that is captured by value.
// example of mutable lambda with value capture:
auto g = [x]() mutable { x++; cout<<"Inside mutable lambda with value capture: "<<x<<endl; };
g(); // Modifies the captured variable x within the lambda, but does not affect the original x in main
cout<<"x after mutable lambda with value capture: "<<x<<endl; // Output: x after mutable lambda with value capture: 20

// what is use of mutuable in this case? The mutable keyword allows us to modify the captured variable within the lambda, even if it is captured by value. In this example, we capture x by value using [x], and then we can modify the captured variable x within the lambda using mutable. However, since we are capturing x by value, the original x in main remains unchanged at 20.
// why to use mutable in this case? We use mutable in this case to allow modification of the captured variable x within the lambda, even though it is captured by value. Without mutable, we would not be able to modify x within the lambda, and any attempt to do so would result in a compilation error. By using mutable, we can modify the captured variable x within the lambda, while still keeping the original x in main unchanged.
// than how to access mutual modified x in main from the lambda? We cannot access the modified x in main from the lambda if we capture it by value, because the lambda creates a copy of x. To access the modified x in main, we need to capture it by reference using [&x] instead of [x]. This way, any modifications to x within the lambda will affect the original x in main.

// Generic lambdas were introduced in C++14 using auto parameters. Template lambdas are supported in C++20.
// In lambda c++ interview questions, mention capture types and STL integration.

return 0;
}