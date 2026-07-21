import java.util.*;

/*
#12 Proxy Pattern
Intent (Definition)

Proxy doesn't change what an object does—it controls when, how, or whether you can access it.

Provide a placeholder (proxy) for another object to control access to it.

Instead of directly accessing the real object, the client talks to the Proxy, 
and the Proxy decides whether or how to forward the request.


Key Components
Subject
: Interface implemented by both Real Subject and Proxy.

RealSubject
: The actual object that does the heavy lifting.

Proxy
: Contains a reference to the RealSubject and implements the same interface.

*/

interface Image {
    void display();
}

class RealImage implements Image {

    private String fileName;

    public RealImage(String fileName) {
        this.fileName = fileName;
        loadFromDisk();
    }

    private void loadFromDisk() {
        System.out.println("Loading image: " + fileName);
    }

    @Override
    public void display() {
        System.out.println("Displaying image: " + fileName);
    }
}

class ProxyImage implements Image {

    private RealImage realImage;
    private final String fileName;

    public ProxyImage(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public void display() {
        if (realImage == null) {
            realImage = new RealImage(fileName);
        }
        realImage.display();
    }
}

public class Main {
    public static void main(String[] args) {

        Image image = new ProxyImage("Vacation.jpg");

        System.out.println("Proxy object created.");

        System.out.println("\nFirst display:");
        image.display();

        System.out.println("\nSecond display:");
        image.display();
    }
}