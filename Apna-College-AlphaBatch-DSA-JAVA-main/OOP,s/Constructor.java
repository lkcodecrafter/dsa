public class Constructor {

    public static void main(String args[]){

        Student s1 = new Student();

        Peen p1 = new Peen("blue",5);

        System.out.println(p1.color);
        



    }
    
}

// class Student{
//     String name;
//     int roll;

//     // creating constructor intentionaly

//     Student(){
//         System.out.println("You have witten this inside the Constructor");
//     }
// }


// What is a constructor? and how to use it
// A constructor is a special method that is called when an object is instantiated
// It is used to initialize the object
// It has the same name as the class and does not have a return type
// It can take parameters to initialize the object with specific values
// If no constructor is defined, a default constructor is provided by Java
// You can overload constructors to have multiple ways to initialize an object
// Example of a constructor:
// Creating a class Peen with a constructor to initialize its properties
// when an object is created
// of the class Peen with specific values for color and tip 
class Peen{
    String color;
    int tip;

    //Giving initial values using a contructor

    Peen(String newColor, int newTip){

        this.color = newColor;
        this.tip = newTip;

    }
}
