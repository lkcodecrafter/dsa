
import java.util.*;

/*
 * 
 * Memento Pattern - It's to store the previous state of an object and restore
 * it when needed.
 * It's like a undo functionality
 * 
 * Steps
 * 1. Create a Memento class which will store the state of the object
 * 2. Create a Originator class which will create the Memento object and restore
 * the state from the Memento object
 * 3. Create a Caretaker class which will store the Memento objects and restore
 * the state from the Memento object
 * 
 */

class Memento {

    private final String state;

    Memento(String state) {
        this.state = state;
    }

    public String getState() {
        return state;
    }
}

class Originator {

    private String text;

    Originator() {
    }

    Originator(String text) {
        this.text = text;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    Memento save() {
        return new Memento(text);
    }

    public void restore(Memento m) {
        text = m.getState();
    }

    public void show() {
        System.out.println(text);
    }

}

class Caretaker {
    Stack<Memento> history = new Stack<>();

    public void save(Memento m) {
        history.push(m);
    }

    public Memento undo() {
        if (history != null && !history.isEmpty()) {
            return history.pop();
        }
        return null;
    }

}

class MementoPattern {
    public static void main(String[] args) {
        Originator org = new Originator();
        Caretaker caretaker = new Caretaker();
        org.setText("hello");
        caretaker.save(org.save());

        org.setText("world");
        caretaker.save(org.save());
        org.setText("Hello World!!");
        org.show();

        org.restore(caretaker.undo());
        org.show();
        org.restore(caretaker.undo());
        org.show();

    }
}
