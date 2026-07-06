
#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

queue<string> eventsQ;
mutex mtx;
bool done = false;

void producer() {
  for (int i = 1; i <= 10; i++) {
    {
      lock_guard<mutex> lock(mtx);
      eventsQ.push("Event_" + to_string(i));
    }
    this_thread::sleep_for(chrono::milliseconds(100)); // Why used this ?
  }
  done = true;
}

void consumer() {
  while (!done || !eventsQ.empty()) {
    lock_guard<mutex> lock(mtx);
    if (!eventsQ.empty()) {
      cout << "Processed: " << eventsQ.front() << endl;
      eventsQ.pop();
    }
  }
}

int main() {
  thread t1(producer);
  thread t2(consumer);

  t1.join();
  t2.join();

  return 0;
}
