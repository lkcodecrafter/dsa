import java.util.*;

/* MediatorPattern.java
Mediator Pattern in Java – Step-by-Step Guide
Mediator Pattern: Example and Implementation

// Mediator Pattern: Overview
The Mediator pattern is a behavioral design pattern that defines an object that encapsulates how a set of objects interact.

Mediator and OOP
In Object-Oriented Programming (OOP), it is sometimes challenging to manage the relationships between multiple objects. When many objects interact directly with one another, the relationships can become complicated and hard to maintain.

The Mediator pattern simplifies this by introducing a mediator object that acts as a central point of communication for all objects.

Real-World Examples
The Mediator pattern is used in many real-world scenarios, such as:

Airport Control Tower: A control tower acts as a mediator between aircraft, managing takeoffs and landings.

Chat Rooms: A chat room server acts as a mediator between users, relaying messages to all participants.

Traffic Control: Traffic lights and control systems coordinate vehicle movement through intersections.
*/

// Mediator Interface
abstract class IMediator {
  abstract void sendMessage(String message, User user);
}

// User Class
class User {
  private String name;
  private IMediator mediator;

  public User(String name, IMediator mediator) {
    this.name = name;
    this.mediator = mediator;
  }

  public String getName() {
    return name;
  }

  public void send(String message) {
    mediator.sendMessage(message, this); // why this used here ??
    // ans :
    // here this is used to refer to the current object
    // that is, the object that is sending the message

  }

  public void receive(String message, String senderName) {
    System.out.println(name + " received: " + message + " from " + senderName);
  }
}

// Concrete Mediator
class ChatRoom extends IMediator {
  private List<User> users = new ArrayList<>();

  public void addUser(User user) {
    users.add(user);
  }

  @Override
  void sendMessage(String message, User user) {
    for (User u : users) {
      // Don't send message to self
      if (u != user) {
        u.receive(message, user.getName());
      }
    }
  }
}

// Mediator Design Pattern
class MediatorPattern {
  public static void main(String[] args) {
    ChatRoom room = new ChatRoom();

    User user1 = new User("Alice", room);
    User user2 = new User("Bob", room);
    User user3 = new User("Charlie", room);

    room.addUser(user1);
    room.addUser(user2);
    room.addUser(user3);

    user1.send("Hello everyone!");
    user2.send("Hi Alice!");
  }
}
