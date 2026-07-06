
### Part 1: Abstract Method vs. Abstract Factory

| Feature | Abstract Method (Language Concept) | Abstract Factory (Design Pattern) |
| :--- | :--- | :--- |
| **What is it?** | A **language feature** (Object-Oriented Programming construct). In C++, this is called a **pure virtual function** (e.g., `virtual void paint() = 0;`). | A **creational design pattern** (architectural solution). |
| **Purpose** | Defines a contract/interface. It forces child classes to implement that specific function. | Provides a way to create families of related objects (e.g., buttons, textboxes, checkboxes) without specifying their concrete classes. |
| **Relationship** | An Abstract Factory class will *contain* abstract methods to define how products are created. | The Abstract Factory pattern *uses* abstract methods to achieve its goal. |

---

### Part 2: Factory Method vs. Abstract Factory
*(Note: "Abstract method" is frequently confused/typo-ed with the **Factory Method** pattern).*

* **Factory Method:** Focuses on creating **only one** type of product (e.g., a `ShapeFactory` creates a `Circle` **or** a `Square`). It relies on inheritance (subclasses override a method to decide which object to instantiate).
* **Abstract Factory:** Focuses on creating **a family** of related products (e.g., `UIFactory` creates a `Button` **and** a `Checkbox` **and** a `Window` that all match the same OS theme). It relies on object composition.

---

### Part 3: How we are creating "families of objects"

The current code in the file under "Abstract Factory" only creates a single `Button` and does not actually implement the pattern. 

To create a **family of objects**, you group related products (e.g., Windows OS widgets vs. Mac OS widgets) together under a unified Factory interface. Here is how it works:

#### C++ Correct Abstract Factory Example
```cpp
#include <iostream>
using namespace std;

// === 1. Abstract Products ===
class Button { public: virtual void paint() = 0; };
class Checkbox { public: virtual void render() = 0; };

// === 2. Windows Product Family ===
class WinButton : public Button { 
public: 
    void paint() override { cout << "Windows Button\n"; } 
};
class WinCheckbox : public Checkbox { 
public: 
    void render() override { cout << "Windows Checkbox\n"; } 
};

// === 3. Mac Product Family ===
class MacButton : public Button { 
public: 
    void paint() override { cout << "Mac Button\n"; } 
};
class MacCheckbox : public Checkbox { 
public: 
    void render() override { cout << "Mac Checkbox\n"; } 
};

// === 4. Abstract Factory ===
class UIFactory {
public:
    virtual Button* createButton() = 0;     // Abstract Method
    virtual Checkbox* createCheckbox() = 0; // Abstract Method
};

// === 5. Concrete Factories ===
class WinFactory : public UIFactory {
public:
    Button* createButton() override { return new WinButton(); }
    Checkbox* createCheckbox() override { return new WinCheckbox(); }
};

class MacFactory : public UIFactory {
public:
    Button* createButton() override { return new MacButton(); }
    Checkbox* createCheckbox() override { return new MacCheckbox(); }
};

// === Client Code ===
void runApplication(UIFactory* factory) {
    // The client doesn't know (or care) if it's using Windows or Mac objects.
    // It just knows it gets a matching family of UI elements!
    Button* btn = factory->createButton();
    Checkbox* chk = factory->createCheckbox();
    
    btn->paint();
    chk->render();
}

int main() {
    // Creating Windows family
    UIFactory* winFactory = new WinFactory();
    runApplication(winFactory); // Output: Windows Button, Windows Checkbox
    
    // Creating Mac family
    UIFactory* macFactory = new MacFactory();
    runApplication(macFactory); // Output: Mac Button, Mac Checkbox
}
```

### Why is this called "creating families of objects"?
If you use `WinFactory`, you are guaranteed to get a `WinButton` **and** a `WinCheckbox`. You cannot accidentally mix a `MacButton` with a `WinCheckbox` because the factory controls the creation of the entire family together.