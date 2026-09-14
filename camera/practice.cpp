#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

mutex mtx;
vector<int> frame;

void producer() {
  unique_lock(mtx);
  frame.push_back(1);
}

void consumer() {
  unique_lock(mtx);
  frame.pop_back();
}

int main() {
  thread p1(producer);
  thread c1(consumer);

  p1.join();
  c1.join();
}