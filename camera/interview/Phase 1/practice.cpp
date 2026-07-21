#include <iostream>
#include <memory>
using namespace std;

class Camera {

  int sensor;

public:
  Camera(int sen = 0) : sensor(sen) {};

  void takePicture() { cout << "Picture Captured" << endl; }

  int getSensor() { return sensor; }
};

int main() {
  auto c1 = make_shared<Camera>(20);
  c1->takePicture();
  cout << endl;
  cout << c1->getSensor() << endl;
  cout << "size of c1 = " << sizeof(c1) << "cout is " << c1.use_count() << endl;

  auto c2 = c1;

  // 'sensor' is now null
  if (!c1) {
    cout << "'sensor' is now null (ownership moved)." << endl;
  }

  c2->takePicture();
  cout << endl;
  cout << c2->getSensor() << endl;
  cout << "size of c2 = " << sizeof(c2) << "cout is " << c2.use_count() << endl;
}