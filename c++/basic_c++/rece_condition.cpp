#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

int counter = 0;    
mutex counter_mutex;
atomic<int> atomic_counter{0};

void unsync_increment(){
    for(int i = 0; i < 10000; ++i){
        // no synchronization: this causes a race condition
        counter++;
    }
}

void mutex_increment(){
    for(int i = 0; i < 10000; ++i){
        // protect increments with a mutex
        lock_guard<mutex> lock(counter_mutex);
        counter++;
    }
}

void atomic_increment(){
    for(int i = 0; i < 10000; ++i){
        // atomic increment is thread-safe without a separate mutex
        atomic_counter++;
    }
}

int main(){
    // 1) Unsynchronized: demonstrates the race condition
    counter = 0;
    thread t1(unsync_increment);
    thread t2(unsync_increment);
    t1.join();
    t2.join();
    cout << "Unsynchronized counter (race condition) = " << counter << endl;

    // 2) Mutex-protected: fixes the race by serializing access
    counter = 0;
    thread t3(mutex_increment);
    thread t4(mutex_increment);
    t3.join();
    t4.join();
    cout << "Mutex-protected counter = " << counter << endl;

    // 3) Atomic: another correct and often faster fix
    atomic_counter = 0;
    thread t5(atomic_increment);
    thread t6(atomic_increment);
    t5.join();
    t6.join();
    cout << "Atomic counter = " << atomic_counter.load() << endl;

    return 0;
}



/*

I updated your file rece_condition.cpp to a small demo that:

First shows the race condition (two threads incrementing a plain int without sync).
Then fixes it with a mutex (using lock_guard).
Finally shows a correct alternative using std::atomic<int>.
Why the race happens (brief): counter++ is not atomic — it reads the value, increments it, then writes it back. When two threads interleave those steps, increments can be lost.

How to compile & run (PowerShell):

With MinGW/GCC: .\g++ -std=c++11 .\rece_condition.cpp -o .\rece_condition.exe -pthread .\rece_condition.exe
With MSVC (Developer Command Prompt / Visual Studio tools): cl /EHsc rece_condition.cpp rece_condition.exe
Expected result (example):

Unsynchronized counter (race condition) = (likely less than 20000)
Mutex-protected counter = 20000
Atomic counter = 20000
If you want, I can:

Explain lock_guard and std::mutex in more detail,
Show variations with more threads or iterations,
Add timings to compare mutex vs atomic performance. Which would you like next?



#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

int counter =0;
mutex mtx;
void increment(){
    for(int i=0;i<10000;i++){
        mtx.lock();
        counter++;
        mtx.unlock();
    }
}

int main(){
thread t1(increment);
thread t2(increment);
t1.join();
t2.join();
cout<<"Counter: "<<counter<<endl;
return 0;

// output Counter: 20000
}

*/