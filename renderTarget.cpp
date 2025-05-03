#include "renderTarget.h"

RenderTarget::RenderTarget(int width, int height)
    : frameBuffer(width, height), width(width), height(height)
{
}

const FrameBuffer &RenderTarget::getFrameBuffer() const
{
    return frameBuffer;
}

FrameBuffer &RenderTarget::getFrameBuffer()
{
    return frameBuffer;
}