---
The Adapter Design Pattern is a structural design pattern that allows objects
with incompatible interfaces to collaborate. Think of it exactly like a physical
power adapter: it sits between an electrical wall outlet and your laptop
charger, converting one interface into another so they can work together without
changing either original device.

The Code Problem vs. Adapter SolutionThe Problem: Incompatible Data or
FrameworksImagine your application processes data using JSON. You need to
integrate a third-party analytics library, but it only accepts data in XML
format. You cannot rewrite your application to use XML, and you cannot edit the
third-party library's source code to accept JSON.

The Solution: The Adapter
WrapperYou create an intermediate class (the Adapter) that implements your
application's expected interface but holds a reference to the third-party
object. When your application calls the adapter, the adapter transforms the data
behind the scenes and hands it to the third-party service.Core ComponentsClient:
The existing system that contains your application's business logic.Target /
Client Interface: The standard interface or protocol that your client expects to
use.Adaptee: The incompatible third-party or legacy class that you want to
reuse.Adapter: A class that implements the Target interface and wraps around the
Adaptee, translating calls between them.Simple Code Implementation (Java)Here is
a simple example showing how a modern computer (Client) that uses USB-C can
connect to an old projector (Adaptee) that only accepts VGA, using an Adapter
---

```java

// 1. Target Interface (What the Client expects)
interface UsbCable {
    void plugAndPlay();
}

// 2. Adaptee (The incompatible third-party/legacy class)
class VgaProjector {
    public void projectVideo() {
        System.out.println("Projecting video via legacy VGA connection.");
    }
}

// 3. Adapter (Implements Target, wraps Adaptee)
class VgaToUsbAdapter implements UsbCable {
    private final VgaProjector legacyProjector;

    public VgaToUsbAdapter(VgaProjector projector) {
        this.legacyProjector = projector;
    }

    @Override
    public void plugAndPlay() {
        System.out.println("Adapter converting USB-C signal to VGA...");
        // Translating the call to the adaptee's specific method
        legacyProjector.projectVideo();
    }
}

// 4. Client / Main Execution
public class Main {
    public static void main(String[] args) {
        // We have an old projector
        VgaProjector oldProjector = new VgaProjector();

        // We wrap it in our adapter so it looks like a modern USB device
        UsbCable adapter = new VgaToUsbAdapter(oldProjector);

        // The client interacts only with the clean, modern interface
        System.out.println("Client plugging in device:");
        adapter.plugAndPlay();
    }
}

Client plugging in device:
Adapter converting USB-C signal to VGA...
Projecting video via legacy VGA connection.

Key Benefits & Trade-offs
Advantages Single Responsibility Principle:

Separates the data conversion layer from your primary business logic.
Open/Closed Principle: You can introduce new types of adapters without
breaking existing client code.
Disadvantages

Increased Code Complexity: Introduces new interfaces and classes to your
codebase.Performance Overhead: In rare cases, extensive
data transformations inside the adapter can slow execution.


```c++
In C++, we implement the target interface using an abstract base class with a
pure virtual function (virtual void ... = 0). We also manage memory cleanly
using object composition and pass values explicitly.


#include <iostream>
#include <string>
using namespace std;

// 1. Target Interface (What the Client expects)
class UsbCable {
public:
  // Virtual destructor is critical for interface classes to prevent memory
  // leaks
  virtual ~UsbCable() = default;

  // Pure virtual function
  virtual void plugAndPlay() = 0;
};

// 2. Adaptee (The incompatible third-party/legacy class)
class VgaProjector {
public:
  void projectVideo() {
    std::cout << "Projecting video via legacy VGA connection." << std::endl;
  }
};

// 3. Adapter (Implements Target, wraps Adaptee)
class VgaToUsbAdapter : public UsbCable {
private:
  VgaProjector *legacyProjector; // Pointer to the incompatible object

public:
  // Constructor accepts a pointer to the legacy object
  VgaToUsbAdapter(VgaProjector *projector) : legacyProjector(projector) {}

  // Overriding the target interface method
  void plugAndPlay() override {
    std::cout << "Adapter converting USB-C signal to VGA..." << std::endl;

    // Translating the call to the adaptee's specific method
    legacyProjector->projectVideo();
  }
};

// 4. Client / Main Execution
int main() {
  // We have an old projector instance
  VgaProjector oldProjector;

  // We wrap it in our adapter so it matches the expected UsbCable interface
  UsbCable *adapter = new VgaToUsbAdapter(&oldProjector);

  // The client interacts only with the clean, modern target interface
  std::cout << "Client plugging in device:" << std::endl;
  adapter->plugAndPlay();

  // Clean up dynamic memory allocation
  delete adapter;

  return 0;
}
