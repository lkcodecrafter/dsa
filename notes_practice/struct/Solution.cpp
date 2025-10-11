#include <iostream>
using namespace std;

//Below we declare struct
struct Rectangle{
    int height;
    int weight;
};

//Declare with Student info
struct Student{
    string name;
    int roll[26];
    char dep[20];
};

int main(){

    //Declaration of struct
    struct Rectangle rec;
    rec.height=10;
    rec.weight=20;

    cout<<rec.height<<endl; // access

    struct Rectangle x={5,6};  // defined
    cout<<x.height << " "<<x.weight;


    struct Student st;
    st.name ="Lalit";
    st.roll[0] = 133;
    st.dep[0] = 'CS';

    cout<<endl;
    cout<<"Name : "<<st.name<< " Roll no : " <<st.roll[0] << " dep no :" <<st.dep[0];
    return 0;
}