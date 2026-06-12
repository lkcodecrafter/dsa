#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Frame.h"

using namespace std;

class BufferQueue {

private:

    queue<Frame*> frameQueue;

    mutex mtx;

    condition_variable cv;

public:

    void push(Frame* frame);

    Frame* pop();
};
