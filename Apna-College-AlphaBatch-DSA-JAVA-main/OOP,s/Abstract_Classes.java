public class Abstract_Classes {

    public static void main(String args[]) {

        Horse h1 = new Horse();
        System.out.println(h1.color);
        h1.walk();
        h1.eat();

        System.out.println();

        Hen p1 = new Hen();

        p1.changeColor();
        System.out.println(p1.color);
        p1.eat();
        p1.walk();

        System.out.println();
        Animal a = new Hen();
        a.walk();
        a.color = "yellow";
        // why a is not able to access eat method?
        // because reference type decides what members can be accessed
        // and object type decides which implementation will be used
        // here reference type is Animal so only those members of Animal class can be accessed
        // but the object type is Hen so the implementation of walk method of Hen class will be used
        // a.eat(); // this will give error
        // but we can access color property because it is present in Animal class
        // and reference type is Animal
        // how to access eat method then?
        // we can type cast the reference type to Hen
        ((Hen)a).eat();
        System.out.println(a.color);
    }

}

// Abstract class is a class which is declared with abstract keyword
// it can have abstract methods as well as concrete methods
// abstract method is a method which is declared without any implementation
// it is compulsory for the subclass to implement the abstract method
// When to use abstract class?
// 1. When we want to provide a common interface for all the subclasses
// 2. When we want to provide some common functionality to all the subclasses
// 3. When we want to achieve abstraction
// How to declare an abstract class?
// 1. Use the abstract keyword before the class keyword
// 2. Use the abstract keyword before the method keyword to declare an abstract method
abstract class Animal {

    String color;

    //this property will be common in all classes
    Animal() {
        color = "brown";
    }

    abstract void walk();
}

class Horse extends Animal{

    //now it is compulsory to use walk function

    void eat(){
        System.out.println("Eats grass");
    }

    void walk(){
        System.out.println("Walks on four legs");
    }

    void maincolor(){
        color = "black";
    }

       
}

class Hen extends Animal{



    void eat(){
        System.out.println("Eats insects");
    }

    void walk(){

        System.out.println("Walks on 2 legs");
        
    }

    void changeColor(){
        color = "blue";
    }
}


