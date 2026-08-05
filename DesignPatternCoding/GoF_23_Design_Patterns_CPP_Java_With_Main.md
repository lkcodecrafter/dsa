
# 🚀 Complete GoF Design Patterns – C++ & Java
### All 23 Patterns • Runnable `main()` • Simple Learning Code

This README is designed so you can **copy–paste–run** each pattern.
Code is **minimal**, **clear**, and **interview‑friendly**.

---
## 🧠 How to Study
1. Read **Intent**
2. Run **C++ main**
3. Run **Java main**
4. Modify behavior → see effect

---

# 🟢 CREATIONAL PATTERNS (5)

## 1. Singleton
**Intent:** Only one instance.

### C++
```cpp
#include <iostream>
using namespace std;

class Singleton {
    static Singleton* instance; // Declaration (tells the compiler it exists)
    Singleton() {} // is it private? yes. but not defined private keyword?  why? 
    // in java it is private. in cpp we can skip private keyword. 
    // if i remove private keyword in cpp, it will still be private. 
    // this is because in cpp, the default access specifier for class members is private. 
    // if i define constructor as private, then it will be private. 
    // but if i don't define private keyword, then it will still be private. 
public:
    static Singleton* getInstance() {
        if(!instance) instance = new Singleton(); // Equivalent to: if (instance == nullptr)
        // Created ONLY the first time
        return instance;
    }
    void show() { cout << "Singleton\n"; }
};
Singleton* Singleton::instance = nullptr; // Definition (allocates memory and initializes it)

int main() {
    Singleton::getInstance()->show();
}
```

### Java
```java
class Singleton {
    private static Singleton instance;
    private Singleton() {}
    static Singleton getInstance() {
        if(instance == null) instance = new Singleton();
        return instance;
    }
    void show() { System.out.println("Singleton"); }

    public static void main(String[] args) {
        Singleton.getInstance().show();
    }
}
```

---

## 2. Factory Method
**Intent:** Create objects without exposing logic.

### C++
```cpp
#include <iostream>
using namespace std;

class Shape {
    // abstract base class
    public: 
        virtual void draw()=0; // pure virtual functio  n
};
class Circle : public Shape {
public: 
    void draw(){ cout<<"Circle\n"; }
};

int main(){
    Shape* s = new Circle(); // why Shape*? not Circle*? Explain this 
    // because Circle is derived from Shape. so we can point to the Shape part of the Circle object. 
    // but if we point to the Circle part of the Shape object, then we cannot access the virtual functions.  // is it true? yes 
    s->draw(); // why ->? not .? Explain this 
    // because s is a pointer. so we use -> to access the member functions. if s was not a pointer, then we would use . to access the member functions.
}
```

### Java
```java
interface Shape { void draw(); }
class Circle implements Shape {
    public void draw(){ System.out.println("Circle"); }
}
public class Main {
    public static void main(String[] args){
        Shape s = new Circle();
        s.draw();
    }
}

// Output
// Circle
```

---

## 3. Abstract Factory
**Intent:** Create families of objects.

How we are creating families of objects? 

### C++
```cpp
#include <iostream>
using namespace std;

class Button { public: virtual void paint()=0; };
class WinButton : public Button {
public: void paint(){ cout<<"Windows Button\n"; }
};

int main(){
    Button* b = new WinButton();
    b->paint();
}
```

### Java
```java
interface Button { void paint(); }
class WinButton implements Button {
    public void paint(){ System.out.println("Windows Button"); }
}
public class Main {
    public static void main(String[] args){
        Button b = new WinButton();
        b.paint();
    }
}
```

---

## 4. Builder
**Intent:** Build complex object step by step.

### C++
```cpp
#include <iostream>
using namespace std;

class House {
public:
    string walls, roof;
};

int main(){
    House h;
    h.walls="Brick";
    h.roof="Concrete";
    cout<<h.walls<<" "<<h.roof<<endl;
}

// One more example - 

#include <iostream>
#include <string>

class GamingPC {
private:
    // const members make the object immutable after creation (like Java's 'final')
    const std::string cpu;
    const std::string ram;
    const std::string graphicsCard;
    const bool hasRgb;

public:
    // Forward declare the Builder class so GamingPC knows it exists
    class Builder;

private:
    // Private constructor: accepts a Builder reference and uses an initializer list
    GamingPC(const Builder& builder);

public:
    void showSpecs() const {
        std::cout << "PC Specs -> CPU: " << cpu 
                  << " | RAM: " << ram 
                  << " | GPU: " << graphicsCard 
                  << " | RGB: " << (hasRgb ? "true" : "false") << std::endl;
    }

    // Nested Builder Class
    class Builder {
    private:
        std::string cpu;
        std::string ram;
        std::string graphicsCard = "Integrated Graphics"; // Default value
        bool hasRgb = false;                              // Default value

        // Allow GamingPC private constructor to read these private fields
        friend class GamingPC;

    public:
        // Constructor forces user to provide mandatory fields
        Builder(const std::string& cpu, const std::string& ram) 
            : cpu(cpu), ram(ram) {}

        // Methods return a reference to 'this' to allow fluent method chaining
        Builder& addGraphicsCard(const std::string& graphicsCard) {
            this->graphicsCard = graphicsCard;
            return *this;
        }

        Builder& addRgb(bool hasRgb) {
            this->hasRgb = hasRgb;
            return *this;
        }

        // The final method that creates the actual GamingPC object
        GamingPC build() const {
            return GamingPC(*this);
        }
    };
};

// Definition of GamingPC constructor (must be defined after Builder class is fully declared)
GamingPC::GamingPC(const GamingPC::Builder& builder)
    : cpu(builder.cpu), 
      ram(builder.ram), 
      graphicsCard(builder.graphicsCard), 
      hasRgb(builder.hasRgb) {}


// Client Code / Main Function
int main() {
    // Build a high-end PC
    GamingPC highEndPc = GamingPC::Builder("AMD Ryzen 9", "64GB")
                            .addGraphicsCard("RTX 4080")
                            .addRgb(true)
                            .build();

    // Build a budget office PC using default values
    GamingPC officePc = GamingPC::Builder("Intel i3", "8GB")
                            .build();

    highEndPc.showSpecs();
    officePc.showSpecs();

    return 0;
}



```

### Java
```java
class House {
    String walls, roof;
}
public class Main {
    public static void main(String[] args){
        House h = new House();
        h.walls="Brick"; h.roof="Concrete";
        System.out.println(h.walls+" "+h.roof);
    }
}

// One more Exaple 

class GamingPC {
    // All fields are final (immutable after creation)
    private final String cpu;
    private final String ram;
    private final String graphicsCard;
    private final boolean hasRgb;

    // The main constructor is private; only the Builder can call it
    private GamingPC(Builder builder) {
        this.cpu = builder.cpu;
        this.ram = builder.ram;
        this.graphicsCard = builder.graphicsCard;
        this.hasRgb = builder.hasRgb;
    }

    public void showSpecs() {
        System.out.println("PC Specs -> CPU: " + cpu + " | RAM: " + ram + 
                           " | GPU: " + graphicsCard + " | RGB: " + hasRgb);
    }

    // Static Inner Builder Class
    public static class Builder {
        private String cpu;         // Required
        private String ram;         // Required
        private String graphicsCard = "Integrated Graphics"; // Default value
        private boolean hasRgb = false;                     // Default value

        // Constructor forces user to provide mandatory fields
        public Builder(String cpu, String ram) {
            this.cpu = cpu;
            this.ram = ram;
        }

        // Methods return 'this' (the builder instance) to allow method chaining
        public Builder addGraphicsCard(String graphicsCard) {
            this.graphicsCard = graphicsCard;
            return this; 
        }

        public Builder addRgb(boolean hasRgb) {
            this.hasRgb = hasRgb;
            return this;
        }

        // The final method that creates the actual GamingPC object
        public GamingPC build() {
            return new GamingPC(this);
        }
    }
}

// Client Code / Main Method
public class Main {
    public static void main(String[] args) {
        // Build a high-end PC
        GamingPC highEndPc = new GamingPC.Builder("AMD Ryzen 9", "64GB")
                .addGraphicsCard("RTX 4080")
                .addRgb(true)
                .build();

        // Build a budget office PC using default values
        GamingPC officePc = new GamingPC.Builder("Intel i3", "8GB")
                .build();

        highEndPc.showSpecs();
        officePc.showSpecs();
    }
}

```

---

## 5. Prototype
**Intent:** Clone existing object.

### C++
```cpp
#include <iostream>
using namespace std;

class Prototype {
public:
    int x;
    Prototype(int x):x(x){}
    Prototype* clone(){ return new Prototype(*this); }
};

int main(){
    Prototype p1(10);
    Prototype* p2 = p1.clone();
    cout<<p2->x<<endl;
}
```

### Java
```java
class Prototype implements Cloneable {
    int x;
    Prototype(int x){ this.x=x; }
    Prototype cloneObj(){ return new Prototype(x); }

    public static void main(String[] args){
        Prototype p1 = new Prototype(10);
        Prototype p2 = p1.cloneObj();
        System.out.println(p2.x);
    }
}
```

---
# 🧱 STRUCTURAL PATTERNS (7) // Strucutre patter is using composition of objects. 

## 6. Adapter
**Intent:** Convert one interface to another.  converting one interface into another so they can work together without changing either original device.

### C++
```cpp
#include <iostream>
using namespace std;

class Old {
public: void oldReq(){ cout<<"Old Request\n"; }
};
class Adapter {
    Old* o;
public:
    Adapter(Old* o):o(o){}
    void request(){ o->oldReq(); }
};

int main(){
    Old o;
    Adapter a(&o);
    a.request();
}
```

### Java
```java
class Old {
    void oldReq(){ System.out.println("Old Request"); }
}
class Adapter {
    Old o;
    Adapter(Old o){ this.o=o; }
    void request(){ o.oldReq(); }
}
public class Main {
    public static void main(String[] args){
        new Adapter(new Old()).request();
    }
}

// Output 
// Old Request
// Why to us this pattern?
// Scenario:
// You have an old system (Old) that works fine. Now, you want to integrate it with a new system (New) that expects a different interface. Instead of rewriting the old system, you create an Adapter to translate calls between the two.
// But we can modify old system to match the new interface.
// Use case: Use when you want to use existing class (with incompatible interface) in your project.

// Adapter Design Pattern in Real World:
// Imagine you have an Android app and you want to integrate a payment SDK from a company that provides it only for iOS. You can't change the SDK code. So, you write an Adapter class that implements the iOS interface but uses the Android SDK internally to make the payment. This way, your app works seamlessly with the SDK.




```

---

## 7. Bridge
**Intent:** Separate abstraction from implementation.

### C++
```cpp
#include <iostream>
using namespace std;

class Color { public: virtual void apply()=0; };
class Red : public Color {
public: void apply(){ cout<<"Red\n"; }
};

int main(){
    Color* c = new Red();
    c->apply();
}
```

### Java
```java
interface Color { void apply(); }
class Red implements Color {
    public void apply(){ System.out.println("Red"); }
}
public class Main {
    public static void main(String[] args){
        Color c = new Red();
        c.apply();
    }
}
```

---

## 8. Composite
**Intent:** Tree structure.

### C++
```cpp
#include <iostream>
using namespace std;

class Component {
public: virtual void show()=0;
};
class Leaf : public Component {
public: void show(){ cout<<"Leaf\n"; }
};

int main(){
    Component* c = new Leaf();
    c->show();
}
```

### Java
```java
interface Component { void show(); }
class Leaf implements Component {
    public void show(){ System.out.println("Leaf"); }
}
public class Main {
    public static void main(String[] args){
        Component c = new Leaf();
        c.show();
    }
}
```

---

## 9. Decorator
**Intent:** Add behavior dynamically.

### C++
```cpp
#include <iostream>
using namespace std;

class Coffee {
public: virtual int cost()=0;
};
class SimpleCoffee : public Coffee {
public: int cost(){ return 10; }
};

int main(){
    Coffee* c = new SimpleCoffee();
    cout<<c->cost()<<endl;
}
```

### Java
```java
interface Coffee { int cost(); }
class SimpleCoffee implements Coffee {
    public int cost(){ return 10; }
}
public class Main {
    public static void main(String[] args){
        Coffee c = new SimpleCoffee();
        System.out.println(c.cost());
    }
}
```

---

## 10. Facade
**Intent:** Simplified interface.

### C++
```cpp
#include <iostream>
using namespace std;

class SystemA {
public: void run(){ cout<<"SystemA\n"; }
};
class Facade {
    SystemA a;
public: void start(){ a.run(); }
};

int main(){
    Facade f;
    f.start();
}
```

### Java
```java
class SystemA {
    void run(){ System.out.println("SystemA"); }
}
class Facade {
    SystemA a = new SystemA();
    void start(){ a.run(); }
}
public class Main {
    public static void main(String[] args){
        new Facade().start();
    }
}
```

---

## 11. Flyweight
**Intent:** Reuse objects.

### C++
```cpp
#include <iostream>
using namespace std;

class Flyweight {
public: void draw(){ cout<<"Draw\n"; }
};

int main(){
    Flyweight f;
    f.draw();
}
```

### Java
```java
class Flyweight {
    void draw(){ System.out.println("Draw"); }
    public static void main(String[] args){
        new Flyweight().draw();
    }
}
```

---

## 12. Proxy
**Intent:** Control access.

### C++
```cpp
#include <iostream>
using namespace std;

class Image {
public: virtual void display()=0;
};
class RealImage : public Image {
public: void display(){ cout<<"Real Image\n"; }
};
class Proxy : public Image {
    RealImage r;
public: void display(){ r.display(); }
};

int main(){
    Proxy p;
    p.display();
}
```

### Java
```java
interface Image { void display(); }
class RealImage implements Image {
    public void display(){ System.out.println("Real Image"); }
}
class Proxy implements Image {
    RealImage r = new RealImage();
    public void display(){ r.display(); }
}
public class Main {
    public static void main(String[] args){
        new Proxy().display();
    }
}
```

---
# 🔁 BEHAVIORAL PATTERNS (11)

## 13. Chain of Responsibility
**Intent:** Pass request along chain.

### C++
```cpp
#include <iostream>
using namespace std;

class Handler {
public:
    virtual void handle()=0;
};

class Concrete : public Handler {
public: void handle(){ cout<<"Handled\n"; }
};

int main(){
    Handler* h = new Concrete();
    h->handle();
}
```

### Java
```java
interface Handler { void handle(); }
class Concrete implements Handler {
    public void handle(){ System.out.println("Handled"); }
}
public class Main {
    public static void main(String[] args){
        new Concrete().handle();
    }
}
```

---

## 14. Command
**Intent:** Encapsulate request.

### C++
```cpp
#include <iostream>
using namespace std;

class Command {
public: virtual void execute()=0;
};
class Concrete : public Command {
public: void execute(){ cout<<"Executed\n"; }
};

int main(){
    Command* c = new Concrete();
    c->execute();
}
```

### Java
```java
interface Command { void execute(); }
class Concrete implements Command {
    public void execute(){ System.out.println("Executed"); }
}
public class Main {
    public static void main(String[] args){
        new Concrete().execute();
    }
}
```

---

## 15. Iterator
**Intent:** Traverse collection.

### C++
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v={1,2,3};
    for(int x:v) cout<<x<<" ";
}
```

### Java
```java
import java.util.*;
public class Main {
    public static void main(String[] args){
        List<Integer> l=Arrays.asList(1,2,3);
        for(int x:l) System.out.print(x+" ");
    }
}
```

---

## 16. Mediator
**Intent:** Central communication.

### C++
```cpp
#include <iostream>
using namespace std;

class Mediator {
public: void notify(){ cout<<"Notified\n"; }
};

int main(){
    Mediator m;
    m.notify();
}
```

### Java
```java
class Mediator {
    void notifyMsg(){ System.out.println("Notified"); }
    public static void main(String[] args){
        new Mediator().notifyMsg();
    }
}
```

---

## 17. Memento
**Intent:** Save state.

### C++
```cpp
#include <iostream>
using namespace std;

class Memento {
public: 
    int state;
    Memento(int s):state(s){}
};

int main(){
    Memento m(10);
    cout<<m.state<<endl;
}
```

### Java
```java
class Memento {
    int state;
    Memento(int s){ state=s; }
    public static void main(String[] args){
        System.out.println(new Memento(10).state);
    }
}
```

---

## 18. Observer
**Intent:** Notify observers.

### C++
```cpp
#include <iostream>
using namespace std;

class Observer {
public: void update(){ cout<<"Updated\n"; }
};

int main(){
    Observer o;
    o.update();
}
```

### Java
```java
class Observer {
    void update(){ System.out.println("Updated"); }
    public static void main(String[] args){
        new Observer().update();
    }
}
```

---

## 19. State
**Intent:** Change behavior with state.

### C++
```cpp
#include <iostream>
using namespace std;

class State {
public: virtual void handle()=0;
};
class On : public State {
public: void handle(){ cout<<"ON\n"; }
};

int main(){
    State* s = new On();
    s->handle();
}
```

### Java
```java
interface State { void handle(); }
class On implements State {
    public void handle(){ System.out.println("ON"); }
}
public class Main {
    public static void main(String[] args){
        new On().handle();
    }
}
```

---

## 20. Strategy
**Intent:** Change algorithm.

### C++
```cpp
#include <iostream>
using namespace std;

class Strategy {
public: virtual int op(int a,int b)=0;
};
class Add : public Strategy {
public: int op(int a,int b){ return a+b; }
};

int main(){
    Strategy* s = new Add();
    cout<<s->op(2,3)<<endl;
}
```

### Java
```java
interface Strategy { int op(int a,int b); }
class Add implements Strategy {
    public int op(int a,int b){ return a+b; }
}
public class Main {
    public static void main(String[] args){
        System.out.println(new Add().op(2,3));
    }
}
```

---

## 21. Template Method
**Intent:** Algorithm skeleton.

### C++
```cpp
#include <iostream>
using namespace std;

class Game {
public:
    void play(){ start(); end(); }
    virtual void start()=0;
    virtual void end()=0;
};
class Chess : public Game {
public: void start(){ cout<<"Start\n"; }
        void end(){ cout<<"End\n"; }
};

int main(){
    Chess c;
    c.play();
}
```

### Java
```java
abstract class Game {
    void play(){ start(); end(); }
    abstract void start();
    abstract void end();
}
class Chess extends Game {
    void start(){ System.out.println("Start"); }
    void end(){ System.out.println("End"); }
}
public class Main {
    public static void main(String[] args){
        new Chess().play();
    }
}
```

---

## 22. Visitor
**Intent:** Separate operation.

### C++
```cpp
#include <iostream>
using namespace std;

class Visitor {
public: void visit(){ cout<<"Visited\n"; }
};

int main(){
    Visitor v;
    v.visit();
}
```

### Java
```java
class Visitor {
    void visit(){ System.out.println("Visited"); }
    public static void main(String[] args){
        new Visitor().visit();
    }
}
```

---

## 23. Interpreter
**Intent:** Interpret language grammar.

### C++
```cpp
#include <iostream>
using namespace std;

class Expression {
public: virtual int interpret()=0;
};
class Number : public Expression {
    int v;
public: Number(int v):v(v){}
    int interpret(){ return v; }
};

int main(){
    Expression* e = new Number(5);
    cout<<e->interpret()<<endl;
}
```

### Java
```java
interface Expression { int interpret(); }
class Number implements Expression {
    int v;
    Number(int v){ this.v=v; }
    public int interpret(){ return v; }

    public static void main(String[] args){
        System.out.println(new Number(5).interpret());
    }
}
```

---

# 🎯 You now have ALL 23 GoF patterns
### ✔ Runnable
### ✔ Interview‑ready
### ✔ C++ & Java

Happy learning 🚀  
— Made for **Lalit Kumar**
