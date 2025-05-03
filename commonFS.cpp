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

    float z = vertex.position.z();
    Eigen::Vector3f worldPos = vertex.worldPosition.head<3>();
    Eigen::Vector3f normal = vertex.normal;

    gBufferData_->worldPositionBuffer.setBuffer(x, y, worldPos);
    gBufferData_->normalBuffer.setBuffer(x, y, normal);
    gBufferData_->zBuffer.testAndUpdate(x, y, z); // 设置深度缓冲区
}

void CommonFS::setGBufferData(const std::shared_ptr<GBufferData>& gBufferData)
{
    gBufferData_ = gBufferData; // 设置GBuffer数据
}