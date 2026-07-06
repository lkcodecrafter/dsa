#pragma once

#include "BufferQueue.h"

class CameraHAL {

private:

    BufferQueue* queue;

public:

    CameraHAL(BufferQueue* q);

    void captureFrames();
};
