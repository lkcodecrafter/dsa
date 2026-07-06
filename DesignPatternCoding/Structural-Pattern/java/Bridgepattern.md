```java 
The Bridge Pattern is one of the most confusing design patterns at first because it looks similar to the Adapter pattern. The key difference is:

Adapter → Makes existing incompatible classes work together.
Bridge → Separates an abstraction from its implementation so they can evolve independently.
Why do we need Bridge?

Imagine you're building a notification system.

Initially, you support two notification types:

Email
SMS

You write:

EmailNotification
SMSNotification

Later, the business says notifications can be sent using different providers:

Twilio
AWS SNS

Now your classes become:

EmailTwilio
EmailAWS

SMSTwilio
SMSAWS

Later, add Push Notifications:

EmailTwilio
EmailAWS

SMSTwilio
SMSAWS

PushTwilio
PushAWS

Now suppose another provider is added:

EmailTwilio
EmailAWS
EmailFirebase

SMSTwilio
SMSAWS
SMSFirebase

PushTwilio
PushAWS
PushFirebase

The number of classes grows rapidly.

This is called a class explosion.

Bridge Solution

Instead of combining everything into one class, separate the two independent dimensions.
```

```java 

Abstraction

"What type of notification is it?"

abstract class Notification {
    MessageSender sender;

    Notification(MessageSender sender) {
        this.sender = sender;
    }

    abstract void send(String message);
}
Implementation

"Who actually sends it?"

interface MessageSender {
    void sendMessage(String message);
}
Concrete Implementations
class TwilioSender implements MessageSender {

    @Override
    public void sendMessage(String message) {
        System.out.println("Sending via Twilio: " + message);
    }
}
class AWSSender implements MessageSender {

    @Override
    public void sendMessage(String message) {
        System.out.println("Sending via AWS: " + message);
    }
}
Refined Abstraction
class EmailNotification extends Notification {

    EmailNotification(MessageSender sender) {
        super(sender);
    }

    @Override
    void send(String message) {
        System.out.print("Email -> ");
        sender.sendMessage(message);
    }
}

Another notification type:

class SMSNotification extends Notification {

    SMSNotification(MessageSender sender) {
        super(sender);
    }

    @Override
    void send(String message) {
        System.out.print("SMS -> ");
        sender.sendMessage(message);
    }
}
Client
public class Main {

    public static void main(String[] args) {

        Notification email =
                new EmailNotification(new TwilioSender());

        Notification sms =
                new SMSNotification(new AWSSender());

        email.send("Hello");

        sms.send("Hi");
    }
}

Output:

Email -> Sending via Twilio: Hello
SMS -> Sending via AWS: Hi
What's happening?

Instead of inheritance:

EmailTwilio
EmailAWS
SMSTwilio
SMSAWS

You now have:

Notification
      |
      +------ EmailNotification
      |
      +------ SMSNotification


MessageSender
      |
      +------ TwilioSender
      |
      +------ AWSSender

And you combine them at runtime:

EmailNotification + TwilioSender

SMSNotification + AWSSender

EmailNotification + AWSSender

SMSNotification + TwilioSender

No extra classes are needed for each combination.

Real-world analogy

Think of a TV and a remote control.

TV = Abstraction
Remote = Implementation

Different TVs:

Sony TV
Samsung TV

Different remotes:

Basic Remote
Smart Remote

You don't create:

SonyBasicRemote
SonySmartRemote
SamsungBasicRemote
SamsungSmartRemote

Instead:

TV <------ Remote

Any remote can work with any TV (assuming compatibility).

This is the Bridge pattern.

Adapter vs Bridge
Adapter	Bridge
Used after classes already exist	Designed before or during system design
Makes incompatible interfaces work together	Separates abstraction from implementation
Focuses on compatibility	Focuses on flexibility and avoiding class explosion
Usually wraps one existing class	Connects two independent class hierarchies
Prototype vs Adapter vs Bridge
Pattern	Purpose
Prototype	Create objects by cloning existing ones
Adapter	Make incompatible classes work together
Bridge	Separate abstraction and implementation so both can vary independently
One-line definition

The Bridge Pattern separates what an object does (abstraction) from how it does it (implementation), allowing both to change independently without creating a large number of subclasses.