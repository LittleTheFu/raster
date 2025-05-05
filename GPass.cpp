#include "GPass.h"
#include "CommonFS.h"
#include "CommonVS.h"

GPass::GPass(int width, int height) : Pass(width, height)
{
    // Initialize GBufferData with the size of the frame buffer
    gBufferData_ = std::make_shared<GBufferData>(width, height); // Example size, replace with actual frame buffer size

    vertexShader_ = std::make_unique<CommonVS>();
    fragmentShader_ = std::make_unique<CommonFS>();

    fragmentShader_->setWidth(width);
    fragmentShader_->setHeight(height);
    fragmentShader_->setGBufferData(gBufferData_); // Set GBuffer data to fragment shader
}

void GPass::preRun()
{
    gBufferData_->clear(); // Clear GBuffer data before rendering
}

const std::shared_ptr<GBufferData> &GPass::getGBufferData() const
{
    return gBufferData_;
}