public class Interfaces {

    public static void main(String args[]){

        System.out.println("INTERFACE");
        Queen q1 = new Queen();
        q1.moves();

        System.out.println("MULTIPLE INHERITANCE");

        Bear b1 = new Bear();

        b1.eats();

        ChessPlayer p1 = new Rook(); // When we use interface as a reference type, it is called polymorphism
        // Here, the reference type is ChessPlayer (interface) and the object type is Rook (class)
        // The method that gets called is determined at runtime based on the object type
        // This is known as dynamic method dispatch or runtime polymorphism
        // So, even though the reference type is ChessPlayer, the moves() method of Rook class will be called
        p1.moves();


    }
    
}

// Why interfaces are used?
// 1. To achieve abstraction
// 2. To achieve multiple inheritance in java
// 3. To define a contract that other classes must follow
// 4. To provide a way to implement polymorphism
// 5. To separate the definition of methods from their implementation
// 6. To allow for loose coupling between classes
// 7. To enable code reusability
// 8. To define constants that can be used across multiple classes
// 9. To provide a way to implement callbacks
// 10. To improve code organization and readability
// 11. To allow for easier testing and mocking of classes
// 12. To enable the use of default methods in interfaces (Java 8 and above)
// 13. To define functional interfaces for use with lambda expressions (Java 8 and above)
// 14. To provide a way to implement event handling mechanisms
// 15. To facilitate the implementation of design patterns such as Strategy, Observer, and Decorator

// How polymorphism is achieved using interfaces?
// Polymorphism is achieved using interfaces by allowing different classes to implement the same 
// interface and provide their own implementation of the methods defined in the interface. 
// This allows objects of different classes to be treated as objects of the same interface type, enabling method 
// calls to be resolved at runtime based on the actual object type rather than the reference type.
// This is known as dynamic method dispatch or runtime polymorphism.

// For example, in the code below, both the Queen and Rook classes implement the ChessPlayer interface and provide 
// their own implementation of the moves() method. When we call the moves() method on a ChessPlayer reference, 
// the actual method that gets executed is determined at runtime based on the object type (Queen or Rook) that the reference points to.
// This allows for flexibility and extensibility in the code, as new classes can be added that implement the same interface without changing the existing code that uses the interface.

//creating a interface
interface ChessPlayer{
    void moves();
}

//creating classes on the above interfaces

class Queen implements ChessPlayer{

    //recreating and making the function public
    public void moves(){
        System.out.println("right,left,up,down,digonal ");
    }

}

class Rook implements ChessPlayer{

    public void moves(){
        System.out.println("right,left,up,down ");
    }
}

interface Herbivore{
    void eats();
}

interface Carnivore{
    void eats();
}

// Implementing multiple inheritance using interfaces
// Which interface method gets called is determined by the class that implements the interfaces
// In this case, Bear class implements both Herbivore and Carnivore interfaces and provides its own implementation of the eats() method
// So, when we call the eats() method on a Bear object, the implementation in the Bear class is executed
// But in both interfaces, the method signature is the same, so there is no ambiguity
// How deciding which method to call when there is a conflict?
// In this case, since both interfaces have the same method signature, there is no conflict
// If the method signatures were different, we would have to provide separate implementations for each interface method in the Bear class
// If there was a conflict, we could use default methods in interfaces (Java 8 and above) to resolve it
class Bear implements Herbivore,Carnivore{
    
    public void eats(){
        System.out.println("Eats meat and grass");
    }
}
