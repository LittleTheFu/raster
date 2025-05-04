#include "shadowPass.h"

#include "shadowMapVS.h"
#include "shadowMapFS.h"

ShadowPass::ShadowPass(int width, int height)
    : Pass(width, height)
{
    zBuffer = std::make_shared<ZBuffer>(width, height);

    vertexShader_ = std::make_unique<ShadowMapVS>();
    fragmentShader_ = std::make_unique<ShadowMapFS>();

    fragmentShader_->setShadowZBuffer(zBuffer);
}

void ShadowPass::preRun()
{
    zBuffer->clear();
}

const std::shared_ptr<ZBuffer> &ShadowPass::getZBuffer() const
{
    return zBuffer;
}