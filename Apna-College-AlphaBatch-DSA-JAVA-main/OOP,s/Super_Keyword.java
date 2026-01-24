public class Super_Keyword {

    public static void main(String args[]){

        Ghoda g1 = new Ghoda();
        g1.color = "brown";
        System.out.println(g1.color);


    }
    
}

class Prani{
    String color = "blue";
    
    
    Prani(){
        System.out.println("Prani constructor is called");
        System.out.println(color);
        
    }
}

// Super keyword is used to refer to the parent class properties and methods
// It is also used to call the parent class constructor
// Here Ghoda is the child class and Prani is the parent class
// Ghoda class extends Prani class
// When we create an object of Ghoda class, the constructor of Prani class is called first
// Then the constructor of Ghoda class is called
// In the Ghoda class constructor, we are changing the color property of the Prani class using super.color
// Finally, we are printing the color property of the Ghoda class object
// Output:
// Prani constructor is called
// blue
// Ghoda consturctor is called
// black
// brown
// Explanation of output:
// 1. When we create an object of Ghoda class, the constructor of Prani class is called first
// 2. The color property of Prani class is printed, which is "blue"
// 3. Then the constructor of Ghoda class is called
// 4. In the Ghoda class constructor, we are changing the color property of the Prani class using super.color to "black"
// 5. The color property of Ghoda class is printed, which is now "black"
// 6. Finally, we are changing the color property of the Ghoda class object to "brown" and printing it
// 7. The final output is "brown"
// How super keyword works in inheritance is demonstrated here
// It helps to access parent class properties and methods easily
// It also helps to avoid confusion when child class has properties or methods with the same name as parent class
// How super is used to call parent class constructor
// It ensures that the parent class is properly initialized before the child class
// Example to call parent class constructor using super()
// Ghoda(){
//  super(); // calls the constructor of Prani class
// ...}
// This is not shown in this example but is an important use of super keyword
// Overall, super keyword is a powerful feature in Java that helps in managing inheritance effectively
// It enhances code readability and maintainability

class Ghoda extends Prani{
  Ghoda(){
    //this changes the properties of the previous class
    // super.color refers to the parent class property
    super.color = "black";
    System.out.println("Ghoda consturctor is called");
    System.out.println(color);
  }
}
