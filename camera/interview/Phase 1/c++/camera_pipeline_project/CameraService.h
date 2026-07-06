#pragma once

#include "BufferQueue.h"

class CameraService {

private:

    BufferQueue* queue;

public:

    CameraService(BufferQueue* q);

    void processFrames();
};
