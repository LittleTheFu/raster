#ifndef _FRAGMENT_SHADER_H_
#define _FRAGMENT_SHADER_H_

#include "light.h"
#include "texture.h"
#include "framebuffer.h"
#include "vertex.h"

class FragmentShader
{
public:
    FragmentShader(FrameBuffer& frameBuffer, const Light& light);
    void apply(const Vertex& vertex);

    void setTexture(const std::shared_ptr<Texture>& texture);

private:
    const Light& light_; // 光源对象
    std::shared_ptr<Texture> texture_; // 纹理对象

    FrameBuffer& frameBuffer_; // 帧缓冲区对象
};

#endif