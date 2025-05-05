#include "baseFS.h"

void BaseFS::setGBufferData(const std::shared_ptr<GBufferData> &gBufferData)
{
}

void BaseFS::setLight(const std::shared_ptr<Light> &light)
{
}

void BaseFS::setColorBuffer(std::shared_ptr<ColorBuffer> &colorBuffer)
{
}

void BaseFS::setViewDir(const Eigen::Vector3f &viewDir)
{
}

void BaseFS::setEyePosition(const Eigen::Vector3f &eyePosition)
{
}

void BaseFS::setTexture(const std::shared_ptr<Texture> &texture)
{
}

void BaseFS::setShadowMapMvpMatrix(const Eigen::Matrix4f &shadowMapMvpMatrix)
{ 
}

void BaseFS::setShadowMapNDCMatrix(const Eigen::Matrix4f &shadowMapNDCMatrix)
{ 
}

void BaseFS::setShadowZBuffer(const std::shared_ptr<ZBuffer> &zBuffer)
{ 
}

void BaseFS::setWidth(int width)
{ 
}

void BaseFS::setHeight(int height)
{ 
}