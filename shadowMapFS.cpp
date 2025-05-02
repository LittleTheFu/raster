#include "shadowMapFS.h"

ShadowMapFS::ShadowMapFS(ZBuffer &zBuffer)
    : zBuffer_(zBuffer) // 初始化深度缓冲区对象
{
}

void ShadowMapFS::apply(const Vertex &vertex)
{
    int x = static_cast<int>(vertex.position.x());
    int y = static_cast<int>(vertex.position.y());
    float depth = vertex.position.z();

    if (x < 0 || x >= zBuffer_.width() ||
        y < 0 || y >= zBuffer_.height())
    {
        return; // 超出范围，返回
    }

    zBuffer_.testAndUpdate(x, y, depth);
}