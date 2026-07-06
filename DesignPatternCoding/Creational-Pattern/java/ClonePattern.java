import java.util.*;

interface Enemy {
    Enemy clone();
}

class ClonePattern implements Enemy {

    String name;
    int rollNumber;

    ClonePattern(String name, int rollNumber) {
        this.name = name;
        this.rollNumber = rollNumber;
    }

    @Override
    public ClonePattern clone() {
        return new ClonePattern(this.name, this.rollNumber);
    }

    public void displayName() {
        System.out.println("Name is " + name);
    }

    public static void main(String[] arg) {
        ClonePattern clonePattern = new ClonePattern("Lalit", 10);
        clonePattern.displayName();

        ClonePattern clonePattern2 = clonePattern.clone();
        clonePattern2.name = "kumar";
        clonePattern2.displayName();
    }
}

/*
 * 
 * @Override public Prototype clone() { return new Car(this.model, this.color);
 * } like we can't do it like as @Override public Car clone() { return new
 * Car(this.model, this.color); }
 * 
 * 
 * Documents :
 * 
 * Yes, you can do that. In Java, this is called a covariant return type.
 * 
 * Suppose your interface is:
 * 
 * interface Prototype {
 * Prototype clone();
 * }
 * 
 * Your implementation can be:
 * 
 * class Car implements Prototype {
 * String model;
 * String color;
 * 
 * Car(String model, String color) {
 * this.model = model;
 * this.color = color;
 * }
 * 
 * @Override
 * public Car clone() { // Valid
 * return new Car(this.model, this.color);
 * }
 * }
 * 
 * This compiles because Car is a subtype of Prototype. Java allows an
 * overriding method to return a more specific type than the one declared in the
 * interface or superclass.
 * 
 * Why is this allowed?
 * 
 * The interface promises:
 * 
 * "I'll return some Prototype."
 * 
 * A Car is a Prototype, so returning a Car satisfies that promise.
 * 
 * Benefits
 * 
 * You don't need to cast:
 * 
 * Without a covariant return type:
 * 
 * Car original = new Car("Tesla", "Red");
 * 
 * Car copy = (Car) original.clone(); // Cast required
 * 
 * With a covariant return type:
 * 
 * Car original = new Car("Tesla", "Red");
 * 
 * Car copy = original.clone(); // No cast needed
 * 
 * This is cleaner and safer.
 * 
 * Then why do many examples return Prototype?
 * 
 * Many tutorials use:
 * 
 * @Override
 * public Prototype clone() {
 * return new Car(this.model, this.color);
 * }
 * 
 * because they want to emphasize that the object is being accessed through the
 * Prototype interface, making the example more generic.
 * 
 * In real Java code, returning the concrete type is often preferred when it
 * makes the API easier to use.
 * 
 * So both implementations are correct:
 * 
 * @Override
 * public Prototype clone() {
 * return new Car(this.model, this.color);
 * }
 * 
 * and
 * 
 * @Override
 * public Car clone() {
 * return new Car(this.model, this.color);
 * }
 * 
 * 
 */