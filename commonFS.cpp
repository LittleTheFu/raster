#include "commonFS.h"

void CommonFS::apply(const Vertex &vertex)
{
    if (!gBufferData_)
    {
        return; // GBuffer数据未设置，直接返回
    }

    // 设置GBuffer数据
    int x = static_cast<int>(vertex.position.x());
    int y = static_cast<int>(vertex.position.y());

    if(x < 0 || x >= gBufferData_->width_ || y < 0 || y >= gBufferData_->height_)
    {
        return; // 顶点位置超出GBuffer范围，直接返回
    }


    float z = vertex.position.z();

    if (!gBufferData_->zBuffer.test(x, y, z))
    {
        return; // 深度测试失败，直接返回
    }
    
    Eigen::Vector3f worldPos = vertex.worldPosition.head<3>();
    Eigen::Vector3f normal = vertex.normal;
    Eigen::Vector2f uv = vertex.texCoord;
    Eigen::Vector3f color = vertex.color;

    gBufferData_->worldPositionBuffer.setBuffer(x, y, worldPos);
    gBufferData_->normalBuffer.setBuffer(x, y, normal);
    gBufferData_->colorBuffer.setBuffer(x, y, color);
    gBufferData_->zBuffer.testAndUpdate(x, y, z); // 设置深度缓冲区
    gBufferData_->uvBuffer.setBuffer(x, y, uv);
}

void CommonFS::setGBufferData(const std::shared_ptr<GBufferData>& gBufferData)
{
    gBufferData_ = gBufferData; // 设置GBuffer数据
}

void CommonFS::setWidth(int width)
{
    width_ = width;
}

void CommonFS::setHeight(int height)
{
    height_ = height;
}