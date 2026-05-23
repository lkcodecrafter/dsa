#include <iostream>
#include <pthread.h>

using namespace std;

/*

1. Mutex

A Mutex (Mutual Exclusion) is a lock mechanism.

Only one thread can access the critical section at a time.


pthread_mutex_t mutex;
pthread_mutex_lock(&mutext);

//critical section
ptread_mutex_unlock(&mutex);

Why Mutex Needed?

Without mutex:
Two threads may modify same data together.

This causes:
Race Condition

*/

