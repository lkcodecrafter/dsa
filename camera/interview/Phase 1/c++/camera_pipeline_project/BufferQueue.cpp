#include "BufferQueue.h"

void BufferQueue::push(Frame* frame) {

    unique_lock<mutex> lock(mtx);

    frameQueue.push(frame);

    cout << "[BufferQueue] Frame "
         << frame->frameId
         << " pushed into queue\n";

    cv.notify_one();
}

Frame* BufferQueue::pop() {

    unique_lock<mutex> lock(mtx);

    while (frameQueue.empty()) {

        cv.wait(lock);
    }

    Frame* frame = frameQueue.front();

    frameQueue.pop();

    cout << "[BufferQueue] Frame "
         << frame->frameId
         << " popped from queue\n";

    return frame;
}
