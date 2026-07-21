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
Design Patterns are **reusable templates** that solve recurring design problems in software engineering. They are not concrete code snippets, but architectural templates.

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
**Intent:** Ensure a class has only one instance and provides a global access point to it.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of the **President of a Country**:
- A country can only have **one** President at a time.
- If any citizen (client) wants to contact the President, they don't elect a new one; they are directed to the same, single existing President instance.

```text
  [ Client A ] ---\
                   \
  [ Client B ] -----> [ Singleton Instance (The President) ]
                   /
  [ Client C ] ---/
```

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

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <string>

// Meyers Singleton (Best practice for C++11 onwards - Thread-Safe natively)
class President {
private:
    std::string name;
    
    // 1. Private constructor prevents direct instantiation from outside
    President() : name("President George") { 
        std::cout << "👤 President initialized (Only once!).\n"; 
    }

public:
    // 2. Delete copy constructor and assignment operator to prevent duplication
    President(const President&) = delete;
    President& operator=(const President&) = delete;

    // 3. Global access point to get the single instance
    static President& getInstance() {
        static President instance; // Guaranteed thread-safe in C++11
        return instance;
    }

    void deliverSpeech() {
        std::cout << "🗣️ " << name << " is delivering a speech to the nation!\n";
    }
};

int main() {
    std::cout << "--- Citizen A requests the President ---\n";
    President& presidentA = President::getInstance();
    presidentA.deliverSpeech();

    President* p = &President::getInstance(); //& we can use if * is there otherwise no 
    p->deliverSpeech(); 

    std::cout << "\n--- Citizen B requests the President ---\n";
    President& presidentB = President::getInstance();
    presidentB.deliverSpeech();

    // Check if they refer to the exact same memory location
    if (&presidentA == &presidentB) {
        std::cout << "\n✅ Success: Both references point to the exact same President instance!\n";
    }
    return 0;
}
```

### 📋 Expected Console Output
```text
--- Citizen A requests the President ---
👤 President initialized (Only once!).
🗣️ President George is delivering a speech to the nation!

--- Citizen B requests the President ---
🗣️ President George is delivering a speech to the nation!

✅ Success: Both references point to the exact same President instance!
```

### Pros & Cons
- **Pros:** Controlled access, dynamic initialization (lazy loading).
- **Cons:** Violates Single Responsibility Principle, difficult to unit test (global state), hides dependencies.

### Interview Questions
- **Q:** How is Meyers Singleton thread-safe?
  - *A:* In C++11, static local variables are guaranteed by the compiler to be initialized in a thread-safe manner during the first control pass.
- **Q:** Why delete the copy constructor and assignment operator?
  - *A:* To prevent cloning/copying of the object, which would result in multiple instances.

---

## 2. Factory Method Pattern
**Intent:** Define an interface for creating an object, but let subclasses decide which class to instantiate.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Toy Factory**:
- The client wants a toy but doesn't know how to construct it.
- Instead of manually building a `Car` or `Doll`, the client uses a `ToyFactory`.
- The factory delegates the actual creation to subclass factories (`CarFactory`, `DollFactory`), returning a generic `Toy` interface to the client.

```text
                     [ Factory Interface (Creator) ]
                                   |
                                   v
                      [ Toy Factory (Concrete) ]
                                   |
                     creates (returns Product pointer)
                                   v
                      [ Toy Interface (Product) ]
                        /                      \
                       v                        v
             [ Car Toy (Concrete) ]   [ Doll Toy (Concrete) ]
```

### UML
```
Creator <|-- ConcreteCreator
   |
   v creates
Product <|-- ConcreteProduct
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>
#include <string>

// 1. Abstract Product
class Toy {
public:
    virtual ~Toy() = default;
    virtual void play() = 0;
};

// 2. Concrete Products
class CarToy : public Toy {
public:
    void play() override { std::cout << "🏎️ Playing with a Toy Car! Vroom!\n"; }
};

class DollToy : public Toy {
public:
    void play() override { std::cout << "🧸 Playing with a Toy Doll! Hello!\n"; }
};

// 3. Creator (Factory) Interface
class ToyFactory {
public:
    virtual ~ToyFactory() = default;
    virtual std::unique_ptr<Toy> createToy() = 0; // The Factory Method
};

// 4. Concrete Creators
class CarFactory : public ToyFactory {
public:
    std::unique_ptr<Toy> createToy() override {
        return std::make_unique<CarToy>();
    }
};

class DollFactory : public ToyFactory {
public:
    std::unique_ptr<Toy> createToy() override {
        return std::make_unique<DollToy>();
    }
};

// Client Code
int main() {
    std::cout << "--- Client orders a Car Toy ---\n";
    std::unique_ptr<ToyFactory> carFactory = std::make_unique<CarFactory>();
    std::unique_ptr<Toy> toy1 = carFactory->createToy();
    toy1->play();

    std::cout << "\n--- Client orders a Doll Toy ---\n";
    std::unique_ptr<ToyFactory> dollFactory = std::make_unique<DollFactory>();
    std::unique_ptr<Toy> toy2 = dollFactory->createToy();
    toy2->play();

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Client orders a Car Toy ---
🏎️ Playing with a Toy Car! Vroom!

--- Client orders a Doll Toy ---
🧸 Playing with a Toy Doll! Hello!
```

### Advantages
- Decouples the client from concrete classes.
- Promotes the Open/Closed Principle (adding a new toy type doesn't break existing client code).

### Interview Questions
- **Q:** Difference between Simple Factory and Factory Method?
  - *A:* Simple Factory uses a single class with conditional logic (switch/if) to create objects. Factory Method uses inheritance and polymorphism, delegating the creation to subclasses.

---

## 3. Abstract Factory Pattern
**Intent:** Provide an interface for creating families of related or dependent objects without specifying their concrete classes.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Furniture Shop** that sells themed products:
- **Modern Theme:** Modern Chair + Modern Sofa.
- **Victorian Theme:** Victorian Chair + Victorian Sofa.
- To prevent mismatched furniture (e.g., placing a Victorian Chair with a Modern Sofa), the customer uses a themed factory (`ModernFurnitureFactory` or `VictorianFurnitureFactory`) to ensure all pieces belong to the same family.

```text
                   [ Furniture Factory (Abstract Factory) ]
                              /                 \
                             v                   v
              [ Modern Factory ]              [ Victorian Factory ]
               /             \                  /               \
              v               v                v                 v
        Modern Chair     Modern Sofa     Victorian Chair   Victorian Sofa
```

### UML
```
Client ---> AbstractFactory
              |
         AbstractProductA & AbstractProductB
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>
#include <string>

// 1. Abstract Products
class Chair {
public:
    virtual ~Chair() = default;
    virtual void sitOn() = 0;
};

class Sofa {
public:
    virtual ~Sofa() = default;
    virtual void lieOn() = 0;
};

// 2. Concrete Products (Modern Family)
class ModernChair : public Chair {
public:
    void sitOn() override { std::cout << "🛋️ Sitting on a sleek Modern Chair.\n"; }
};

class ModernSofa : public Sofa {
public:
    void lieOn() override { std::cout << "🛋️ Lying on a comfortable Modern Sofa.\n"; }
};

// Concrete Products (Victorian Family)
class VictorianChair : public Chair {
public:
    void sitOn() override { std::cout << "🪑 Sitting on an ornate Victorian Chair.\n"; }
};

class VictorianSofa : public Sofa {
public:
    void lieOn() override { std::cout << "🪑 Lying on an elegant Victorian Sofa.\n"; }
};

// 3. Abstract Factory
class FurnitureFactory {
public:
    virtual ~FurnitureFactory() = default;
    virtual std::unique_ptr<Chair> createChair() = 0;
    virtual std::unique_ptr<Sofa> createSofa() = 0;
};

// 4. Concrete Factories
class ModernFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() override { return std::make_unique<ModernChair>(); }
    std::unique_ptr<Sofa> createSofa() override { return std::make_unique<ModernSofa>(); }
};

class VictorianFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() override { return std::make_unique<VictorianChair>(); }
    std::unique_ptr<Sofa> createSofa() override { return std::make_unique<VictorianSofa>(); }
};

// Client Code (independent of concrete styles)
void orderRoomSet(FurnitureFactory& factory) {
    auto chair = factory.createChair();
    auto sofa = factory.createSofa();
    chair->sitOn();
    sofa->lieOn();
}

int main() {
    std::cout << "--- Ordering Modern Furniture Set ---\n";
    ModernFurnitureFactory modernFactory;
    orderRoomSet(modernFactory);

    std::cout << "\n--- Ordering Victorian Furniture Set ---\n";
    VictorianFurnitureFactory victorianFactory;
    orderRoomSet(victorianFactory);

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Ordering Modern Furniture Set ---
🛋️ Sitting on a sleek Modern Chair.
🛋️ Lying on a comfortable Modern Sofa.

--- Ordering Victorian Furniture Set ---
🪑 Sitting on an ornate Victorian Chair.
🪑 Lying on an elegant Victorian Sofa.
```

### Interview Questions
- **Q:** When should you use Abstract Factory over Factory Method?
  - *A:* Use Factory Method when creating a single product. Use Abstract Factory when you need to create families of related products that must match/work together.

---

## 4. Builder Pattern
**Intent:** Separate the construction of a complex object from its representation so that the same construction process can create different representations.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of ordering a **Custom Pizza**:
- A pizza has many configuration options: crust type, sauce, cheese, toppings.
- Instead of a constructor with 10 parameters (like `Pizza("thick", "tomato", true, false, true, "pepperoni")`), we use a `PizzaBuilder` to add ingredients step-by-step.
- The `Cook` (Director) guides the builder through the steps to assemble the final product.

```text
    [ Pizza Builder ] ---> buildCrust() ---> buildSauce() ---> buildToppings() ---> getPizza()
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <string>
#include <memory>
#include <vector>

// 1. Product
class Pizza {
private:
    std::string crust;
    std::string sauce;
    std::vector<std::string> toppings;
public:
    void setCrust(const std::string& c) { crust = c; }
    void setSauce(const std::string& s) { sauce = s; }
    void addTopping(const std::string& t) { toppings.push_back(t); }
    
    void show() const {
        std::cout << "🍕 Pizza [Crust: " << crust << " | Sauce: " << sauce << " | Toppings: ";
        for (const auto& t : toppings) std::cout << t << " ";
        std::cout << "]\n";
    }
};

// 2. Builder Interface
class PizzaBuilder {
protected:
    std::unique_ptr<Pizza> pizza;
public:
    virtual ~PizzaBuilder() = default;
    void createNewPizza() { pizza = std::make_unique<Pizza>(); }
    std::unique_ptr<Pizza> getPizza() { return std::move(pizza); }

    virtual void buildCrust() = 0;
    virtual void buildSauce() = 0;
    virtual void buildToppings() = 0;
};

// 3. Concrete Builder (Spicy Chicken Pizza)
class SpicyChickenPizzaBuilder : public PizzaBuilder {
public:
    void buildCrust() override { pizza->setCrust("Thin Crust"); }
    void buildSauce() override { pizza->setSauce("Spicy Marinara"); }
    void buildToppings() override { 
        pizza->addTopping("Chicken"); 
        pizza->addTopping("Jalapenos"); 
    }
};

// 4. Director: Controls the construction sequence
class PizzaCook {
public:
    void cookPizza(PizzaBuilder& builder) {
        builder.createNewPizza();
        builder.buildCrust();
        builder.buildSauce();
        builder.buildToppings();
    }
};

// Client Code
int main() {
    std::cout << "--- Builder Pattern: Cook prepares Pizza ---\n";
    PizzaCook cook;
    SpicyChickenPizzaBuilder builder;

    // Director builds the product using concrete builder steps
    cook.cookPizza(builder);
    
    // Retrieve the final assembled product
    std::unique_ptr<Pizza> myPizza = builder.getPizza();
    myPizza->show();

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Builder Pattern: Cook prepares Pizza ---
🍕 Pizza [Crust: Thin Crust | Sauce: Spicy Marinara | Toppings: Chicken Jalapenos ]
```

### Interview Questions
- **Q:** Why use a Director in Builder?
  - *A:* The Director defines the specific assembly steps and sequence, while the Builder implements the steps. This decouples the construction logic from the client.

---

## 5. Prototype Pattern
**Intent:** Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Cellular Mitosis / Cloning Lab**:
- You have an existing complex organism (e.g., a cloned sheep named `Dolly`).
- Constructing a new sheep from scratch is extremely expensive and complex.
- Instead, you call a `clone()` function on `Dolly` to get an exact replica (deep copy) of the sheep.

```text
  [ Original Sheep (Dolly) ] -- clone() --> [ Cloned Sheep (Dolly Copy) ]
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>
#include <string>

// 1. Prototype Interface
class Animal {
public:
    virtual ~Animal() = default;
    virtual std::unique_ptr<Animal> clone() const = 0;
    virtual void makeNoise() const = 0;
    virtual void setName(const std::string& name) = 0;
};

// 2. Concrete Prototype
class Sheep : public Animal {
private:
    std::string name;
    std::string woolColor;
public:
    Sheep(const std::string& n, const std::string& c) : name(n), woolColor(c) {}

    // Copy Constructor (used implicitly inside clone())
    Sheep(const Sheep& other) : name(other.name + "_Clone"), woolColor(other.woolColor) {}

    std::unique_ptr<Animal> clone() const override {
        return std::make_unique<Sheep>(*this); // Deep copy via copy constructor
    }

    void setName(const std::string& n) override { name = n; }

    void makeNoise() const override {
        std::cout << "🐑 " << name << " (" << woolColor << " wool) says: Baaaa!\n";
    }
};

// Client Code
int main() {
    std::cout << "--- Creating Original Sheep prototype ---\n";
    std::unique_ptr<Animal> originalSheep = std::make_unique<Sheep>("Dolly", "White");
    originalSheep->makeNoise();

    std::cout << "\n--- Cloning Sheep from prototype ---\n";
    std::unique_ptr<Animal> clonedSheep = originalSheep->clone();
    clonedSheep->makeNoise();

    std::cout << "\n--- Modifying Clone's property independently ---\n";
    clonedSheep->setName("Polly");
    clonedSheep->makeNoise();
    
    std::cout << "Original remains unchanged: ";
    originalSheep->makeNoise();

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Creating Original Sheep prototype ---
🐑 Dolly (White wool) says: Baaaa!

--- Cloning Sheep from prototype ---
🐑 Dolly_Clone (White wool) says: Baaaa!

--- Modifying Clone's property independently ---
🐑 Polly (White wool) says: Baaaa!
Original remains unchanged: 🐑 Dolly (White wool) says: Baaaa!
```

### Interview Questions
- **Q:** What is the difference between shallow and deep copies in Prototype?
  - *A:* Shallow copies only copy primitive values and pointers (referencing the same underlying dynamic memory, causing bugs). Deep copies allocate new memory and copy data, ensuring the clone is completely independent.

---

# Part 3 - Structural Patterns (7)

## 6. Adapter Pattern
**Intent:** Convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a traveler from the **US** visiting **Europe**:
- **The Target (European Socket):** Expects round pins (`plugInRoundPins()`).
- **The Adaptee (US Laptop Charger):** Has flat pins (`plugInFlatPins()`).
- **The Adapter (Travel Adapter):** Plugs into the European socket (round pins) and provides a slot for the US charger (flat pins).

```text
   +-----------------------+
   |   Traveler (Client)   |
   +-----------+-----------+
               |
               | Uses
               v
   +-----------------------+
   |   US Charger          |  ===> [Flat Pins: ||] (Incompatible with Europe!)
   |   (Adaptee)           |
   +-----------+-----------+
               |
               | Plugs into
               v
   +-----------------------+
   | Travel Adapter        |  (Implements EuropeanSocket,
   |   (Adapter)           |   wraps US Charger)
   +-----------+-----------+
               |
               | Converts and plugs into
               v
   +-----------------------+
   | European Wall Socket  |  ===> [Round Holes: o o] (Success! Power flows)
   |      (Target)         |
   +-----------------------+
```

### UML
```
Client ---> Target (interface)
              ^
              | implements
           Adapter ---> Adaptee (wraps)
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>

// 1. Target Interface: What the client expects (European Socket)
class EuropeanSocket {
public:
    virtual ~EuropeanSocket() = default;
    virtual void plugInRoundPins() = 0;
};

// 2. Adaptee: The class that needs adapting (US Charger)
class USCharger {
public:
    void plugInFlatPins() {
        std::cout << "🔌 US Charger: Plugs in successfully with 2 flat pins.\n";
    }
};

// 3. Adapter: Implements the Target interface and wraps the Adaptee
class PowerAdapter : public EuropeanSocket {
private:
    std::shared_ptr<USCharger> usCharger; // Wrapped object (composition)
public:
    PowerAdapter(std::shared_ptr<USCharger> charger) : usCharger(charger) {}

    void plugInRoundPins() override {
        std::cout << "🔄 Adapter: Converting round pin connection to flat pins...\n";
        usCharger->plugInFlatPins(); // Delegating the work
    }
};

// 4. Client Code
int main() {
    std::cout << "--- Traveler in Europe tries to charge US laptop ---\n";

    // Step 1: Traveler has their US Charger
    auto myUSCharger = std::make_shared<USCharger>();

    // Step 2: Traveler buys/uses a Power Adapter for their US Charger
    auto travelAdapter = std::make_shared<PowerAdapter>(myUSCharger);

    // Step 3: Traveler plugs the Adapter into the European Socket
    // The client interacts only with the Target interface (EuropeanSocket)
    travelAdapter->plugInRoundPins();

    std::cout << "🎉 Success: Laptop is now charging in Europe!\n";
    return 0;
}
```

### 📋 Expected Console Output
```text
--- Traveler in Europe tries to charge US laptop ---
🔄 Adapter: Converting round pin connection to flat pins...
🔌 US Charger: Plugs in successfully with 2 flat pins.
🎉 Success: Laptop is now charging in Europe!
```

---

## 7. Bridge Pattern
**Intent:** Decouple an abstraction from its implementation so that the two can vary independently.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Remote Control** and a **TV / Radio**:
- **Abstraction (Remote Control):** What the user interacts with (power buttons, volume up).
- **Implementation (TV / Radio):** The actual device performing the hardware actions.
- Instead of creating a class for every Remote-Device combination (like `TVBasicRemote`, `RadioAdvancedRemote` causing class explosion), we bridge them. The Remote (Abstraction) holds a pointer to a generic Device (Implementation), allowing both to vary independently.

```text
           ABSTRACTION                             IMPLEMENTATION
      +---------------------+                  +---------------------+
      |   Remote (Parent)   |                  |   Device (Parent)   |
      +----------+----------+                  +----------+----------+
                 |                                        |
      has-a      | Bridge Link (holds pointer to Device)  |
      Device     o======================================> |
                 |                                        |
        +--------+--------+                      +--------+--------+
        |                 |                      |                 |
        v                 v                      v                 v
  +-----------+     +-----------+          +-----------+     +-----------+
  |  Basic    |     | Advanced  |          |    TV     |     |   Radio   |
  |  Remote   |     |  Remote   |          |  Device   |     |  Device   |
  +-----------+     +-----------+          +-----------+     +-----------+
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>
#include <string>

// 1. Implementation Interface: The Device
class Device {
public:
    virtual ~Device() = default;
    virtual bool isEnabled() = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual void setVolume(int percent) = 0;
    virtual std::string getName() = 0;
};

// 2. Concrete Implementations
class TV : public Device {
private:
    bool on = false;
    int volume = 30;
public:
    bool isEnabled() override { return on; }
    void enable() override { on = true; std::cout << "📺 TV: Powered ON.\n"; }
    void disable() override { on = false; std::cout << "📺 TV: Powered OFF.\n"; }
    void setVolume(int percent) override { 
        volume = percent; 
        std::cout << "📺 TV: Volume set to " << volume << "%.\n"; 
    }
    std::string getName() override { return "TV"; }
};

class Radio : public Device {
private:
    bool on = false;
    int volume = 15;
public:
    bool isEnabled() override { return on; }
    void enable() override { on = true; std::cout << "📻 Radio: Powered ON.\n"; }
    void disable() override { on = false; std::cout << "📻 Radio: Powered OFF.\n"; }
    void setVolume(int percent) override { 
        volume = percent; 
        std::cout << "📻 Radio: Volume set to " << volume << "%.\n"; 
    }
    std::string getName() override { return "Radio"; }
};

// 3. Abstraction: Remote Control (holds a bridge link to Device)
class RemoteControl {
protected:
    std::shared_ptr<Device> device; // The Bridge Link
public:
    RemoteControl(std::shared_ptr<Device> dev) : device(dev) {}
    virtual ~RemoteControl() = default;

    void togglePower() {
        std::cout << "🎛️ Remote: Pressing Power Button...\n";
        if (device->isEnabled()) {
            device->disable();
        } else {
            device->enable();
        }
    }

    void volumeUp() {
        std::cout << "🎛️ Remote: Pressing Volume Up...\n";
        device->setVolume(50);
    }
};

// 4. Refined Abstraction: Advanced Remote (adds new features without changing device classes)
class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(std::shared_ptr<Device> dev) : RemoteControl(dev) {}

    void mute() {
        std::cout << "🎛️ Advanced Remote: Pressing Mute Button...\n";
        device->setVolume(0);
    }
};

// Client Code
int main() {
    std::cout << "--- Testing Bridge Pattern with TV and Basic Remote ---\n";
    auto tv = std::make_shared<TV>();
    RemoteControl basicRemote(tv);
    basicRemote.togglePower();
    basicRemote.volumeUp();

    std::cout << "\n--- Testing Bridge Pattern with Radio and Advanced Remote ---\n";
    auto radio = std::make_shared<Radio>();
    AdvancedRemoteControl advancedRemote(radio);
    advancedRemote.togglePower();
    advancedRemote.mute();

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Testing Bridge Pattern with TV and Basic Remote ---
🎛️ Remote: Pressing Power Button...
📺 TV: Powered ON.
🎛️ Remote: Pressing Volume Up...
📺 TV: Volume set to 50%.

--- Testing Bridge Pattern with Radio and Advanced Remote ---
🎛️ Remote: Pressing Power Button...
📻 Radio: Powered ON.
🎛️ Advanced Remote: Pressing Mute Button...
📻 Radio: Volume set to 0%.
```

---

## 8. Composite Pattern
**Intent:** Compose objects into tree structures to represent part-whole hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Computer File System**:
- A file system has **Files** (Leaf nodes) and **Directories** (Composite nodes).
- A Directory can contain Files AND other Directories.
- Both Files and Directories share a common component interface (e.g., `print()` or `getSize()`). This allows the client to trigger `print()` on the root directory and print the entire tree structure recursively, treating a single file and a collection of files identically.

```text
               [ Component (Node) ]
               /                  \
              v                    v
      [ Leaf (File) ]       [ Composite (Directory) ]
                             /          |          \
                            v           v           v
                        [ File ]    [ File ]   [ Sub-Directory ]
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// 1. Component: Common interface for both Leaf and Composite
class FileSystemNode {
public:
    virtual ~FileSystemNode() = default;
    virtual void print(int indent = 0) = 0;
};

// 2. Leaf: Represents individual files (no children)
class File : public FileSystemNode {
private:
    std::string name;
public:
    File(const std::string& n) : name(n) {}
    
    void print(int indent = 0) override {
        std::cout << std::string(indent, ' ') << "📄 File: " << name << "\n";
    }
};

// 3. Composite: Represents directories (can contain files and/or other directories)
class Directory : public FileSystemNode {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemNode>> children;
public:
    Directory(const std::string& n) : name(n) {}

    void add(std::shared_ptr<FileSystemNode> node) {
        children.push_back(node);
    }

    void print(int indent = 0) override {
        std::cout << std::string(indent, ' ') << "📁 Directory: " << name << "\n";
        for (const auto& child : children) {
            child->print(indent + 4); // Recursive call to child nodes
        }
    }
};

// Client Code
int main() {
    std::cout << "--- Creating Directory Structure ---\n";
    
    // Create root directory
    auto root = std::make_shared<Directory>("Root");

    // Create files
    auto file1 = std::make_shared<File>("Readme.md");
    auto file2 = std::make_shared<File>("Main.cpp");

    // Add files to root
    root->add(file1);
    root->add(file2);

    // Create sub-directory and add a file
    auto srcFolder = std::make_shared<Directory>("src");
    auto headerFile = std::make_shared<File>("Header.h");
    srcFolder->add(headerFile);

    // Nest sub-directory into root directory
    root->add(srcFolder);

    // Print the entire structure recursively
    root->print();

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Creating Directory Structure ---
📁 Directory: Root
    📄 File: Readme.md
    📄 File: Main.cpp
    📁 Directory: src
        📄 File: Header.h
```

---

## 9. Decorator Pattern ✅
*(Current Chapter)*

### Problem
We want to add capabilities to objects at runtime (e.g., adding visual effects, metrics trackers, logging, or camera pipelines) without inheritance. Using inheritance results in static subclasses and **class explosion** (e.g., `SimpleCoffee`, `CoffeeWithMilk`, `CoffeeWithSugar`, `CoffeeWithMilkAndSugar`).

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Cup of Espresso** and **Toppings**:
- You start with a base coffee (`Espresso`).
- Instead of creating subclasses for every recipe combination, you wrap the Espresso dynamically in condiment wrappers (`Milk`, `Mocha`).
- Each condiment wraps the inner coffee object, adding to its description and cost, then delegating the rest to the inner component.

```text
           [ Mocha Decorator ]   --> Cost: +$0.20
                 |
                 v wraps
           [ Milk Decorator ]    --> Cost: +$0.50
                 |
                 v wraps
           [ Espresso Base ]     --> Cost: $1.99
```

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

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <string>
#include <memory>

// 1. Abstract Component Interface
class Beverage {
public:
    virtual ~Beverage() = default;
    virtual std::string getDescription() = 0;
    virtual double cost() = 0;
};

// 2. Concrete Component
class Espresso : public Beverage {
public:
    std::string getDescription() override { return "Espresso"; }
    double cost() override { return 1.99; }
};

// 3. Decorator Base Class (implements Beverage, wraps another Beverage)
class CondimentDecorator : public Beverage {
protected:
    std::shared_ptr<Beverage> beverage; // Wrapped component
public:
    CondimentDecorator(std::shared_ptr<Beverage> b) : beverage(b) {}
};

// 4. Concrete Decorators
class Milk : public CondimentDecorator {
public:
    Milk(std::shared_ptr<Beverage> b) : CondimentDecorator(b) {}
    
    std::string getDescription() override { 
        return beverage->getDescription() + ", Milk"; 
    }
    
    double cost() override { 
        return beverage->cost() + 0.50; 
    }
};

class Mocha : public CondimentDecorator {
public:
    Mocha(std::shared_ptr<Beverage> b) : CondimentDecorator(b) {}
    
    std::string getDescription() override { 
        return beverage->getDescription() + ", Mocha"; 
    }
    
    double cost() override { 
        return beverage->cost() + 0.20; 
    }
};

// Client Code
int main() {
    std::cout << "--- Ordering Drinks ---\n";

    // Step 1: Order a plain Espresso
    std::shared_ptr<Beverage> drink1 = std::make_shared<Espresso>();
    std::cout << drink1->getDescription() << " | Cost: $" << drink1->cost() << "\n";

    // Step 2: Decorate the Espresso with Milk
    std::shared_ptr<Beverage> drink2 = std::make_shared<Milk>(drink1);
    std::cout << drink2->getDescription() << " | Cost: $" << drink2->cost() << "\n";

    // Step 3: Decorate the drink again with Mocha
    std::shared_ptr<Beverage> drink3 = std::make_shared<Mocha>(drink2);
    std::cout << drink3->getDescription() << " | Cost: $" << drink3->cost() << "\n";

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Ordering Drinks ---
Espresso | Cost: $1.99
Espresso, Milk | Cost: $2.49
Espresso, Milk, Mocha | Cost: $2.69
```

---

## 10. Facade Pattern
**Intent:** Provide a unified interface to a set of interfaces in a subsystem. Facade defines a higher-level interface that makes the subsystem easier to use.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Customer Service Representative**:
- When placing a product order, you don't call the Warehouse department to check stock, the Billing department to charge your card, and the Shipping department to track delivery.
- You talk only to a **Representative (Facade)** who handles the complex coordination with all departments behind the scenes.

```text
                     [ Facade (Customer Service) ]
                        /          |          \
                       v           v           v
                 [ Warehouse ] [ Billing ] [ Shipping ]
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <string>

// Subsystem 1: Warehouse
class Warehouse {
public:
    bool isAvailable(const std::string& item) {
        std::cout << "📦 Warehouse: Checking availability for " << item << "... Available!\n";
        return true;
    }
};

// Subsystem 2: Billing
class Billing {
public:
    void processPayment(double amount) {
        std::cout << "💳 Billing: Processing payment of $" << amount << "... Success!\n";
    }
};

// Subsystem 3: Shipping
class Shipping {
public:
    void shipProduct(const std::string& item) {
        std::cout << "🚚 Shipping: Dispatching " << item << " for delivery!\n";
    }
};

// Facade: Unified entry point
class OrderFacade {
private:
    Warehouse warehouse;
    Billing billing;
    Shipping shipping;
public:
    void placeOrder(const std::string& item, double price) {
        std::cout << "🛒 Facade: Starting checkout process for " << item << "\n";
        if (warehouse.isAvailable(item)) {
            billing.processPayment(price);
            shipping.shipProduct(item);
            std::cout << "🎉 Facade: Order completed successfully!\n";
        }
    }
};

// Client Code
int main() {
    OrderFacade orderFacade;
    orderFacade.placeOrder("Gaming Laptop", 1299.99);
    return 0;
}
```

### 📋 Expected Console Output
```text
🛒 Facade: Starting checkout process for Gaming Laptop
📦 Warehouse: Checking availability for Gaming Laptop... Available!
💳 Billing: Processing payment of $1299.99... Success!
🚚 Shipping: Dispatching Gaming Laptop for delivery!
🎉 Facade: Order completed successfully!
```

---

## 11. Flyweight Pattern
**Intent:** Use sharing to support large numbers of fine-grained objects efficiently.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Forest in a Video Game**:
- A forest contains 10,000 tree objects.
- Each tree has heavy 3D model data, leaves meshes, and high-res textures. Instantiating 10,000 heavy tree objects will exhaust system RAM (Intrinsic state: shared).
- Instead, you create a single heavy `TreeType` object (Flyweight) containing the model/textures.
- Then, you create 10,000 lightweight `Tree` objects containing only their coordinates `(x, y)` (Extrinsic state: unique) and a reference to the single shared `TreeType` object.

```text
  [ Shared TreeType (Flyweight) ]  <=== holds 3D mesh & texture data (10 MB)
            ^              ^
            | references   |
  [ Tree 1 (x: 10, y: 20) ] [ Tree 2 (x: 45, y: 80) ] <=== lightweight objects (16 bytes each)
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

// 1. Flyweight: Intrinsic State (shared, heavy data)
class TreeType {
private:
    std::string name;
    std::string color;
    std::string texture; // Simulating heavy texture data
public:
    TreeType(const std::string& n, const std::string& c, const std::string& t) 
        : name(n), color(c), texture(t) {}
        
    void draw(int x, int y) {
        std::cout << "Drawing tree of type [" << name << " (" << color 
                  << ")] at coordinate (" << x << ", " << y << ")\n";
    }
};

// 2. Flyweight Factory: Manages flyweight instances, ensuring uniqueness
class TreeFactory {
private:
    static std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes;
public:
    static std::shared_ptr<TreeType> getTreeType(const std::string& name, const std::string& color, const std::string& texture) {
        std::string key = name + "_" + color + "_" + texture;
        if (treeTypes.find(key) == treeTypes.end()) {
            std::cout << "Creating NEW TreeType: [" << name << "]\n";
            treeTypes[key] = std::make_shared<TreeType>(name, color, texture);
        }
        return treeTypes[key];
    }
};
std::unordered_map<std::string, std::shared_ptr<TreeType>> TreeFactory::treeTypes;

// 3. Client Context: Extrinsic State (unique coordinates, references flyweight)
class Tree {
private:
    int x;
    int y;
    std::shared_ptr<TreeType> type; // Reference to shared flyweight
public:
    Tree(int x_coord, int y_coord, std::shared_ptr<TreeType> t) 
        : x(x_coord), y(y_coord), type(t) {}
        
    void draw() {
        type->draw(x, y);
    }
};

// Client Code
int main() {
    std::cout << "--- Creating a Forest (Flyweight) ---\n";
    std::vector<Tree> forest;

    // Get tree types (reused if identical)
    auto oakType = TreeFactory::getTreeType("Oak", "Green", "OakTexture.png");
    auto pineType = TreeFactory::getTreeType("Pine", "Dark Green", "PineTexture.png");
    auto oakTypeReused = TreeFactory::getTreeType("Oak", "Green", "OakTexture.png"); // Reused!

    // Plant trees
    forest.push_back(Tree(10, 20, oakType));
    forest.push_back(Tree(15, 25, oakTypeReused));
    forest.push_back(Tree(50, 60, pineType));

    // Render forest
    for (auto& tree : forest) {
        tree.draw();
    }

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Creating a Forest (Flyweight) ---
Creating NEW TreeType: [Oak]
Creating NEW TreeType: [Pine]
Drawing tree of type [Oak (Green)] at coordinate (10, 20)
Drawing tree of type [Oak (Green)] at coordinate (15, 25)
Drawing tree of type [Pine (Dark Green)] at coordinate (50, 60)
```

---

## 12. Proxy Pattern
**Intent:** Provide a surrogate or placeholder for another object to control access to it.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Credit Card**:
- A Credit Card acts as a **Proxy** for a physical Bank Account (Real Subject).
- Instead of carrying and handing over a chest of cash (heavy/insecure real subject), you present your Credit Card.
- The card intercepts calls (validates transaction limits, confirms security code) and forwards the valid payment instructions to the bank account.

```text
  [ Client ] ---> [ Proxy (Credit Card) ] -- Access Check/Lazy Load --> [ Real Subject (Bank Account) ]
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <string>
#include <memory>

// 1. Subject Interface
class Internet {
public:
    virtual ~Internet() = default;
    virtual void connectTo(const std::string& serverHost) = 0;
};

// 2. Real Subject
class RealInternet : public Internet {
public:
    void connectTo(const std::string& serverHost) override {
        std::cout << "🌐 Connecting to " << serverHost << "...\n";
    }
};

// 3. Proxy: Intercepts connection requests and checks security rules
class ProxyInternet : public Internet {
private:
    std::shared_ptr<RealInternet> realInternet;
public:
    ProxyInternet() : realInternet(std::make_shared<RealInternet>()) {}

    void connectTo(const std::string& serverHost) override {
        // Simple access control rules
        if (serverHost == "restricted-site.com" || serverHost == "blocked.org") {
            std::cout << "❌ Proxy: Access to " << serverHost << " is DENIED!\n";
        } else {
            realInternet->connectTo(serverHost); // Delegate to real subject
        }
    }
};

// Client Code
int main() {
    std::cout << "--- Testing Proxy Internet Connection ---\n";
    std::unique_ptr<Internet> internet = std::make_unique<ProxyInternet>();

    internet->connectTo("google.com");
    internet->connectTo("restricted-site.com");

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Testing Proxy Internet Connection ---
🌐 Connecting to google.com...
❌ Proxy: Access to restricted-site.com is DENIED!
```

---

# Part 4 - Behavioral Patterns (11)

## 13. Chain of Responsibility
**Intent:** Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Support Ticket Escalation System**:
- You submit a tech support request.
- First, **Level 1 Support** (first handler) receives it. If it is a simple password reset, they handle it.
- If it is a database error, they can't handle it, so they pass it to **Level 2 Support** (next link in the chain).
- The request continues down the chain until a support engineer handles it or it reaches the end.

```text
  [ Client Request ] ---> [ Level 1 Support ] --- (cannot handle) ---> [ Level 2 Support ] --- (cannot handle) ---> [ Level 3 Support ] (Resolved!)
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <string>
#include <memory>

// Abstract Handler
class SupportHandler {
protected:
    std::shared_ptr<SupportHandler> nextHandler;
public:
    virtual ~SupportHandler() = default;
    void setNext(std::shared_ptr<SupportHandler> next) { nextHandler = next; }

    virtual void handleRequest(const std::string& issue, int severity) {
        if (nextHandler) {
            nextHandler->handleRequest(issue, severity);
        } else {
            std::cout << "❌ No handler found for issue: " << issue << "\n";
        }
    }
};

// Concrete Handler 1: Level 1 Support (Handles low severity)
class Level1Support : public SupportHandler {
public:
    void handleRequest(const std::string& issue, int severity) override {
        if (severity <= 1) {
            std::cout << "✅ Level 1 Support resolved issue: [" << issue << "]\n";
        } else {
            std::cout << "⏭️ Level 1 Support: Escalating issue...\n";
            SupportHandler::handleRequest(issue, severity); // Pass down the chain
        }
    }
};

// Concrete Handler 2: Level 2 Support (Handles medium severity)
class Level2Support : public SupportHandler {
public:
    void handleRequest(const std::string& issue, int severity) override {
        if (severity <= 2) {
            std::cout << "✅ Level 2 Support resolved issue: [" << issue << "]\n";
        } else {
            std::cout << "⏭️ Level 2 Support: Escalating issue...\n";
            SupportHandler::handleRequest(issue, severity); // Pass down the chain
        }
    }
};

// Client Code
int main() {
    std::cout << "--- Chain of Responsibility: Tech Support ---\n";
    
    // Create chain links
    auto level1 = std::make_shared<Level1Support>();
    auto level2 = std::make_shared<Level2Support>();

    // Link the chain: Level 1 -> Level 2
    level1->setNext(level2);

    std::cout << "Client submits: Simple password reset (Severity 1)\n";
    level1->handleRequest("Reset Password", 1);

    std::cout << "\nClient submits: Database backup failure (Severity 2)\n";
    level1->handleRequest("DB Backup Fail", 2);

    std::cout << "\nClient submits: Core server crash (Severity 3)\n";
    level1->handleRequest("Server Crash", 3);

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Chain of Responsibility: Tech Support ---
Client submits: Simple password reset (Severity 1)
✅ Level 1 Support resolved issue: [Reset Password]

Client submits: Database backup failure (Severity 2)
⏭️ Level 1 Support: Escalating issue...
✅ Level 2 Support resolved issue: [DB Backup Fail]

Client submits: Core server crash (Severity 3)
⏭️ Level 1 Support: Escalating issue...
⏭️ Level 2 Support: Escalating issue...
❌ No handler found for issue: Server Crash
```

---

## 14. Command Pattern
**Intent:** Encapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undoable operations.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Restaurant Order Slip**:
- You (Client) tell the Waiter (Invoker) your order.
- The Waiter writes your order on an **Order Slip (Command)** and pins it in the kitchen.
- The Chef (Receiver) reads the slip and cooks the meal.
- The Waiter doesn't need to know how to cook; the Chef doesn't need to know which customer ordered. The Order Slip encapsulates the request completely.

```text
  [ Customer (Client) ] ---> creates Order ---> [ Waiter (Invoker) ] ---> executes Order slip ---> [ Chef (Receiver) ]
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>
#include <vector>

// 1. Receiver: Knows how to perform the actual action
class Light {
public:
    void turnOn() { std::cout << "💡 Light: Powered ON.\n"; }
    void turnOff() { std::cout << "🔌 Light: Powered OFF.\n"; }
};

// 2. Command Interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// 3. Concrete Command
class LightOnCommand : public Command {
private:
    std::shared_ptr<Light> light; // Receiver reference
public:
    LightOnCommand(std::shared_ptr<Light> l) : light(l) {}

    void execute() override { light->turnOn(); }
    void undo() override { light->turnOff(); }
};

// 4. Invoker: Asks the command to carry out the request
class RemoteControl {
private:
    std::shared_ptr<Command> command;
public:
    void setCommand(std::shared_ptr<Command> cmd) { command = cmd; }
    
    void pressButton() {
        std::cout << "🎛️ Remote: Pressing Execute Button...\n";
        command->execute();
    }
    
    void pressUndo() {
        std::cout << "🎛️ Remote: Pressing Undo Button...\n";
        command->undo();
    }
};

// Client Code
int main() {
    std::cout << "--- Command Pattern Demo ---\n";
    auto livingRoomLight = std::make_shared<Light>();
    
    // Create the command wrapping the receiver
    auto lightOn = std::make_shared<LightOnCommand>(livingRoomLight);

    // Set the command inside the invoker
    RemoteControl remote;
    remote.setCommand(lightOn);

    // Trigger actions
    remote.pressButton();
    remote.pressUndo();

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Command Pattern Demo ---
🎛️ Remote: Pressing Execute Button...
💡 Light: Powered ON.
🎛️ Remote: Pressing Undo Button...
🔌 Light: Powered OFF.
```

---

## 15. Interpreter Pattern
**Intent:** Given a language, define a representation for its grammar along with an interpreter that uses the representation to interpret sentences in the language.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Math Expression Evaluator**:
- You have a math expression like `5 + 2`.
- You break it into components: the numbers `5` and `2` (Terminal Expressions) and the operator `+` (Non-terminal Expression).
- The interpreter evaluates each node to compute the final result.

```text
  [ Expression: "5 + 2" ] ---> [ Interpreter ] ---> [ Evaluated Result: 7 ]
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>
#include <string>

// Abstract Expression
class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret() = 0;
};

// Terminal Expression: Represents numbers
class NumberExpression : public Expression {
private:
    int number;
public:
    NumberExpression(int num) : number(num) {}
    int interpret() override { return number; }
};

// Non-Terminal Expression: Represents addition operation (+)
class AddExpression : public Expression {
private:
    std::shared_ptr<Expression> leftExpression;
    std::shared_ptr<Expression> rightExpression;
public:
    AddExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) 
        : leftExpression(left), rightExpression(right) {}

    int interpret() override {
        return leftExpression->interpret() + rightExpression->interpret();
    }
};

// Client Code
int main() {
    std::cout << "--- Interpreter Pattern: Evaluating Expression (5 + 10) ---\n";

    // Setup syntax tree: 5 + 10
    auto expr1 = std::make_shared<NumberExpression>(5);
    auto expr2 = std::make_shared<NumberExpression>(10);
    auto sum = std::make_shared<AddExpression>(expr1, expr2);

    // Interpret the tree
    int result = sum->interpret();
    std::cout << "Result: " << result << "\n";

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Interpreter Pattern: Evaluating Expression (5 + 10) ---
Result: 15
```

---

## 16. Iterator Pattern
**Intent:** Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **TV Remote Control Channel Surfer**:
- You have a collection of TV channels.
- You don't need to know how the TV tuner stores channels (array, linked list, hash map).
- You just use the **Next (Iterator)** button on the remote to go to the next channel sequentially.

```text
  [ Channel Collection ] <================= has iterator
            |                                     |
  [ TV Tuner internal details ]        [ Remote Channel Up/Down (Iterator) ] ---> next(), hasNext()
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Iterator Interface
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual std::string next() = 0;
};

// Concrete Iterator for TV Channel Collection
class ChannelIterator : public Iterator {
private:
    std::vector<std::string> channels;
    size_t position = 0;
public:
    ChannelIterator(const std::vector<std::string>& list) : channels(list) {}

    bool hasNext() override {
        return position < channels.size();
    }

    std::string next() override {
        return channels[position++];
    }
};

// Aggregate Interface
class ChannelCollection {
public:
    virtual ~ChannelCollection() = default;
    virtual std::unique_ptr<Iterator> createIterator() = 0;
};

// Concrete Aggregate
class TVChannels : public ChannelCollection {
private:
    std::vector<std::string> channelsList;
public:
    void addChannel(const std::string& ch) { channelsList.push_back(ch); }

    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<ChannelIterator>(channelsList);
    }
};

// Client Code
int main() {
    std::cout << "--- Iterator Pattern: Surfing Channels ---\n";
    TVChannels tv;
    tv.addChannel("Sports Channel");
    tv.addChannel("News Channel");
    tv.addChannel("Movie Channel");

    // Use Iterator to traverse without exposing list representation
    auto iterator = tv.createIterator();
    while (iterator->hasNext()) {
        std::cout << "📺 Playing: " << iterator->next() << "\n";
    }

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Iterator Pattern: Surfing Channels ---
📺 Playing: Sports Channel
📺 Playing: News Channel
📺 Playing: Movie Channel
```

---

## 17. Mediator Pattern
**Intent:** Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping objects from referring to each other explicitly, letting you vary their interaction independently.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of an **Airport Air Traffic Control (ATC) Tower**:
- Airplanes landing at an airport do not coordinate directly with each other (which would lead to chaos).
- Instead, each plane talks only to the **ATC Tower (Mediator)**.
- The ATC Tower determines flight schedules and safety coordinates, instructing each plane individually when to land or take off.

```text
   [ Airplane A ] <----\             /----> [ Airplane B ]
                        v           v
                     [ ATC Tower (Mediator) ]
                        ^           ^
   [ Airplane C ] <----/             \----> [ Airplane D ]
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Plane; // Forward declaration

// Mediator Interface
class ATCTower {
public:
    virtual ~ATCTower() = default;
    virtual void registerPlane(std::shared_ptr<Plane> plane) = 0;
    virtual void sendMessage(const std::string& msg, std::shared_ptr<Plane> sender) = 0;
};

// Colleague class
class Plane : public std::enable_shared_from_this<Plane> {
protected:
    std::shared_ptr<ATCTower> atc;
    std::string flightNumber;
public:
    Plane(std::shared_ptr<ATCTower> tower, const std::string& id) : atc(tower), flightNumber(id) {}
    virtual ~Plane() = default;

    std::string getFlightNumber() const { return flightNumber; }

    void send(const std::string& msg) {
        std::cout << "✈️ " << flightNumber << " sends request: \"" << msg << "\"\n";
        atc->sendMessage(msg, shared_from_this());
    }

    void receive(const std::string& msg) {
        std::cout << "✈️ " << flightNumber << " received instructions: \"" << msg << "\"\n";
    }
};

// Concrete Mediator
class HeathrowATC : public ATCTower {
private:
    std::vector<std::shared_ptr<Plane>> planes;
public:
    void registerPlane(std::shared_ptr<Plane> plane) override {
        planes.push_back(plane);
    }

    void sendMessage(const std::string& msg, std::shared_ptr<Plane> sender) override {
        for (const auto& plane : planes) {
            // Send instructions to everyone EXCEPT the sender
            if (plane != sender) {
                plane->receive(sender->getFlightNumber() + " -> " + msg);
            }
        }
    }
};

// Client Code
int main() {
    std::cout << "--- Air Traffic Control (Mediator) ---\n";
    auto atc = std::make_shared<HeathrowATC>();

    auto flight1 = std::make_shared<Plane>(atc, "Flight AA101");
    auto flight2 = std::make_shared<Plane>(atc, "Flight BA202");
    
    atc->registerPlane(flight1);
    atc->registerPlane(flight2);

    // Communication is centralized through the Mediator (ATC)
    flight1->send("Ready to land on Runway 1.");
    
    return 0;
}
```

### 📋 Expected Console Output
```text
--- Air Traffic Control (Mediator) ---
✈️ Flight AA101 sends request: "Ready to land on Runway 1."
✈️ Flight BA202 received instructions: "Flight AA101 -> Ready to land on Runway 1."
```

---

## 18. Memento Pattern
**Intent:** Without violating encapsulation, capture and externalize an object's internal state so that the object can be restored to this state later.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Video Game Save State**:
- You are about to fight a dangerous game boss.
- You create a **Save State (Memento)** containing your health points and score.
- The save state is saved on your hard drive (Caretaker).
- If your character dies, you load the save state to restore the player's status (Originator) back to the exact saved state.

```text
  [ Player (Originator) ] === save() ===> [ SaveState (Memento) ] === stored in ===> [ GameSystem (Caretaker) ]
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <string>
#include <memory>
#include <vector>

// 1. Memento: Stores the saved state
class Memento {
private:
    std::string textState;
public:
    Memento(const std::string& state) : textState(state) {}
    std::string getSavedState() const { return textState; }
};

// 2. Originator: The active object whose state needs saving/restoration
class TextEditor {
private:
    std::string text;
public:
    void write(const std::string& t) { text += t; }
    
    void show() { std::cout << "📝 Editor Content: \"" << text << "\"\n"; }

    // Save state into Memento
    std::shared_ptr<Memento> save() {
        return std::make_shared<Memento>(text);
    }

    // Restore state from Memento
    void restore(std::shared_ptr<Memento> memento) {
        text = memento->getSavedState();
    }
};

// 3. Caretaker: Manages and keeps track of memento history (does not inspect memento contents)
class History {
private:
    std::vector<std::shared_ptr<Memento>> undoStack;
public:
    void push(std::shared_ptr<Memento> m) { undoStack.push_back(m); }
    
    std::shared_ptr<Memento> pop() {
        if (undoStack.empty()) return nullptr;
        auto m = undoStack.back();
        undoStack.pop_back();
        return m;
    }
};

// Client Code
int main() {
    std::cout << "--- Text Editor with Undo History ---\n";
    TextEditor editor;
    History history;

    // User types text
    editor.write("Hello ");
    editor.show();
    history.push(editor.save()); // Save checkpoint

    // User types more text
    editor.write("World!");
    editor.show();
    
    // User performs undo
    std::cout << "⏮️ Triggering Undo...\n";
    auto previousState = history.pop();
    if (previousState) {
        editor.restore(previousState);
    }
    
    editor.show();
    return 0;
}
```

### 📋 Expected Console Output
```text
--- Text Editor with Undo History ---
📝 Editor Content: "Hello "
📝 Editor Content: "Hello World!"
⏮️ Triggering Undo...
📝 Editor Content: "Hello "
```

---

## 19. Observer Pattern
**Intent:** Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Newsletter Subscription**:
- A publisher prints a weekly tech newsletter.
- Readers (Observers) subscribe to the newsletter publisher (Subject).
- When a new edition is ready, the publisher automatically sends it to all active subscribers. The publisher doesn't care who they are as long as they are on the mailing list.

```text
                           +------------------------+
                           |  Publisher (Subject)   |
                           +-----------+------------+
                                       |
                   notify()            |  Notifies on state change
       +-------------------------------+-------------------------------+
       |                               |                               |
       v                               v                               v
+------+------+                 +------+------+                 +------+------+
| Subscriber  |                 | Subscriber  |                 | Subscriber  |
| (Observer)  |                 | (Observer)  |                 | (Observer)  |
+-------------+                 +-------------+                 +-------------+
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

// 1. Observer Interface
class Subscriber {
public:
    virtual ~Subscriber() = default;
    virtual void update(const std::string& article) = 0;
};

// 2. Concrete Observer
class Reader : public Subscriber {
private:
    std::string name;
public:
    Reader(const std::string& n) : name(n) {}

    void update(const std::string& article) override {
        std::cout << "📬 Reader [" << name << "] received new article: \"" << article << "\"\n";
    }
};

// 3. Subject (Observable)
class Newsletter {
private:
    std::vector<std::shared_ptr<Subscriber>> subscribers;
public:
    void subscribe(std::shared_ptr<Subscriber> s) {
        subscribers.push_back(s);
    }

    void unsubscribe(std::shared_ptr<Subscriber> s) {
        subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), s), subscribers.end());
    }

    void publishNewArticle(const std::string& title) {
        std::cout << "✍️ Publisher published: \"" << title << "\"\n";
        for (const auto& sub : subscribers) {
            sub->update(title); // Notify observers
        }
    }
};

// Client Code
int main() {
    std::cout << "--- Observer Pattern Newsletter System ---\n";
    Newsletter techWeekly;

    // Create subscribers
    auto reader1 = std::make_shared<Reader>("Alice");
    auto reader2 = std::make_shared<Reader>("Bob");

    // Register observers
    techWeekly.subscribe(reader1);
    techWeekly.subscribe(reader2);

    // Notify observers
    techWeekly.publishNewArticle("Mastering Design Patterns in C++!");

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Observer Pattern Newsletter System ---
✍️ Publisher published: "Mastering Design Patterns in C++!"
📬 Reader [Alice] received new article: "Mastering Design Patterns in C++!"
📬 Reader [Bob] received new article: "Mastering Design Patterns in C++!"
```

---

## 20. State Pattern
**Intent:** Allow an object to alter its behavior when its internal state changes. The object will appear to change its class.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Vending Machine**:
- A vending machine behaves differently based on its current state.
- **No Coin state:** Pressing the dispenser button gives an error ("Please insert coin").
- **Has Coin state:** Pressing the dispenser button drops a soda and transitions state to **No Coin**.
- **Sold Out state:** Inserting a coin rejects the coin immediately.

```text
        +-------------------------------------------------+
        |                    Context                      |
        |            (Vending Machine State)              |
        +-----------------------+-------------------------+
                                |
                                v
      +-------------------------+-------------------------+
      |        State Interfaces & Concrete States        |
      |   [No Coin] <---> [Has Coin] <---> [Dispensing]   |
      +---------------------------------------------------+
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>

class VendingMachine; // Forward declaration

// Abstract State
class State {
public:
    virtual ~State() = default;
    virtual void insertCoin(VendingMachine& machine) = 0;
    virtual void dispense(VendingMachine& machine) = 0;
};

// VendingMachine Context
class VendingMachine {
private:
    std::shared_ptr<State> currentState;
public:
    VendingMachine(std::shared_ptr<State> initialState) : currentState(initialState) {}

    void setState(std::shared_ptr<State> state) { currentState = state; }

    void insertCoin() { currentState->insertCoin(*this); }
    void pressDispenseButton() { currentState->dispense(*this); }
};

// Concrete State: No Coin State
class NoCoinState : public State {
public:
    void insertCoin(VendingMachine& machine) override; // Defined below
    void dispense(VendingMachine& machine) override {
        std::cout << "❌ Machine: Please insert a coin first!\n";
    }
};

// Concrete State: Has Coin State
class HasCoinState : public State {
public:
    void insertCoin(VendingMachine& machine) override {
        std::cout << "⚠️ Machine: Coin already inserted!\n";
    }
    void dispense(VendingMachine& machine) override; // Defined below
};

// State Transition Definitions
void NoCoinState::insertCoin(VendingMachine& machine) {
    std::cout << "🪙 Machine: Coin inserted successfully.\n";
    machine.setState(std::make_shared<HasCoinState>()); // Change state
}

void HasCoinState::dispense(VendingMachine& machine) {
    std::cout << "🥤 Machine: Dispensing cold soda!\n";
    machine.setState(std::make_shared<NoCoinState>()); // Revert state
}

// Client Code
int main() {
    std::cout << "--- Vending Machine State Demo ---\n";
    
    // Start machine in NoCoinState
    VendingMachine machine(std::make_shared<NoCoinState>());

    // Test actions
    machine.pressDispenseButton();
    machine.insertCoin();
    machine.pressDispenseButton();
    
    return 0;
}
```

### 📋 Expected Console Output
```text
--- Vending Machine State Demo ---
❌ Machine: Please insert a coin first!
🪙 Machine: Coin inserted successfully.
🥤 Machine: Dispensing cold soda!
```

---

## 21. Strategy Pattern
**Intent:** Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of **Google Maps Travel Route**:
- You want to travel from your house to the airport.
- You can select different route calculation algorithms **(Strategies)**:
  - **Driving Strategy:** Finds high-speed highways.
  - **Walking Strategy:** Finds pedestrian sidewalks.
  - **Public Transit Strategy:** Synchronizes bus schedules.
- The Maps app (Context) switches strategies dynamically based on your select choice.

```text
                     [ Navigation App (Context) ]
                                  |
               uses strategy      |  (Interchangeable at runtime)
                                  v
                    [ Route Strategy (Interface) ]
                   /              |               \
                  v               v                v
         [ Road Strategy ] [ Walk Strategy ] [ Public Transit Strategy ]
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>
#include <string>

// 1. Strategy Interface
class RouteStrategy {
public:
    virtual ~RouteStrategy() = default;
    virtual void buildRoute(const std::string& start, const std::string& end) = 0;
};

// 2. Concrete Strategies
class DrivingStrategy : public RouteStrategy {
public:
    void buildRoute(const std::string& start, const std::string& end) override {
        std::cout << "🚗 Drive Route: Take highway from " << start << " to " << end << ". (Fastest)\n";
    }
};

class WalkingStrategy : public RouteStrategy {
public:
    void buildRoute(const std::string& start, const std::string& end) override {
        std::cout << "🥾 Walking Route: Take sidewalks from " << start << " to " << end << ". (Scenic)\n";
    }
};

// 3. Context
class NavigationApp {
private:
    std::shared_ptr<RouteStrategy> routeStrategy;
public:
    void setStrategy(std::shared_ptr<RouteStrategy> strategy) {
        routeStrategy = strategy;
    }

    void navigate(const std::string& from, const std::string& to) {
        if (routeStrategy) {
            routeStrategy->buildRoute(from, to);
        } else {
            std::cout << "❌ Navigation: Strategy not selected!\n";
        }
    }
};

// Client Code
int main() {
    std::cout << "--- Google Maps Navigation ---\n";
    NavigationApp app;

    // Use Driving strategy
    app.setStrategy(std::make_shared<DrivingStrategy>());
    app.navigate("Home", "Airport");

    // User switches to Walking route
    std::cout << "\nUser switches to walking mode...\n";
    app.setStrategy(std::make_shared<WalkingStrategy>());
    app.navigate("Home", "Airport");

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Google Maps Navigation ---
🚗 Drive Route: Take highway from Home to Airport. (Fastest)

User switches to walking mode...
🥾 Walking Route: Take sidewalks from Home to Airport. (Scenic)
```

---

## 22. Template Method Pattern
**Intent:** Define the skeleton of an algorithm in an operation, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of **Brewing Hot Drinks (Tea / Coffee)**:
- The steps to brew a hot beverage are identical:
  1. Boil water.
  2. Brew key ingredient.
  3. Pour drink in cup.
  4. Add condiments.
- The base class defines the skeleton algorithm template. Subclasses simply override step 2 and step 4 to implement coffee-specific or tea-specific behaviors.

```text
  [ Abstract Beverage Maker ] (Template: Boil Water -> Brew -> Pour -> Add Toppings)
             /              \
            v                v
     [ Coffee Maker ]    [ Tea Maker ]
     (Brews Coffee)      (Brews Tea Leaves)
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>

// Base Template Class
class BeverageTemplate {
private:
    void boilWater() { std::cout << "💧 Step 1: Boiling water...\n"; }
    void pourInCup() { std::cout << "☕ Step 3: Pouring into cup...\n"; }

protected:
    // Subclasses must implement these steps
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

public:
    virtual ~BeverageTemplate() = default;

    // The Template Method: Defines skeleton sequence
    void prepareBeverage() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
        std::cout << "🎉 Beverage is ready!\n";
    }
};

// Concrete Implementation 1: Coffee
class CoffeeMaker : public BeverageTemplate {
protected:
    void brew() override {
        std::cout << "🫘 Step 2: Brewing fine coffee beans...\n";
    }
    void addCondiments() override {
        std::cout << "🥛 Step 4: Adding milk and sugar...\n";
    }
};

// Concrete Implementation 2: Tea
class TeaMaker : public BeverageTemplate {
protected:
    void brew() override {
        std::cout << "🍃 Step 2: Steeping tea leaves in water...\n";
    }
    void addCondiments() override {
        std::cout << "🍋 Step 4: Adding lemon slices...\n";
    }
};

// Client Code
int main() {
    std::cout << "--- Brewing Coffee ---\n";
    std::unique_ptr<BeverageTemplate> coffee = std::make_unique<CoffeeMaker>();
    coffee->prepareBeverage();

    std::cout << "\n--- Brewing Tea ---\n";
    std::unique_ptr<BeverageTemplate> tea = std::make_unique<TeaMaker>();
    tea->prepareBeverage();

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Brewing Coffee ---
💧 Step 1: Boiling water...
🫘 Step 2: Brewing fine coffee beans...
☕ Step 3: Pouring into cup...
🥛 Step 4: Adding milk and sugar...
🎉 Beverage is ready!

--- Brewing Tea ---
💧 Step 1: Boiling water...
🍃 Step 2: Steeping tea leaves in water...
☕ Step 3: Pouring into cup...
🍋 Step 4: Adding lemon slices...
🎉 Beverage is ready!
```

---

## 23. Visitor Pattern
**Intent:** Represent an operation to be performed on the elements of an object structure. Visitor lets you define a new operation without changing the classes of the elements on which it operates.

### 🖼️ Visual Mental Image (The Real-World Analogy)
Think of a **Museum Tour Guide**:
- A museum houses different types of exhibits: **Paintings** and **Sculptures**.
- You want to perform operations on them (e.g., explain art history, clean dust).
- Instead of polluting the `Painting` and `Sculpture` classes with history lectures and cleaning logic, you create a **Tour Guide / Art Expert (Visitor)** object.
- The Visitor walks through the museum and performs specific visitor operations when visiting each exhibit.

```text
                       [ Visitor (Tour Guide) ]
                             /          \
                            v            v
                    visits /              \ visits
                          v                v
                 [ Painting ]            [ Sculpture ]
```

### 💻 Complete C++ Runnable Program
```cpp
#include <iostream>
#include <memory>
#include <vector>

class Painting;
class Sculpture;

// 1. Visitor Interface
class MuseumVisitor {
public:
    virtual ~MuseumVisitor() = default;
    virtual void visit(Painting& painting) = 0;
    virtual void visit(Sculpture& sculpture) = 0;
};

// 2. Element Interface
class MuseumElement {
public:
    virtual ~MuseumElement() = default;
    virtual void accept(MuseumVisitor& visitor) = 0;
};

// 3. Concrete Elements
class Painting : public MuseumElement {
public:
    void accept(MuseumVisitor& visitor) override {
        visitor.visit(*this); // Double dispatch
    }
    void showPainting() { std::cout << "🎨 Classic oil painting exhibit.\n"; }
};

class Sculpture : public MuseumElement {
public:
    void accept(MuseumVisitor& visitor) override {
        visitor.visit(*this); // Double dispatch
    }
    void showSculpture() { std::cout << "🗿 Renaissance marble sculpture exhibit.\n"; }
};

// 4. Concrete Visitor: Art Expert Tour Guide
class ArtExpert : public MuseumVisitor {
public:
    void visit(Painting& painting) override {
        painting.showPainting();
        std::cout << "   🗣️ Art Expert: Explaining Brushstroke techniques.\n";
    }

    void visit(Sculpture& sculpture) override {
        sculpture.showSculpture();
        std::cout << "   🗣️ Art Expert: Explaining Marble carving chisel angles.\n";
    }
};

// Client Code
int main() {
    std::cout << "--- Museum Exhibition Walkthrough ---\n";
    
    // Create elements list
    std::vector<std::shared_ptr<MuseumElement>> exhibits;
    exhibits.push_back(std::make_shared<Painting>());
    exhibits.push_back(std::make_shared<Sculpture>());

    // Visitor enters the museum
    ArtExpert guide;
    for (const auto& exhibit : exhibits) {
        exhibit->accept(guide);
    }

    return 0;
}
```

### 📋 Expected Console Output
```text
--- Museum Exhibition Walkthrough ---
🎨 Classic oil painting exhibit.
   🗣️ Art Expert: Explaining Brushstroke techniques.
🗿 Renaissance marble sculpture exhibit.
   🗣️ Art Expert: Explaining Marble carving chisel angles.
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
