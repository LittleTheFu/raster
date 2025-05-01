#ifndef _FRAGMENT_SHADER_H_
#define _FRAGMENT_SHADER_H_

#include "light.h"
#include "texture.h"
#include "framebuffer.h"
#include "vertex.h"

class FragmentShader
{
public:
    FragmentShader(FrameBuffer& frameBuffer, const Light& light, const Texture& texture);
    void apply(const Vertex& vertex);

private:
    Light light_; // 光源对象
    Texture texture_; // 纹理对象

    FrameBuffer& frameBuffer_; // 帧缓冲区对象
};

#endif