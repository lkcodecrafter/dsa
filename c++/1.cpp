// 1. EvenOrOddOrNaturalNumbers Function Analysis

#include <bits/stdc++.h>
#include <thread>
#include <mutex>

using namespace std;

pthread_mutex_t l1;
pthread_mutex_t l2;

void EvenOrOddOrNaturalNumbers(int n) {

    pthread_mutex_init(&l1, NULL);
    pthread_mutex_init(&l2, NULL);

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            pthread_mutex_lock(&l1);
            cout << "Even: " << i << endl;
            pthread_mutex_unlock(&l1);
        } else if (i % 2 == 1) {
            pthread_mutex_lock(&l2);
            cout << "Odd: " << i << endl;
            pthread_mutex_unlock(&l2);
        } else {
            cout << "Natural: " << i << endl;
        }
    }
}

// Why we used mutex locks here?
// In this function, we are printing even and odd numbers. 
// If we have multiple threads calling this function, there could be a race condition where two threads might 
// try to print even or odd numbers at the same time, leading to interleaved output.
// By using mutex locks (l1 for even numbers and l2 for odd numbers), we ensure that only one thread can print even numbers 
// at a time and only one thread can print odd numbers at a time, thus preventing interleaved output and ensuring thread safety.
// Note: The "Natural" case will never be executed because every integer is either even or odd.

// Give example of how multiple threads can call this function and how mutex locks will help in that case?
// Example: Suppose we have two threads, Thread A and Thread B, both calling the EvenOrOddOrNaturalNumbers function with n = 10.
// Thread A might start executing and print "Even: 0", then Thread B might start executing and print "Odd: 1".
// If there were no mutex locks, the output could be interleaved like this:
// Even: 0
// Odd: 1
// Even: 2
// Odd: 3
// However, with mutex locks in place, the output will be more organized:
// Thread A will acquire l1 lock and print even numbers:
// Thread B will acquire l2 lock and print odd numbers:
// Even: 0
// Even: 2
// Odd: 1
// Odd: 3
// Even: 4
// Odd: 5
// Even: 6
// Odd: 7
// Even: 8
// Odd: 9

// what is the diff between mutex locks and semaphores?
// Mutex locks and semaphores are both synchronization primitives used to control access to shared resources in concurrent programming, but they have some key differences:
// 1. Mutex Locks: A mutex (short for "mutual exclusion") is a locking mechanism that allows only one thread to access a resource at a time. It is typically used to protect critical sections of code that access shared resources. A mutex can be locked and unlocked by the same thread, and it provides exclusive access to the resource it protects.
// 2. Semaphores: A semaphore is a signaling mechanism that can be used to control access to a resource that has a limited number of instances. A semaphore maintains a count that represents the number of available resources. Threads can acquire the semaphore (decrement
//  the count) to access the resource and release the semaphore (increment the count) when they are done. Semaphores can allow multiple threads to access a resource simultaneously, up to a specified limit, whereas mutex locks only allow one thread at a time.
// In summary, mutex locks are used for exclusive access to a resource, while semaphores can be used for controlling access to a resource with multiple instances.


int main(int argc, char const *argv[])
{
    EvenOrOddOrNaturalNumbers(5); // still not able to understand the use of mutex locks here, as we are not creating multiple threads to call this function.
    // To see the effect of mutex locks, we would need to create multiple threads that call this function simultaneously.
    // Example of creating multiple threads to call the EvenOrOddOrNaturalNumbers function:
    thread t1(EvenOrOddOrNaturalNumbers, 10);
    thread t2(EvenOrOddOrNaturalNumbers, 10);
    t1.join();
    t2.join();
    // In this example, we have two threads (t1 and t2) that are both calling the EvenOrOddOrNaturalNumbers function with n = 10.
    // The mutex locks will help ensure that the output from both threads is not interleaved and remains organized, as explained in the previous example.
    // Note: The output may still be interleaved if the threads are not properly synchronized, but the mutex locks will help reduce the chances of interleaving and ensure that the output is more organized.
    // In a real-world scenario, you would typically have more complex logic and shared resources that require synchronization, and the use of mutex locks would be more evident in those cases.
    // In this simple example, the use of mutex locks may not be necessary, but it serves as a demonstration of how to use mutex locks to control access to shared resources in a concurrent programming environment.
    // In conclusion, mutex locks are used to ensure that only one thread can access a resource at a time, while semaphores can allow multiple threads to access a resource simultaneously up to a specified limit. 
    //The use of mutex locks in the EvenOrOddOrNaturalNumbers function helps to prevent interleaved output when multiple threads are calling the function simultaneously, ensuring that the output remains organized and thread-safe.

    // We have used 2 threads, still i'm not able to understand the use of mutex locks here, as we are not creating multiple threads to call this function.
    // To see the effect of mutex locks, we would need to create multiple threads that call this function simultaneously.
    // Example of creating multiple threads to call the EvenOrOddOrNaturalNumbers function:
    thread t3(EvenOrOddOrNaturalNumbers, 10);
    thread t4(EvenOrOddOrNaturalNumbers, 10);
    t3.join();
    t4.join();
    return 0;
}
// please visualize the output of this code when we have multiple threads calling the EvenOrOddOrNaturalNumbers function simultaneously, and how mutex locks will help in that case.
// When multiple threads are calling the EvenOrOddOrNaturalNumbers function simultaneously, the output can be interleaved if there are no mutex locks in place. For example, if we have two threads (Thread A and Thread B) both calling the function with n = 10, the output could look like this without mutex locks:
// Even: 0
// Odd: 1
// Even: 2
// Odd: 3
// Even: 4  
// Odd: 5
// Even: 6
// Odd: 7
// Even: 8
// Odd: 9
// However, with mutex locks in place, the output will be more organized and less interleaved. For example, if Thread A acquires the l1 lock to print even numbers and Thread B acquires the l2 lock to print odd numbers, the output could look like this:
// Even: 0
// Even: 2
// Even: 4
// Even: 6
// Even: 8
// Odd: 1
// Odd: 3
// Odd: 5
// Odd: 7
// Odd: 9   

 


void EvenOrOdd(int n) {

    pthread_mutex_init(&l1, NULL);
    pthread_mutex_init(&l2, NULL);

    int i = 0;

    while(i <= n) {

        if(i % 2 == 0) {

            pthread_mutex_lock(&l1);

            cout << i << " Even Number" << endl;

            pthread_mutex_unlock(&l1);
        }
        else {

            pthread_mutex_lock(&l2);

            cout << i << " Odd Number" << endl;

            pthread_mutex_unlock(&l2);
        }

        i++;
    }

    pthread_mutex_destroy(&l1);
    pthread_mutex_destroy(&l2);
}

/*
Why Mutex Used?

Mutex prevents:

Race condition
Multiple threads printing together
Shared resource corruption

*/