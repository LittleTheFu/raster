#include "shadowMapCamera.h"

ShadowMapCamera::ShadowMapCamera(const Eigen::Vector3f &pos, const Eigen::Vector3f &target, const Eigen::Vector3f &up)
    : camera(pos, target, up), // 初始化相机
      zBuffer(width, height),   // 初始化深度缓冲区
      fragmentShader(zBuffer) // 初始化片段着色器
{
    ndcMatrix_ = Eigen::Matrix4f::Identity();

    // 设置齐次坐标的缩放和平移
    ndcMatrix_(0, 0) = 0.5f * width;  // x轴的缩放
    ndcMatrix_(1, 1) = 0.5f * height; // y轴的缩放
    ndcMatrix_(0, 3) = 0.5f * width;  // x轴的平移
    ndcMatrix_(1, 3) = 0.5f * height; // y轴的平移

    // y轴翻转的处理
    ndcMatrix_(1, 1) *= -1.0f;

    vertexShader.setViewProjectionMatrix(getViewProjectMatrix()); // 设置视图投影矩阵
}

void ShadowMapCamera::render(const VertexBuffer &vertexBuffer)
{
    zBuffer.clear(); // 清空深度缓冲区

    auto it = vertexBuffer.getVertices().begin();
    const auto end = vertexBuffer.getVertices().end();

    while (std::distance(it, end) >= 3)
    {
        Vertex v0 = getScreenVertex(*it);
        Vertex v1 = getScreenVertex(*(it + 1));
        Vertex v2 = getScreenVertex(*(it + 2));

        drawTriangle(v0, v1, v2);

        std::advance(it, 3);
    }
}

Eigen::Matrix4f ShadowMapCamera::getViewProjectMatrix() const
{
    return camera.getProjectionMatrix() * camera.getViewMatrix(); // 返回投影矩阵和视图矩阵的乘积
}

Vertex ShadowMapCamera::getScreenVertex(const Vertex &vertex) const
{
    Vertex vertexNdc = vertexShader.apply(vertex); // 应用顶点着色器
    vertexNdc.position /= vertexNdc.position.w();
    vertexNdc.position = ndcMatrix_ * vertexNdc.position; // 转换到NDC坐标系

    return vertexNdc; // 返回x, y, z坐标
}

Eigen::Matrix4f ShadowMapCamera::getNDCMatrix() const
{
    return ndcMatrix_; // 返回NDC矩阵
}

bool ShadowMapCamera::testZBuffer(const Eigen::Vector3f &pos) const
{
    int x = static_cast<int>(pos.x());
    int y = static_cast<int>(pos.y());
    float z = pos.z();

    return zBuffer.test(x, y, z); // 测试深度缓冲区
}

void ShadowMapCamera::drawTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2)
{
    // 对顶点按 y 坐标排序
    std::array<Vertex, 3> vertices = {v0, v1, v2};
    std::sort(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b)
              { return a.position.y() < b.position.y(); });

    const Vertex &top = vertices[0];
    const Vertex &middle = vertices[1];
    const Vertex &bottom = vertices[2];

    for (int y = static_cast<int>(top.position.y()); y <= static_cast<int>(bottom.position.y()); ++y)
    {
        Vertex leftVertex, rightVertex;
        float t_segment; // 插值比例

        if (y <= middle.position.y())
        {
            float y_top_mid = middle.position.y() - top.position.y();
            if (std::abs(y_top_mid) < 1e-6)
                t_segment = 0.0f;
            else
                t_segment = (y - top.position.y()) / y_top_mid;
            leftVertex = top.interpolate(middle, t_segment);

            float y_top_bottom = bottom.position.y() - top.position.y();
            if (std::abs(y_top_bottom) < 1e-6)
                t_segment = 0.0f;
            else
                t_segment = (y - top.position.y()) / y_top_bottom;
            rightVertex = top.interpolate(bottom, t_segment);
        }
        else
        {
            float y_mid_bottom = bottom.position.y() - middle.position.y();
            if (std::abs(y_mid_bottom) < 1e-6)
                t_segment = 0.0f;
            else
                t_segment = (y - middle.position.y()) / y_mid_bottom;
            leftVertex = middle.interpolate(bottom, t_segment);

            float y_top_bottom = bottom.position.y() - top.position.y();
            if (std::abs(y_top_bottom) < 1e-6)
                t_segment = 0.0f;
            else
                t_segment = (y - top.position.y()) / y_top_bottom;
            rightVertex = top.interpolate(bottom, t_segment);
        }

        if (leftVertex.position.x() > rightVertex.position.x())
        {
            std::swap(leftVertex, rightVertex);
        }

        for (int x = static_cast<int>(leftVertex.position.x()); x <= static_cast<int>(rightVertex.position.x()); ++x)
        {
            float alpha = (x - leftVertex.position.x()) / (rightVertex.position.x() - leftVertex.position.x());

            if (alpha < 0.0f || alpha > 1.0f || std::isnan(alpha))
            {
                continue;
            }

            Vertex interpolatedVertex = leftVertex.interpolate(rightVertex, alpha);
            interpolatedVertex.position.x() = static_cast<float>(x);
            interpolatedVertex.position.y() = static_cast<float>(y);
            interpolatedVertex.position.w() = 1.0f;

            fragmentShader.apply(interpolatedVertex); // 应用片段着色器
        }
    }
}