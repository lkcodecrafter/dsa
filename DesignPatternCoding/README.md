# 🎯 GoF (Gang of Four) Design Patterns
## Complete Interview & Practical Guide (C++)

> A beginner-to-advanced guide to all 23 GoF Design Patterns with C++ examples, UML diagrams, interview questions, and real-world use cases.

---

# 📚 Table of Contents
- [Part 1 - Introduction](#part-1---introduction)
- [Part 2 - Creational Patterns (5)](#part-2---creational-patterns-5)
- [Part 3 - Structural Patterns (7)](#part-3---structural-patterns-7)
- [Part 4 - Behavioral Patterns (11)](#part-4---behavioral-patterns-11)
- [Part 5 - Design Pattern Comparison](#part-5---design-pattern-comparison)
- [Part 6 - Modern C++ & Design Patterns](#part-6---modern-c---design-patterns)
- [Part 7 - Design Patterns in Embedded Systems](#part-7---design-patterns-in-embedded-systems)
- [Part 8 - Qualcomm Camera HAL Examples](#part-8---qualcomm-camera-hal-examples)
- [Part 9 - UML Cheat Sheet](#part-9---uml-cheat-sheet)
- [Part 10 - Interview Preparation](#part-10---interview-preparation)

---

# Part 1 - Introduction

### What are Design Patterns?
Design Patterns are **reusable, templates** that solve recurring design problems in software engineering. They are not concrete code snippets, but architectural templates.

### Why Design Patterns?
- **Avoid reinventing the wheel:** Use battle-tested architectures.
- **Common vocabulary:** Allows developers to say "This is an Observer pattern" and align immediately.
- **Enhance SOLID principles:** Keep code maintainable, decoupled, and extensible.

### History of GoF
Introduced in 1994 by Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides (the **Gang of Four**) in their seminal book *Design Patterns: Elements of Reusable Object-Oriented Software*.

### SOLID Principles
- **S**ingle Responsibility (SRP)
- **O**pen/Closed (OCP) - open for extension, closed for modification.
- **L**iskov Substitution (LSP) - child classes should be substitutable for parents.
- **I**nterface Segregation (ISP)
- **D**ependency Inversion (DIP)

### Composition vs Inheritance
- **Inheritance ("Is-A"):** Static, compile-time relationship. Leads to class explosion.
- **Composition ("Has-A"):** Dynamic, runtime relationship. Flexible and decoupled. **Favor Composition over Inheritance.**

### Coupling & Cohesion
- **Coupling:** Degree of dependency between modules (Aim: **Low Coupling**).
- **Cohesion:** How focused a module's responsibilities are (Aim: **High Cohesion**).

### UML Basics
- `+` Public, `-` Private, `#` Protected
- `-->` Association (uses-a)
- `--|>` Inheritance/Realization (is-a)
- `o--` Aggregation (weak has-a, lifecycle independent)
- `*--` Composition (strong has-a, lifecycle bound)

---

# Part 2 - Creational Patterns (5)

## 1. Singleton Pattern
**Intent:** Ensure a class has only one instance and provides a global access point.

### Problem
Multiple parts of a system need access to a single shared resource (e.g., Configuration, Logging, Hardware Context) without creating multiple duplicate objects.

### UML
```
+-----------------------------------+
|            Singleton              |
+-----------------------------------+
| - static instance: Singleton*     |
| - Singleton()                     |
+-----------------------------------+
| + static getInstance(): Singleton*|
+-----------------------------------+
```

### C++ Example (Classic Thread-Safe & Meyers Singleton)
```cpp
#include <iostream>
#include <mutex>

// 1. Classic Thread-Safe Singleton (Double-Checked Locking)
class ClassicSingleton {
private:
    static ClassicSingleton* instance;
    static std::mutex mtx;
    ClassicSingleton() { std::cout << "Classic Singleton Created.\n"; }

public:
    ClassicSingleton(const ClassicSingleton&) = delete;
    ClassicSingleton& operator=(const ClassicSingleton&) = delete;

    static ClassicSingleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new ClassicSingleton();
            }
        }
        return instance;
    }
};
ClassicSingleton* ClassicSingleton::instance = nullptr;
std::mutex ClassicSingleton::mtx;

// 2. Meyers Singleton (Best practice for C++11 onwards - Thread-Safe natively)
class MeyersSingleton {
private:
    MeyersSingleton() { std::cout << "Meyers Singleton Created.\n"; }

public:
    MeyersSingleton(const MeyersSingleton&) = delete;
    MeyersSingleton& operator=(const MeyersSingleton&) = delete;

    static MeyersSingleton& getInstance() {
        static MeyersSingleton instance; // Guaranteed thread-safe in C++11
        return instance;
    }
    void doSomething() { std::cout << "Working...\n"; }
};
```

### Pros & Cons
- **Pros:** Controlled access, dynamic initialization.
- **Cons:** Violates Single Responsibility, difficult to unit test (global state), hides dependencies.

### Interview Questions
- **Q:** How is Meyers Singleton thread-safe?
  - *A:* In C++11, static local variables are guaranteed by the runtime compiler to be initialized in a thread-safe manner.
- **Q:** Why delete copy constructor and assignment operator?
  - *A:* To prevent cloning and multiple instances.

---

## 2. Factory Method Pattern
**Intent:** Define an interface for creating an object, but let subclasses decide which class to instantiate.

### Problem
A framework needs to create objects, but doesn't know the exact class types beforehand.

### UML
```
Creator <|-- ConcreteCreator
   |
   v creates
Product <|-- ConcreteProduct
```

### C++ Example
```cpp
#include <iostream>
#include <memory>

class Product {
public:
    virtual ~Product() = default;
    virtual void use() = 0;
};

class ConcreteProductA : public Product {
public:
    void use() override { std::cout << "Product A used.\n"; }
};

class Creator {
public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<Product> createProduct() = 0; // Factory Method
};

class ConcreteCreatorA : public Creator {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::make_unique<ConcreteProductA>();
    }
};
```

### Advantages
- Decouples client from concrete classes.
- Promotes Open/Closed Principle.

### Interview Questions
- **Q:** Difference between Simple Factory and Factory Method?
  - *A:* Simple Factory uses a single class with conditional logic (switch/if). Factory Method uses inheritance and polymorphism, delegating creation to sub-classes.

---

## 3. Abstract Factory Pattern
**Intent:** Provide an interface for creating families of related or dependent objects without specifying their concrete classes.

### UML
```
Client ---> AbstractFactory
              |
         AbstractProductA & AbstractProductB
```

### C++ GUI Example
```cpp
#include <iostream>
#include <memory>

class Button { public: virtual ~Button() = default; virtual void paint() = 0; };
class WinButton : public Button { public: void paint() override { std::cout << "Win Button.\n"; } };
class MacButton : public Button { public: void paint() override { std::cout << "Mac Button.\n"; } };

class ScrollBar { public: virtual ~ScrollBar() = default; virtual void scroll() = 0; };
class WinScrollBar : public ScrollBar { public: void scroll() override { std::cout << "Win ScrollBar.\n"; } };
class MacScrollBar : public ScrollBar { public: void scroll() override { std::cout << "Mac ScrollBar.\n"; } };

class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<ScrollBar> createScrollBar() = 0;
};

class WinFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override { return std::make_unique<WinButton>(); }
    std::unique_ptr<ScrollBar> createScrollBar() override { return std::make_unique<WinScrollBar>(); }
};
```

### Interview Questions
- **Q:** When to use Abstract Factory?
  - *A:* When a system must configure itself with families of compatible parts (e.g., cross-platform UI widgets).

---

## 4. Builder Pattern
**Intent:** Separate the construction of a complex object from its representation so that the same construction process can create different representations.

### C++ Example
```cpp
#include <iostream>
#include <string>

class PC {
public:
    std::string cpu;
    std::string gpu;
    void show() { std::cout << "PC: " << cpu << " & " << gpu << "\n"; }
};

class PCBuilder {
protected:
    PC pc;
public:
    virtual ~PCBuilder() = default;
    virtual void buildCPU() = 0;
    virtual void buildGPU() = 0;
    PC getResult() { return pc; }
};

class GamingPCBuilder : public PCBuilder {
public:
    void buildCPU() override { pc.cpu = "Intel i9"; }
    void buildGPU() override { pc.gpu = "RTX 4090"; }
};

class Director {
public:
    PC construct(PCBuilder& builder) {
        builder.buildCPU();
        builder.buildGPU();
        return builder.getResult();
    }
};
```

### Interview Questions
- **Q:** Why use a Director?
  - *A:* The Director defines the assembly steps, while the Builder implements them. It keeps assembly logic out of client code.

---

## 5. Prototype Pattern
**Intent:** Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.

### C++ Example
```cpp
#include <iostream>
#include <memory>

class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void print() = 0;
};

class ConcretePrototype : public Prototype {
private:
    int data;
public:
    ConcretePrototype(int d) : data(d) {}
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype>(*this); // Deep copy clone
    }
    void print() override { std::cout << "Data: " << data << "\n"; }
};
```

### Interview Questions
- **Q:** Difference between deep and shallow copies in Prototype?
  - *A:* Shallow copies pointers, sharing the underlying reference memory. Deep copies allocate new memory and copy values, preventing runtime side effects.

---

# Part 3 - Structural Patterns (7)

## 6. Adapter Pattern
**Intent:** Convert the interface of a class into another interface clients expect.

### UML
```
Client ---> Target (interface)
              ^
              | implements
           Adapter ---> Adaptee
```

### C++ Object Adapter Example
```cpp
#include <iostream>

class Target {
public:
    virtual ~Target() = default;
    virtual void request() = 0;
};

class Adaptee {
public:
    void legacyRequest() { std::cout << "Legacy Request Called.\n"; }
};

class Adapter : public Target {
private:
    Adaptee* adaptee;
public:
    Adapter(Adaptee* a) : adaptee(a) {}
    void request() override {
        adaptee->legacyRequest();
    }
};
```

---

## 7. Bridge Pattern
**Intent:** Decouple an abstraction from its implementation so that the two can vary independently.

### C++ Device/Remote Example
```cpp
#include <iostream>

class Device {
public:
    virtual ~Device() = default;
    virtual void setVolume(int v) = 0;
};

class TV : public Device {
public:
    void setVolume(int v) override { std::cout << "TV volume set to: " << v << "\n"; }
};

class Remote {
protected:
    Device* device; // Bridge link
public:
    Remote(Device* d) : device(d) {}
    virtual void volumeUp() = 0;
};

class AdvancedRemote : public Remote {
public:
    AdvancedRemote(Device* d) : Remote(d) {}
    void volumeUp() override { device->setVolume(50); }
};
```

---

## 8. Composite Pattern
**Intent:** Compose objects into tree structures to represent part-whole hierarchies.

### File System C++ Example
```cpp
#include <iostream>
#include <vector>
#include <string>

class Component {
public:
    virtual ~Component() = default;
    virtual void display(int depth) = 0;
};

class File : public Component {
private:
    std::string name;
public:
    File(std::string n) : name(n) {}
    void display(int depth) override {
        std::cout << std::string(depth, '-') << name << "\n";
    }
};

class Directory : public Component {
private:
    std::string name;
    std::vector<Component*> children;
public:
    Directory(std::string n) : name(n) {}
    void add(Component* c) { children.push_back(c); }
    void display(int depth) override {
        std::cout << std::string(depth, '+') << name << "\n";
        for (auto child : children) {
            child->display(depth + 2);
        }
    }
};
```

---

## 9. Decorator Pattern ✅
*(Current Chapter)*

### Problem
We want to add capabilities to objects at runtime (e.g., adding visual effects, metrics trackers, logging, or camera pipelines) without inheritance. Using inheritance results in static subclasses and **class explosion** (e.g., `SimpleCoffee`, `CoffeeWithMilk`, `CoffeeWithSugar`, `CoffeeWithMilkAndSugar`).

### UML
```
             Component
             ^       ^
             |       |
     BaseComponent  Decorator ---> Component (wraps)
                       ^
                       |
               ConcreteDecorator
```

### C++ Coffee & Pizza & Camera HAL Example
```cpp
#include <iostream>
#include <memory>
#include <string>

// --- Abstract Component ---
class Beverage {
public:
    virtual ~Beverage() = default;
    virtual std::string getDescription() = 0;
    virtual double cost() = 0;
};

// --- Concrete Component ---
class Espresso : public Beverage {
public:
    std::string getDescription() override { return "Espresso"; }
    double cost() override { return 1.99; }
};

// --- Decorator Base Class ---
class CondimentDecorator : public Beverage {
protected:
    std::shared_ptr<Beverage> beverage; // Wrapped component
public:
    CondimentDecorator(std::shared_ptr<Beverage> b) : beverage(b) {}
};

// --- Concrete Decorators ---
class Milk : public CondimentDecorator {
public:
    Milk(std::shared_ptr<Beverage> b) : CondimentDecorator(b) {}
    std::string getDescription() override { return beverage->getDescription() + ", Milk"; }
    double cost() override { return beverage->cost() + 0.50; }
};

class Mocha : public CondimentDecorator {
public:
    Mocha(std::shared_ptr<Beverage> b) : CondimentDecorator(b) {}
    std::string getDescription() override { return beverage->getDescription() + ", Mocha"; }
    double cost() override { return beverage->cost() + 0.20; }
};
```

### Camera HAL Frame Processor Example
```cpp
class Frame {
public:
    void render() { std::cout << "Rendering clean video frame.\n"; }
};

class FrameProcessor {
public:
    virtual ~FrameProcessor() = default;
    virtual void process(Frame& f) = 0;
};

class BaseFrameProcessor : public FrameProcessor {
public:
    void process(Frame& f) override { f.render(); }
};

class FrameDecorator : public FrameProcessor {
protected:
    FrameProcessor* processor;
public:
    FrameDecorator(FrameProcessor* p) : processor(p) {}
};

class BeautyFilter : public FrameDecorator {
public:
    BeautyFilter(FrameProcessor* p) : FrameDecorator(p) {}
    void process(Frame& f) override {
        std::cout << "Applying Skin-Smoothing Beauty Filter...\n";
        processor->process(f);
    }
};
```

### Step-by-Step Execution Flow
1. Instantiate base object `Espresso`.
2. Wrap it inside `Milk` decorator: `Milk(Espresso)`.
3. Wrap it again inside `Mocha` decorator: `Mocha(Milk(Espresso))`.
4. Call `.cost()`: `Mocha` adds `$0.20` + delegates to `Milk` (`$0.50` + delegates to `Espresso` (`$1.99`)). Result = `$2.69`.

---

## 10. Facade Pattern
**Intent:** Provide a unified interface to a set of interfaces in a subsystem.

### C++ Example
```cpp
#include <iostream>

class ISP { public: void configure() { std::cout << "ISP pipeline ready.\n"; } };
class Sensor { public: void startStream() { std::cout << "Sensor streaming active.\n"; } };

// Facade
class CameraDeviceFacade {
private:
    ISP isp;
    Sensor sensor;
public:
    void startCapture() {
        isp.configure();
        sensor.startStream();
        std::cout << "Camera initialized completely.\n";
    }
};
```

---

## 11. Flyweight Pattern
**Intent:** Use sharing to support large numbers of fine-grained objects efficiently.

### C++ Example
```cpp
#include <iostream>
#include <unordered_map>
#include <string>

class CharacterFlyweight {
private:
    char symbol; // Intrinsic state
public:
    CharacterFlyweight(char s) : symbol(s) {}
    void display(int size) { // Extrinsic state passed dynamically
        std::cout << "Char: " << symbol << " Size: " << size << "\n";
    }
};

class FlyweightFactory {
private:
    std::unordered_map<char, CharacterFlyweight*> flyweights;
public:
    CharacterFlyweight* getCharacter(char symbol) {
        if (flyweights.find(symbol) == flyweights.end()) {
            flyweights[symbol] = new CharacterFlyweight(symbol);
        }
        return flyweights[symbol];
    }
};
```

---

## 12. Proxy Pattern
**Intent:** Provide a surrogate or placeholder for another object to control access to it.

### C++ Example
```cpp
#include <iostream>

class Subject {
public:
    virtual ~Subject() = default;
    virtual void request() = 0;
};

class RealSubject : public Subject {
public:
    void request() override { std::cout << "Executing real request.\n"; }
};

class Proxy : public Subject {
private:
    RealSubject* realSubject = nullptr;
public:
    ~Proxy() { delete realSubject; }
    void request() override {
        if (!realSubject) {
            realSubject = new RealSubject(); // Lazy loading
        }
        std::cout << "Proxy Intercepting... Calling real target.\n";
        realSubject->request();
    }
};
```

---

# Part 4 - Behavioral Patterns (11)

## 13. Chain of Responsibility
**Intent:** Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request.

### C++ Logger Example
```cpp
#include <iostream>

class Logger {
protected:
    Logger* nextLogger = nullptr;
public:
    virtual ~Logger() = default;
    void setNext(Logger* next) { nextLogger = next; }
    void log(int level, const std::string& msg) {
        if (canHandle(level)) {
            write(msg);
        }
        if (nextLogger) {
            nextLogger->log(level, msg);
        }
    }
    virtual bool canHandle(int level) = 0;
    virtual void write(const std::string& msg) = 0;
};
```

---

## 14. Command Pattern
**Intent:** Encapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undoable operations.

### C++ Command Example
```cpp
#include <iostream>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class Light {
public:
    void turnOn() { std::cout << "Light is ON.\n"; }
};

class LightOnCommand : public Command {
private:
    Light* light;
public:
    LightOnCommand(Light* l) : light(l) {}
    void execute() override { light->turnOn(); }
};
```

---

## 15. Interpreter Pattern
**Intent:** Given a language, define a representation for its grammar along with an interpreter that uses the representation to interpret sentences in the language.

### C++ Calculator Example
```cpp
#include <iostream>
#include <memory>

class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret() = 0;
};

class Constant : public Expression {
private:
    int val;
public:
    Constant(int v) : val(v) {}
    int interpret() override { return val; }
};
```

---

## 16. Iterator Pattern
**Intent:** Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

### C++ Example
```cpp
#include <iostream>
#include <vector>

template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual T next() = 0;
    virtual bool hasNext() = 0;
};

template <typename T>
class ConcreteIterator : public Iterator<T> {
private:
    std::vector<T> data;
    size_t index = 0;
public:
    ConcreteIterator(std::vector<T> d) : data(d) {}
    T next() override { return data[index++]; }
    bool hasNext() override { return index < data.size(); }
};
```

---

## 17. Mediator Pattern
**Intent:** Define an object that encapsulates how a set of objects interact.

### Chat Room Example
```cpp
#include <iostream>
#include <string>
#include <vector>

class User;
class ChatMediator {
public:
    virtual void sendMessage(const std::string& msg, User* sender) = 0;
};
```

---

## 18. Memento Pattern
**Intent:** Without violating encapsulation, capture and externalize an object's internal state so that the object can be restored to this state later.

### C++ Text Editor Example
```cpp
#include <iostream>
#include <string>

class Memento {
private:
    std::string state;
public:
    Memento(std::string s) : state(s) {}
    std::string getState() { return state; }
};
```

---

## 19. Observer Pattern
**Intent:** Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.

### Camera HAL Callback Example
```cpp
#include <iostream>
#include <vector>

class FrameObserver {
public:
    virtual void onFrameReady() = 0;
};

class CameraSensor {
private:
    std::vector<FrameObserver*> observers;
public:
    void registerObserver(FrameObserver* o) { observers.push_back(o); }
    void notifyObservers() {
        for (auto o : observers) {
            o->onFrameReady();
        }
    }
};
```

---

## 20. State Pattern
**Intent:** Allow an object to alter its behavior when its internal state changes. The object will appear to change its class.

### C++ State Example
```cpp
#include <iostream>

class Context;
class State {
public:
    virtual ~State() = default;
    virtual void handle(Context* c) = 0;
};
```

---

## 21. Strategy Pattern
**Intent:** Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

### sorting/processing Example
```cpp
#include <iostream>

class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort() = 0;
};

class QuickSort : public SortStrategy {
public:
    void sort() override { std::cout << "Sorting using QuickSort.\n"; }
};
```

---

## 22. Template Method Pattern
**Intent:** Define the skeleton of an algorithm in an operation, deferring some steps to subclasses.

### C++ Example
```cpp
#include <iostream>

class Game {
public:
    void play() { // Template Method
        initialize();
        start();
        end();
    }
    virtual void initialize() = 0;
    virtual void start() = 0;
    virtual void end() = 0;
};
```

---

## 23. Visitor Pattern
**Intent:** Represent an operation to be performed on the elements of an object structure. Visitor lets you define a new operation without changing the classes of the elements on which it operates.

### C++ Example
```cpp
#include <iostream>

class Element;
class Visitor {
public:
    virtual void visit(Element* e) = 0;
};
```

---

# Part 5 - Design Pattern Comparison

| Comparison | Key Difference |
|---|---|
| **Factory vs Abstract Factory** | Factory creates a single product; Abstract Factory creates families of related products. |
| **Factory vs Builder** | Factory creates objects in a single call; Builder builds objects step-by-step. |
| **Builder vs Prototype** | Builder creates objects incrementally; Prototype duplicates existing objects using clones. |
| **Adapter vs Bridge** | Adapter resolves compatibility interface issues; Bridge separates Abstraction and Implementation. |
| **Adapter vs Facade** | Adapter wraps a single class to adapt it; Facade wraps a whole subsystem to simplify it. |
| **Decorator vs Proxy** | Decorator adds features dynamically; Proxy controls access/lifecycle of an object. |
| **Strategy vs State** | Strategy configures an algorithm statically or dynamically; State switches behaviors based on state machine values. |
| **Strategy vs Template** | Strategy uses delegation/composition (runtime); Template uses inheritance (compile-time). |

---

# Part 6 - Modern C++ & Design Patterns

Modern C++ (C++11/14/17/20) changes how design patterns are implemented:
- **Smart Pointers (`std::unique_ptr`, `std::shared_ptr`):** Eliminates raw pointer manual memory management and memory leaks.
- **RAII (Resource Acquisition Is Initialization):** Ties resource cleanup to object lifetimes automatically.
- **Meyers Singleton:** Uses compiler-guaranteed thread-safe local static variables.
- **CRTP (Curiously Recurring Template Pattern):** Achieves static polymorphism without virtual table lookups, optimizing performance in embedded and graphics programming.

---

# Part 7 - Design Patterns in Embedded Systems

Design patterns in embedded microcontrollers require optimizing for memory footprint and performance:
- **State Machine Pattern:** Crucial for handling hardware states, RTOS scheduling, and sensor states (e.g., AUTOSAR State Manager).
- **Strategy Pattern:** Used to switch hardware interfaces at runtime (e.g., switching between UART and SPI communication drivers).
- **Command Pattern:** Used in DMA (Direct Memory Access) frame transmission pipelines and capture task scheduling.

---

# Part 8 - Qualcomm Camera HAL Examples

Android Camera HAL (CAMX/CHI) depends heavily on GoF patterns:
- **Singleton in Camera HAL:** Access global services such as `SensorManager` and `CameraService`.
- **Factory Pattern:** Dynamically instantiates the correct sensor control object (e.g., IMX586 vs S5KGW1) based on EEPROM device IDs.
- **Observer Pattern:** Notifies client applications of RAW/YUV frame metadata, auto-exposure changes, and autofocus state transitions.
- **Decorator Pattern:** Wraps a standard frame processor with specialized CHI processors to perform hardware denoising, EIS, and beauty filters.

---

# Part 9 - UML Cheat Sheet

- **Dependency (`..>`)**: Temporary usage relationship (Class A uses Class B inside a method parameters).
- **Association (`-->`)**: Persistent field relationship (Class A holds a pointer/reference of Class B).
- **Aggregation (`o-->`)**: "Has-A" relationship where parts can exist independently of the whole (e.g., Computer and Keyboard).
- **Composition (`*-->`)**: "Has-A" relationship where parts cannot exist without the whole (e.g., Room inside House).

---

# Part 10 - Interview Preparation

### Beginner Questions
1. **What is a design pattern?**
   - A general, reusable blueprint to solve a common design problem.
2. **Name three categories of design patterns.**
   - Creational, Structural, and Behavioral.

### Intermediate Questions
1. **Why is composition preferred over inheritance?**
   - Composition is runtime-configurable, decouples relationships, and avoids structural inheritance bloat.
2. **What is the Open/Closed Principle?**
   - Code should be open for extension but closed for modification.

### Advanced Questions
1. **How is Android's Binder framework related to the Proxy Pattern?**
   - Binder uses static or dynamic proxies to abstract the IPC (Inter-Process Communication) mechanics, presenting local stubs to developers that represent remote services.
2. **Explain the benefits of Meyers Singleton.**
   - It is thread-safe, has zero manual heap allocation leaks, and uses lazy-loading.
