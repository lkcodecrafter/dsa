#include <iostream>
using namespace std;

class Camera {

public:
  virtual void name() = 0;
};

class SubCam : public Camera {};

/*

Reuse existing functionality.

*/

int main() {
  SubCam sc;
  sc.name();
}
