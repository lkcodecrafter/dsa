public class Getters_Setters {

    public static void main(String args[]){

        Pen p1 = new Pen();//created p1 as a new object

        System.out.println("Before modifying the values of the private variables");
        System.out.println(p1.getColor());
        System.out.println(p1.getTip());

        System.out.println("After modifying the value of the private variables");
        p1.setColor("black");
        p1.setTip(10);

        System.out.println(p1.getColor());
        System.out.println(p1.getTip());

    }
    
}

// this in java : used to refer to the current object
// mainly used in three scenarios
// 1. to refer to the current class instance variables
// 2. to invoke the current class method (implicitly)
// 3. to invoke the current class constructor
// here we are using this to refer to the current class instance variables
// we have made the variables private so that they cannot be accessed directly outside the class
// we are using getters and setters to access and modify the private variables
// getters are used to get the value of the private variables
// setters are used to set or modify the value of the private variables
// this is a very important concept in encapsulation in OOPs
// encapsulation is the process of wrapping the data (variables) and code (methods) together as a single unit
// in encapsulation the variables of a class will be hidden from other classes and can be accessed only through the methods of their current class
// this is also known as data hiding
// example : bank account details, password etc should not be accessible directly
// instead we use getters and setters to access and modify them
// this helps in protecting the data from unauthorized access and modification
// it also helps in maintaining the integrity of the data
// it also helps in controlling the access to the data
// we can add validation logic in the setters to control the values being set to the variables
// for example we can restrict the tip size to be within a certain range
// we can also make the getters return a copy of the variable instead of the actual variable to prevent modification
// of the variable outside the class
// overall getters and setters are very important in OOPs and encapsulation

class Pen{
   private String color = "blue";
   private int tip = 5;

    //Getters used to get value of the variables


    // this tell use the variable that we declared inside the function
    String getColor(){
        return this.color;
    }

    int getTip(){
        return this.tip;
    }

    // Setters used to modify the value

    void setColor(String newColor){

        this.color = newColor;
    }

    void setTip(int newTip){
        this.tip = newTip;
    }
}
