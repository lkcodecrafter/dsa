
# 📘 Design Patterns in C++ – Complete Guide with Examples

This README is a **complete learning + practice guide** for **Design Patterns**, written in **simple C++**, with **clear explanations** and **easy-to-remember structure**.

---

## 1️⃣ What are Design Patterns?
Design Patterns are **reusable solutions** to common software design problems.
They are **not code**, but **proven ways to structure code**.

### Why use them?
- Cleaner code
- Loose coupling
- Easy maintenance
- Interview favorite ⭐

---

## 2️⃣ Classification of Design Patterns
| Category | Purpose |
|-------|--------|
| Creational | Object creation |
| Structural | Object composition |
| Behavioral | Object interaction |

---

# 🧩 CREATIONAL PATTERNS

## 1. Singleton Pattern
👉 Ensures **only one object** exists.

### Use Case
- Logger
- Configuration manager

```cpp
class Singleton {
private:
    static Singleton* instance;
    Singleton() {}

public:
    static Singleton* getInstance() {
        if (!instance)
            instance = new Singleton();
        return instance;
    }
};
Singleton* Singleton::instance = nullptr;
```

---

## 2. Factory Method Pattern
👉 Creates objects **without exposing creation logic**.

```cpp
class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() { cout << "Circle\n"; }
};

class ShapeFactory {
public:
    static Shape* createShape() {
        return new Circle();
    }
};
```

---

## 3. Abstract Factory Pattern
👉 Factory of factories

```cpp
class Button {
public:
    virtual void paint() = 0;
};

class WinButton : public Button {
public:
    void paint() { cout << "Windows Button\n"; }
};

class GUIFactory {
public:
    virtual Button* createButton() = 0;
};
```

---

## 4. Builder Pattern
👉 Builds complex objects **step by step**

```cpp
class House {
public:
    string walls, roof;
};

class HouseBuilder {
public:
    House build() {
        return {"Brick Walls", "Concrete Roof"};
    }
};
```

---

## 5. Prototype Pattern
👉 Clone existing object

```cpp
class Prototype {
public:
    virtual Prototype* clone() = 0;
};

class Concrete : public Prototype {
public:
    Prototype* clone() {
        return new Concrete(*this);
    }
};
```

---

# 🧱 STRUCTURAL PATTERNS

## 1. Adapter Pattern
👉 Converts one interface into another

```cpp
class OldSystem {
public:
    void oldRequest() {}
};

class Adapter {
    OldSystem* old;
public:
    Adapter(OldSystem* o) : old(o) {}
    void request() {
        old->oldRequest();
    }
};
```

---

## 2. Bridge Pattern
👉 Separates abstraction from implementation

```cpp
class Color {
public:
    virtual void apply() = 0;
};

class Red : public Color {
public:
    void apply() { cout << "Red"; }
};
```

---

## 3. Decorator Pattern
👉 Adds behavior dynamically

```cpp
class Coffee {
public:
    virtual int cost() = 0;
};

class SimpleCoffee : public Coffee {
public:
    int cost() { return 10; }
};
```

---

## 4. Facade Pattern
👉 Simplified interface

```cpp
class CPU {
public:
    void start() {}
};

class Computer {
    CPU cpu;
public:
    void start() {
        cpu.start();
    }
};
```

---

## 5. Proxy Pattern
👉 Controls access

```cpp
class Image {
public:
    virtual void display() = 0;
};

class ProxyImage : public Image {
public:
    void display() {}
};
```

---

# 🔁 BEHAVIORAL PATTERNS

## 1. Observer Pattern
👉 One-to-many notification

```cpp
class Observer {
public:
    virtual void update() = 0;
};
```

---

## 2. Strategy Pattern
👉 Change behavior at runtime

```cpp
class Strategy {
public:
    virtual int execute(int a, int b) = 0;
};
```

---

## 3. Command Pattern
👉 Encapsulates request

```cpp
class Command {
public:
    virtual void execute() = 0;
};
```

---

## 4. State Pattern
👉 Change behavior based on state

```cpp
class State {
public:
    virtual void handle() = 0;
};
```

---

## 5. Template Method Pattern
👉 Algorithm skeleton

```cpp
class Game {
public:
    void play() {
        start();
        end();
    }
    virtual void start() = 0;
    virtual void end() = 0;
};
```

---

## 6. Visitor Pattern
👉 Separate operations from objects

```cpp
class Visitor {
public:
    virtual void visit() = 0;
};
```

---

# ✅ How to Practice
1. Rewrite each pattern
2. Add real-world example
3. Convert to interview answers

---

## ⭐ Interview Tip
> First say **intent**, then **structure**, then **example**.

---

Happy Learning 🚀  
Made for **Lalit Kumar**


# 🏗️ Software Design Patterns: The Ultimate Guide

This repository contains a deep dive into the 23 classic Gang of Four (GoF) design patterns, categorized by their intent and usage.

## ❓ Why Use Design Patterns?
Design patterns are not ready-made code, but rather **templates** for solving common problems in software design.
* **Don't Reinvent the Wheel:** Use battle-tested solutions to recurring problems.
* **Common Language:** Developers can say "this is a Decorator" and others instantly understand the architecture.
* **Maintainability:** Patterns promote "Clean Code" principles like SOLID, making software easier to scale and debug.

---

## 📂 1. Classification of Patterns

Design patterns are grouped into three main categories based on how they interact with your objects:

| Category | Purpose | Example Patterns |
| :--- | :--- | :--- |
| **Creational** | How objects are created. | Singleton, Factory, Builder |
| **Structural** | How classes and objects compose into larger structures. | Adapter, Facade, Proxy |
| **Behavioral** | How objects communicate and distribute responsibility. | Observer, Strategy, State |

---

## 🛠️ 2. Creational Patterns
*Focus: Isolating the system from how its objects are created.*

**Example: Singleton Pattern (C++)**
The Singleton ensures a class has only one instance and provides a global point of access to it.

```cpp
class Singleton {
private:
    static Singleton* instance;
    Singleton() {} // Private constructor

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

# 🏗️ The Design Patterns Compendium (Java & C++)

A comprehensive guide to the 23 Gang of Four design patterns, featuring side-by-side implementations in Java and C++.

---

## 1. Creational Patterns: Singleton
**Goal:** Ensure a class has only one instance.

### ☕ Java (Thread-Safe)
```java
public class Singleton {
    private static volatile Singleton instance;
    private Singleton() {}

    public static Singleton getInstance() {
        if (instance == null) {
            synchronized (Singleton.class) {
                if (instance == null) instance = new Singleton();
            }
        }
        return instance;
    }
}
🖥️ C++ (Meyers Singleton)C++class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance; // Thread-safe in C++11
        return instance;
    }
private:
    Singleton() {}
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;
};
2. Structural Patterns: AdapterGoal: Wrap an incompatible interface into one the client expects.☕ JavaJavainterface Target { void request(); }

class Adaptee { void specificRequest() { System.out.println("Adaptee call"); } }

class Adapter implements Target {
    private Adaptee adaptee;
    public Adapter(Adaptee a) { this.adaptee = a; }
    public void request() { adaptee.specificRequest(); }
}
🖥️ C++C++class Target {
public:
    virtual void request() = 0;
};

class Adaptee {
public:
    void specificRequest() { cout << "Adaptee call" << endl; }
};

class Adapter : public Target {
    Adaptee* adaptee;
public:
    Adapter(Adaptee* a) : adaptee(a) {}
    void request() override { adaptee->specificRequest(); }
};
3. Behavioral Patterns: StrategyGoal: Define a family of algorithms and make them interchangeable.☕ JavaJavainterface Strategy { void execute(); }

class ConcreteStrategyA implements Strategy {
    public void execute() { System.out.println("Strategy A"); }
}

class Context {
    private Strategy strategy;
    public void setStrategy(Strategy s) { this.strategy = s; }
    public void run() { strategy.execute(); }
}
🖥️ C++C++class Strategy {
public:
    virtual void execute() = 0;
};

class ConcreteStrategyA : public Strategy {
public:
    void execute() override { cout << "Strategy A" << endl; }
};

class Context {
    Strategy* strategy;
public:
    void setStrategy(Strategy* s) { strategy = s; }
    void run() { strategy->execute(); }
};
📖 Pattern Summary TablePatternTypeUse CaseFactory MethodCreationalWhen you don't know the exact class until runtime.BuilderCreationalConstructing complex objects step-by-step.DecoratorStructuralAdding behavior to objects without inheritance.ObserverBehavioralNotifying multiple objects about state changes.StateBehavioralAllowing an object to change behavior when its state changes.🛠️ How to CompileJava: javac FileName.javaC++: g++ -std=c++11 FileName.cpp -o Pattern
---

### Why Java and C++ look different here:
* **Memory Management:** In Java, we rely on the Garbage Collector. In C++, we use `delete` or smart pointers (though I used raw pointers for simplicity above) to prevent memory leaks.
* **Thread Safety:** Java requires explicit `synchronized` blocks for singletons, whereas C++11 guarantees that local static variables are initialized in a thread-safe manner.

Would you like me to expand on a specific sub-section, such as the **Observer** 