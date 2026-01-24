public class Inheritance {

    public static void main(String args[]) {

        Fish shark = new Fish();

        // inherited properties
        shark.skinColor = "blue";
        shark.eat();

        // self properties
        shark.fins = 5;

        Mamals whale = new Mamals();

        whale.skinColor = "black";
        whale.eat();
        whale.fins = 0;
        whale.milk = 100;
        whale.size = "big";

    }
}

// main class or parent class
// What is inheritance?
// Inheritance is a mechanism in object-oriented programming that allows a new class (called a derived class or child class) to inherit properties and behaviors (attributes and methods) from an existing class (
// called a base class or parent class). This promotes code reusability and establishes a hierarchical relationship between classes.
// Types of Inheritance:
// Single Inheritance: A derived class inherits from a single base class.
// Multilevel Inheritance: A derived class inherits from a base class, and then another class inherits from that derived class.
// Hierarchical Inheritance: Multiple derived classes inherit from a single base class.
// Hybrid Inheritance: A combination of two or more types of inheritance.
// In this example, we will demonstrate Single Inheritance and Multilevel Inheritance.
// Base class or parent class
// superclass 
// base class
// parent class
// derived class
// child class
// subclass
// inherited class
// single inherited class
// double inherited class
// multilevel inherited class
// hybrid inherited class
// hierarchical inherited class
// multiple inherited class

class Animals {

    String skinColor;

    void eat() {
        System.out.println("Eats");
    }

    void breath() {
        System.out.println("Breath");
    }
}

// derived class or child class

// Single inherited class

class Fish extends Animals {

    int fins;

    void swim() {
        System.out.println("Swims");
    }
}

// Double inherited class
class Mamals extends Fish {

    int milk;

    String size;

}