#ifndef _RENDER_TARGET_H_
#define _RENDER_TARGET_H_

#include "frameBuffer.h"


class RenderTarget {
public:
    RenderTarget(int width, int height);

    const FrameBuffer& getFrameBuffer() const;
    FrameBuffer& getFrameBuffer();
    
private:
    FrameBuffer frameBuffer;
    int width;
    int height;
};

#endif // _RENDER_TARGET_H_