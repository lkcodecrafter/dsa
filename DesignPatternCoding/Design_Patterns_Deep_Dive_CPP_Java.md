
# 🎯 Design Patterns – Deep Dive (C++ & Java)
### With Dry Runs • ASCII Diagrams • Interview Q&A • Android / Camera HAL Use-Cases

Made specially for **daily learning (One Pattern / Day)** and **interview mastery**.

---

## 🧠 How to Use This File
✔ Read **Intent**
✔ See **ASCII Diagram**
✔ Understand **Dry Run**
✔ Practice **C++ & Java Code**
✔ Learn **Interview Answers**
✔ Relate to **Real Android / Camera HAL usage**

---

# 🟢 DAY 1 – SINGLETON PATTERN

## ✅ Intent
Ensure **only one instance** of a class exists and provide a global access point.

---

## 📊 ASCII Diagram
```
+------------------+
|   Singleton      |
|------------------|
| static instance  |
| getInstance()    |
+------------------+
```

---

## 🔁 Dry Run
1. `getInstance()` called
2. instance == null → create object
3. return same instance every time

---

## 💻 C++ Code
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

## ☕ Java Code
```java
class Singleton {
    private static Singleton instance;

    private Singleton() {}

    public static Singleton getInstance() {
        if (instance == null)
            instance = new Singleton();
        return instance;
    }
}
```

---

## 🎤 Interview Q&A
**Q:** Why Singleton is dangerous?  
**A:** Global state, hard to test, threading issues

---

## 📱 Android / Camera HAL Usage
- CameraService
- SensorManager
- Logger
- HAL global context

---

# 🟢 DAY 2 – FACTORY METHOD PATTERN

## ✅ Intent
Create objects **without exposing creation logic**.

---

## 📊 ASCII Diagram
```
Creator ---> Factory ---> Product
```

---

## 🔁 Dry Run
Client → Factory → Concrete object returned

---

## 💻 C++ Code
```cpp
class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() { cout << "Circle"; }
};

class ShapeFactory {
public:
    static Shape* create() {
        return new Circle();
    }
};

int main(){
  ShapeFactory::create()->draw();  
}

// output 
// Circle
```

---

## ☕ Java Code
```java
interface Shape {
    void draw();
}

class Circle implements Shape {
    public void draw() {
        System.out.println("Circle");
    }
}

class ShapeFactory {
    static Shape create() {
        return new Circle();
    }
}
```

---

## 🎤 Interview Q&A
**Q:** Difference between Factory & Abstract Factory?  
**A:** Factory → one product  
Abstract Factory → family of products

---

## 📱 Android / Camera HAL Usage
- Codec creation
- Camera session pipelines
- Buffer allocators

---

# 🟢 DAY 3 – OBSERVER PATTERN

## ✅ Intent
One-to-many dependency → auto notify observers

---

## 📊 ASCII Diagram
```
Subject ---> Observer1
        ---> Observer2
```

---

## 💻 C++ Code
```cpp
class Observer {
public:
    virtual void update() = 0;
};
```

---

## ☕ Java Code
```java
interface Observer {
    void update();
}
```

---

## 🎤 Interview Q&A
**Q:** Where used in Android?  
**A:** LiveData, RxJava, callbacks

---

## 📱 Camera HAL Usage
- Auto-exposure updates
- Frame metadata listeners

---

# 🟢 DAY 4 – STRATEGY PATTERN

## ✅ Intent
Switch algorithms **at runtime**

---

## 📊 ASCII Diagram
```
Context ---> StrategyA
        ---> StrategyB
```

---

## 💻 C++ Code
```cpp
class Strategy {
public:
    virtual int execute(int a, int b) = 0;
};
```

---

## ☕ Java Code
```java
interface Strategy {
    int execute(int a, int b);
}
```

---

## 📱 Android Usage
- Image processing modes
- Compression strategies

---

# 🟢 DAY 5 – COMMAND PATTERN

## Intent
Encapsulate request as object

---

## 📱 Android Usage
- Button clicks
- Camera capture requests

---

# 🟢 DAY 6 – STATE PATTERN

## Intent
Change behavior based on state

---

## 📱 Camera HAL Usage
- IDLE → PREVIEW → CAPTURE

---

# 🟢 DAY 7 – DECORATOR PATTERN

## Intent
Add behavior dynamically

---

## 📱 Android Usage
- Image filters
- UI themes

---

# 🟢 DAY 8 – FACADE PATTERN

## Intent
Simplified interface

---

## 📱 Camera HAL Usage
- CameraManager → hides HAL complexity

---

# 🟢 DAY 9 – ADAPTER PATTERN

## Intent
Convert incompatible interfaces

---

## 📱 Android Usage
- Legacy camera → Camera2

---

# 🟢 DAY 10 – TEMPLATE METHOD

## Intent
Define algorithm skeleton

---

## 📱 Android Usage
- Activity lifecycle

---

# 🟢 DAY 11 – VISITOR PATTERN

## Intent
Separate algorithm from object

---

## 📱 Usage
- AST parsing
- Compiler design

---

# 🟢 DAY 12 – PROXY PATTERN

## Intent
Control access

---

## 📱 Android Usage
- Binder IPC
- Lazy loading

---

# 🏁 FINAL INTERVIEW MASTER TIP
> Always answer as:  
> **Intent → Diagram → Example → Tradeoff**

---

Made with ❤️ for **Lalit Kumar**
