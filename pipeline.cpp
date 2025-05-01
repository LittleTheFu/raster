#include "pipeline.h"

Pipeline::Pipeline(int width, int height, FrameBuffer& frameBuffer, const Light& light, const Texture& texture)
      : fragmentShader_(frameBuffer, light, texture) // 初始化片段着色器
{
    screenWidth_ = width;
    screenHeight_ = height;

    // 初始化模型矩阵、视图矩阵和投影矩阵
    modelMatrix_ = Eigen::Matrix4f::Identity();
    viewMatrix_ = Eigen::Matrix4f::Identity();
    projectionMatrix_ = Eigen::Matrix4f::Identity();
    mvpMatrix_ = Eigen::Matrix4f::Identity();

    calculateNDCMatrix(); // 计算NDC矩阵

    isDirty_ = true; // 初始时需要更新MVP矩阵
}

void Pipeline::setModelMatrix(const Eigen::Matrix4f& modelMatrix)
{
    vertexShader_.setModelMatrix(modelMatrix); // 设置模型矩阵
}

void Pipeline::setViewMatrix(const Eigen::Matrix4f& viewMatrix)
{
    vertexShader_.setViewMatrix(viewMatrix); // 设置视图矩阵
}

void Pipeline::setProjectionMatrix(const Eigen::Matrix4f& projectionMatrix)
{
    vertexShader_.setProjectionMatrix(projectionMatrix);
}

Vertex Pipeline::getScreenVertex(const Vertex &vertex)
{
    Vertex vertexNdc = vertexShader_.apply(vertex); // 应用顶点着色器
    vertexNdc.position /= vertexNdc.position.w();
    vertexNdc.position = ndcMatrix_ * vertexNdc.position; // 转换到NDC坐标系

    return vertexNdc; // 返回x, y, z坐标
}

void Pipeline::drawScreenTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2)
{
    // 对顶点按 y 坐标排序，确保 v0 是顶部，v2 是底部
    std::array<Vertex, 3> vertices = {v0, v1, v2};

    std::sort(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b)
              {
                  return a.position.y() < b.position.y(); // 从上到下排序
              });

    // 获取排序后的顶点
    const Vertex &top = vertices[0];
    const Vertex &middle = vertices[1];
    const Vertex &bottom = vertices[2];

    // 扫描线填充算法
    for (int y = static_cast<int>(top.position.y() ); y <= static_cast<int>(bottom.position.y()); ++y)
    {
        // 计算当前扫描线的左右交点
        float leftX = 0.0f, rightX = 0.0f;
        Vertex leftVertex, rightVertex;

        // 对于扫描线在顶点与中间点之间
        if (y <= middle.position.y())
        {
            // 计算与 top 和 middle 之间的交点
            leftVertex = interpolateVertex(top, middle, y);
            rightVertex = interpolateVertex(top, bottom, y);
        }
        else
        {
            // 计算与 middle 和 bottom 之间的交点
            leftVertex = interpolateVertex(middle, bottom, y);
            rightVertex = interpolateVertex(top, bottom, y);
        }

        // 对交点进行排序，以确保从左到右绘制
        if (leftVertex.position.x() > rightVertex.position.x())
        {
            std::swap(leftVertex, rightVertex);
        }

        // 在当前扫描线填充颜色
        for (int x = static_cast<int>(leftVertex.position.x() + 0.5f); x <= static_cast<int>(rightVertex.position.x() + 0.5f); ++x)
        {
            // 使用左右交点的颜色进行插值
            float alpha = (x - leftVertex.position.x()) / (rightVertex.position.x() - leftVertex.position.x());

            if( alpha < 0 || alpha > 1 || std::isnan(alpha))
            {
                // fragmentShader_.apply(leftVertex); // 如果alpha不在[0,1]范围内，跳过
                continue; // 如果alpha不在[0,1]范围内，跳过
            }

            Eigen::Vector3f interpolatedColor = (1 - alpha) * leftVertex.color + alpha * rightVertex.color;
            // 插值世界坐标
            Eigen::Vector3f interpolatedWorldPosition = (1 - alpha) * leftVertex.worldPosition + alpha * rightVertex.worldPosition;
            // 插值纹理坐标
            Eigen::Vector2f interpolatedTexCoord = (1 - alpha) * leftVertex.texCoord + alpha * rightVertex.texCoord;
            // 插值法线
            Eigen::Vector3f interpolatedNormal = (1 - alpha) * leftVertex.normal + alpha * rightVertex.normal;
            // 插值Z
            float interpolatedZ = (1 - alpha) * leftVertex.position.z() + alpha * rightVertex.position.z(); // 插值 z 值
            // 插值视线方向
            Eigen::Vector3f interpolatedViewDir = (1 - alpha) * leftVertex.viewDir + alpha * rightVertex.viewDir;

            Eigen::Vector4f interpolatedPosition{static_cast<float>(x), static_cast<float>(y), interpolatedZ, 1.0f}; // 插值位置
            Vertex interpolatedVertex{interpolatedPosition, interpolatedColor, interpolatedTexCoord, interpolatedNormal, interpolatedViewDir, interpolatedWorldPosition};

            fragmentShader_.apply(interpolatedVertex);
        }
    }
}

Vertex Pipeline::interpolateVertex(const Vertex &v0, const Vertex &v1, int y) const
{
    Vertex result;

    // 计算插值比例t
    float t = (y - v0.position.y()) / (v1.position.y() - v0.position.y());

    if(t < 0 || t > 1)
    {
        result = v0; // 如果t不在[0,1]范围内，直接返回v0
        return result;
    }

    // 插值世界坐标
    result.worldPosition = (1 - t) * v0.worldPosition + t * v1.worldPosition;

    // 插值视线方向
    result.viewDir = (1 - t) * v0.viewDir + t * v1.viewDir;
    result.viewDir.normalize(); // 确保视线方向归一化

    // 插值位置
    result.position.x() = v0.position.x() + t * (v1.position.x() - v0.position.x());
    result.position.y() = y;  // 固定y
    result.position.z() = v0.position.z() + t * (v1.position.z() - v0.position.z());
    result.position.w() = 1.0f;  // 假设使用齐次坐标

    // 插值颜色
    result.color = (1 - t) * v0.color + t * v1.color;

    // 插值纹理坐标
    result.texCoord = (1 - t) * v0.texCoord + t * v1.texCoord;

    // 插值法线
    result.normal = (1 - t) * v0.normal + t * v1.normal;

    return result;
}

void Pipeline::calculateNDCMatrix()
{
    ndcMatrix_ = Eigen::Matrix4f::Identity();

    // 设置齐次坐标的缩放和平移
    ndcMatrix_(0, 0) = 0.5f * screenWidth_;  // x轴的缩放
    ndcMatrix_(1, 1) = 0.5f * screenHeight_; // y轴的缩放
    ndcMatrix_(0, 3) = 0.5f * screenWidth_;  // x轴的平移
    ndcMatrix_(1, 3) = 0.5f * screenHeight_; // y轴的平移

    // y轴翻转的处理
    ndcMatrix_(1, 1) *= -1.0f;
}