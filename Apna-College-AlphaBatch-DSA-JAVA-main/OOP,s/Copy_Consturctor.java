public class Copy_Consturctor {

    public static void main(String args[]){

        Student s1 = new Student();

        s1.name = "abcd";
        s1.roll = 456;
        s1.pwd = 0000;
        s1.marks[0] = 10;
        s1.marks[1] = 9;

        Student s2 = new Student(s1);

        s2.pwd = 9999;
        System.out.println("Shallow copy");
        System.out.println("before chandging the values in the s1 object ");
        System.out.println("Marks of s2 are "+s2.marks[0]+ " , " +s2.marks[1]);

        // changing the marks in s1
        
        s1.marks[0] = 6;
        s1.marks[1] = 5;

        System.out.println("After changing the values in s1");
        System.out.println("Marks of s2 are "+s2.marks[0]+" , "+s2.marks[1]);

        //marks will change as the it is done with SHALLOW COPY
        // but will not change if deep copy consturctor is used

        

    }
    
}

// What is copy consturctor?
// A copy constructor is a special type of constructor in object-oriented programming that is 
// used to create a new object as a copy of an existing object. It initializes the new object
// using the values of the attributes from the existing object.
// It is commonly used when you want to create a duplicate of an object with the same 
// state or properties.
// Copy constructors are often used in languages like C++ and Java to ensure that when an object
// is copied, the new object has its own separate copy of the data, rather than just referencing
// the same memory location as the original object.

// Shallow Copy vs Deep Copy
// Shallow Copy: In a shallow copy, a new object is created, but the fields of the object are copied
// by reference. This means that if the original object contains references to other objects, both the original
// and the copied object will refer to the same memory locations for those referenced objects. Changes made to the referenced
// objects in either the original or copied object will be reflected in both.

// Deep Copy: In a deep copy, a new object is created, and all fields of the object are copied recursively.
// This means that if the original object contains references to other objects, new copies of those referenced
// objects are also created. As a result, the original and copied objects are completely independent of each other.
// Changes made to the referenced objects in one will not affect the other. 
// Deep copy is more memory-intensive but ensures complete separation between the original and copied objects.
// In the example below both types of copy constructors are shown but the deep copy constructor is active
// and shallow copy constructor is commented out.
// You can switch between them to see the difference in behavior.

class Student{

    String name;
    int roll;
    int pwd;
    int marks[];

    //Creating a function for the copy constructor

        //function for shallow copy
    
    /*
    Student(Student s1)
    {
        marks = new int[2];
        this.name = s1.name;
        this.roll = s1.roll;
        this.marks = s1.marks;
     }
    */

    // function for deep fry

    
    Student(Student s1){
        marks = new int[2];
        this.name = s1.name;
        this.roll = s1.roll;

        // copied the array deeply
        this.marks[0] = s1.marks[0];
        this.marks[1] = s1.marks[1];
    }
    

    // this for a empty object
    Student(){
        marks = new int[2];

    }
    
}
