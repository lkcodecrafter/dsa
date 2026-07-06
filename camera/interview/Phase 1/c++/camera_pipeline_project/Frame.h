#pragma once

#include <iostream>

using namespace std;

struct Frame {

    int frameId;
    char* buffer;
    int size;

    Frame(int id, int s) {

        frameId = id;
        size = s;

        buffer = new char[size];

        cout << "[Frame] Allocated Buffer for Frame "
             << frameId << endl;
    }

    ~Frame() {

        delete[] buffer;

        cout << "[Frame] Released Buffer for Frame "
             << frameId << endl;
    }
};
