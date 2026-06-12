#include <iostream>
#include <thread>

#include "CameraHAL.h"
#include "CameraService.h"

using namespace std;

int main() {

    BufferQueue queue;

    CameraHAL hal(&queue);

    CameraService service(&queue);

    thread halThread(
        &CameraHAL::captureFrames,
        &hal);

    thread serviceThread(
        &CameraService::processFrames,
        &service);

    halThread.join();

    serviceThread.join();

    cout << "\n===== Camera Pipeline Finished =====\n";

    return 0;
}
