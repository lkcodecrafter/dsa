#include "CameraService.h"

#include <thread>
#include <chrono>

using namespace std;

CameraService::CameraService(BufferQueue* q) {

    queue = q;
}

void CameraService::processFrames() {

    for (int i = 1; i <= 5; i++) {

        Frame* frame = queue->pop();

        cout << "[CameraService] Processing Frame "
             << frame->frameId
             << endl;

        cout << "[CameraService] Buffer Address = "
             << static_cast<void*>(frame->buffer)
             << endl;

        this_thread::sleep_for(
            chrono::milliseconds(1000));

        delete frame;
    }
}
