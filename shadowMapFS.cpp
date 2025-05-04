#include "shadowMapFS.h"

void ShadowMapFS::setZBuffer(std::shared_ptr<ZBuffer> zBuffer)
{
    zBuffer_ = zBuffer;
}

void ShadowMapFS::apply(const Vertex &vertex)
{
    if (!zBuffer_)
    {
        return; // 如果没有深度缓冲区对象，直接返回
    }

    // 将顶点坐标转换为整数坐标
    int x = static_cast<int>(vertex.position.x());
    int y = static_cast<int>(vertex.position.y());
    float depth = vertex.position.z();

    if (x < 0 || x >= zBuffer_->width() ||
        y < 0 || y >= zBuffer_->height())
    {
        return; // 超出范围，返回
    }

    zBuffer_->testAndUpdate(x, y, depth);
}