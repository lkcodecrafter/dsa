#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

void print_patter1() {
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= i; j++) {
      cout << j << " ";
    }
    cout << endl;
  }

  // Output
  // 1
  // 1 2
  // 1 2 3
  // 1 2 3 4
}

void print_patter2() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cout << i << " ";
    }
    cout << endl;
  }

  // Output
  // 0 0 0 0
  // 1 1 1 1
  // 2 2 2 2
  // 3 3 3 3
}

void print_pattern_3() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cout << j << " ";
    }
    cout << endl;
  }

  // Output
  // 0 1 2 3
  // 0 1 2 3
  // 0 1 2 3
  // 0 1 2 3
}

void print_pattern_4() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cout << j + 1;
    }
    cout << endl;
  }

  // Output
  // 1 2 3 4
  // 1 2 3 4
  // 1 2 3 4
  // 1 2 3 4
}

void print_pattern_5() {

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cout << 4 - j;
    }
    cout << endl;
  }

  // Output
  // 4 3 2 1
  // 4 3 2 1
  // 4 3 2 1
  // 4 3 2 1
}

int main() {
  print_patter1();
  print_patter2();
  print_pattern_3();
  return 0;
}