#include "pass.h"

Pass::Pass(int width, int height)
    : width_(width), height_(height),
      projectionMatrix_(Eigen::Matrix4f::Identity()),
      ndcMatrix_(Eigen::Matrix4f::Identity())
{
    calculateNDCMatrix(); // 计算NDC矩阵
}

void Pass::setMvpMatrix(const Eigen::Matrix4f &projectionMatrix)
{
    projectionMatrix_ = projectionMatrix;

    if(vertexShader_)
    {
        vertexShader_->setMvpMatrix(projectionMatrix_);
    }
}

void Pass::calculateNDCMatrix()
{
    ndcMatrix_ = Eigen::Matrix4f::Identity();

    // 设置齐次坐标的缩放和平移
    ndcMatrix_(0, 0) = 0.5f * width_;  // x轴的缩放
    ndcMatrix_(1, 1) = 0.5f * height_; // y轴的缩放
    ndcMatrix_(0, 3) = 0.5f * width_;  // x轴的平移
    ndcMatrix_(1, 3) = 0.5f * height_; // y轴的平移

    // y轴翻转的处理
    ndcMatrix_(1, 1) *= -1.0f;
}

Vertex Pass::getScreenVertex(const Vertex &vertex, bool &isIn)
{
    if(!vertexShader_)
    {
        return vertex; // 如果没有设置顶点着色器，则直接返回原始顶点
    }

    Vertex vertexNdc = vertexShader_->apply(vertex); // 应用顶点着色器
    vertexNdc.position /= vertexNdc.position.w();

    isIn = isInNdcCube(vertexNdc);
    vertexNdc.position = ndcMatrix_ * vertexNdc.position; // 转换到NDC坐标系

    return vertexNdc; // 返回x, y, z坐标
}

void Pass::preRun()
{
}

void Pass::run(const VertexBuffer &vertexBuffer)
{
    preRun(); // 渲染前的准备工作

    auto it = vertexBuffer.getVertices().begin();
    const auto end = vertexBuffer.getVertices().end();

    while (std::distance(it, end) >= 3)
    {
        bool isIn0 = true;
        bool isIn1 = true;
        bool isin2 = true;

        Vertex v0 = getScreenVertex(*it, isIn0);
        Vertex v1 = getScreenVertex(*(it + 1), isIn1);
        Vertex v2 = getScreenVertex(*(it + 2), isin2);

        // if(!isCompletelyOutsideScreen(v0, v1, v2))
        if(isIn0 || isIn1 || isin2)
        {
            drawScreenTriangle(v0, v1, v2); // 绘制屏幕三角形
        }

        std::advance(it, 3);
    }
}

void Pass::setLight(const std::shared_ptr<Light> &light)
{
}

void Pass::setGBufferData(const std::shared_ptr<GBufferData> &gBufferData)
{
}

void Pass::setEyePosition(const Eigen::Vector3f &eyePosition)
{
}

void Pass::setTexture(const std::shared_ptr<Texture> &texture)
{
}

void Pass::setShadowZBuffer(const std::shared_ptr<ZBuffer> &zBuffer)
{
}

void Pass::setShadowMapMvpMatrix(const Eigen::Matrix4f &shadowMapMvpMatrix)
{
}

void Pass::setShadowMapNDCMatrix(const Eigen::Matrix4f &shadowMapNDCMatrix)
{
}

const Eigen::Matrix4f& Pass::getNDCMatrix() const
{
    return ndcMatrix_;
}

const Eigen::Matrix4f& Pass::getMvpMatrix() const
{
    return projectionMatrix_;
}

bool Pass::isInNdcCube(const Vertex &vertex) const
{
    bool isInX = (vertex.position.x() >= -1.0f && vertex.position.x() <= 1.0f);
    bool isInY = (vertex.position.y() >= -1.0f && vertex.position.y() <= 1.0f);
    bool isInZ = (vertex.position.z() >= -1.0f && vertex.position.z() <= 1.0f);

    return isInX && isInY && isInZ;
}

bool Pass::isCompletelyOutsideScreen(const Vertex &v0, const Vertex &v1, const Vertex &v2)
{
    float x_min = std::min(v0.position.x(), std::min(v1.position.x(), v2.position.x()));
    float x_max = std::max(v0.position.x(), std::max(v1.position.x(), v2.position.x()));

    if (x_min >= width_ || x_max < 0) {
        return true;
    }

    float y_min = std::min(v0.position.y(), std::min(v1.position.y(), v2.position.y()));
    float y_max = std::max(v0.position.y(), std::max(v1.position.y(), v2.position.y()));

    if (y_min >= height_ || y_max < 0) {
        return true;
    }

    return false;
    
    // bool isOutside_0 = (v0.position.x() < 0 || v0.position.x() >= width_ || v0.position.y() < 0 || v0.position.y() >= height_);
    // bool isOutside_1 = (v1.position.x() < 0 || v1.position.x() >= width_ || v1.position.y() < 0 || v1.position.y() >= height_);
    // bool isOutside_2 = (v2.position.x() < 0 || v2.position.x() >= width_ || v2.position.y() < 0 || v2.position.y() >= height_);

    // return isOutside_0 && isOutside_1 && isOutside_2;
}

void Pass::setShadowMapCamera(const std::shared_ptr<ShadowMapCamera> camera)
{

}

void Pass::setShadowMapZBuffers(std::array<std::shared_ptr<ZBuffer>, ShadowMapCamera::NUM> zBuffers)
{

}


void Pass::drawScreenTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2)
{
    if (!fragmentShader_)
    {
        return; // 如果没有设置片段着色器，则直接返回
    }

    // 对顶点按 y 坐标排序
    std::array<Vertex, 3> vertices = {v0, v1, v2};
    std::sort(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b)
              { return a.position.y() < b.position.y(); });

    const Vertex &top = vertices[0];
    const Vertex &middle = vertices[1];
    const Vertex &bottom = vertices[2];

    for (int y = static_cast<int>(top.position.y()); y <= static_cast<int>(bottom.position.y()); ++y)
    {
        if( y < 0 || y >= height_)
            continue;

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
            if(x < 0 || x >= width_)
                continue;

            float alpha = (x - leftVertex.position.x()) / (rightVertex.position.x() - leftVertex.position.x());

            if (alpha < 0.0f || alpha > 1.0f || std::isnan(alpha))
            {
                continue;
            }

            Vertex interpolatedVertex = leftVertex.interpolate(rightVertex, alpha);
            interpolatedVertex.position.x() = static_cast<float>(x);
            interpolatedVertex.position.y() = static_cast<float>(y);
            interpolatedVertex.position.w() = 1.0f;

            fragmentShader_->apply(interpolatedVertex); // 应用片段着色器
        }
    }
}