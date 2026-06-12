#include "CameraHAL.h"

#include <thread>
#include <chrono>

using namespace std;

CameraHAL::CameraHAL(BufferQueue* q) {

    queue = q;
}

void CameraHAL::captureFrames() {

    for (int i = 1; i <= 5; i++) {

        Frame* frame = new Frame(i, 1024);

        cout << "[CameraHAL] Captured Frame "
             << frame->frameId
             << endl;

        queue->push(frame);

        this_thread::sleep_for(
            chrono::milliseconds(500));
    }
}
