
## 4. Builder
**Intent:** Build complex object step by step.

### C++
```cpp
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
