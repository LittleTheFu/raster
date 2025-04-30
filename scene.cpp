#include "scene.h"
#include "triangle.h"

Scene::Scene()
    : camera(Eigen::Vector3f(0.0f, 0.0f, -50.0f), // position
             Eigen::Vector3f(0.0f, 0.0f, 1.0f),  // target
             Eigen::Vector3f(0.0f, 1.0f, 0.0f))  // up
{
    // 其他初始化代码
    triangle.setVertex(0, Eigen::Vector4f(-5, -5, 10, 1.0f));
    triangle.setVertex(1, Eigen::Vector4f(5, -5, 10, 1.0f));
    triangle.setVertex(2, Eigen::Vector4f(0, 5, 10, 1.0f));
}

std::array<Eigen::Vector3f, 3> Scene::getTriangleScreenCoords() const
{
    static int count = 0;
    count += 1;
    count %= 1000000;

    // 使用整数除法确保 count / 10 取整数部分
    float scaleFactor = abs(sin(count * 0.0001f));
    float scale = scaleFactor;
    // float scale = 1;

    std::array<Eigen::Vector3f, 3> screenCoords;

    Eigen::Matrix4f viewMatrix = camera.getViewMatrix().inverse();
    Eigen::Matrix4f projectionMatrix = camera.getProjectionMatrix();

    Eigen::Vector4f v0 = triangle.vertex(0);
    v0 *= scale; // 缩放
    v0.w() = 1.0f; // 齐次坐标
    v0 = viewMatrix * v0; // 先变换到视图空间
    v0 = projectionMatrix * v0;
    v0 /= v0.w(); // 齐次除法
    // Eigen::Vector3f ndc0(v0.x(), v0.y(), v0.z());
    screenCoords[0] = ndcToScreen(v0, 800, 600); // 假设屏幕大小为800x600

    Eigen::Vector4f v1 = triangle.vertex(1);
    v1 *= scale;
    v1.w() = 1.0f;
    v1 = viewMatrix * v1; // 先变换到视图空间
    v1 = projectionMatrix * v1;
    v1 /= v1.w(); // 齐次除法
    // Eigen::Vector3f ndc1(v1.x(), v1.y(), v1.z());
    screenCoords[1] = ndcToScreen(v1, 800, 600); // 假设屏幕大小为800x600

    Eigen::Vector4f v2 = triangle.vertex(2);
    v2 *= scale;
    v2.w() = 1.0f;
    v2 = viewMatrix * v2; // 先变换到视图空间
    v2 = projectionMatrix * v2;
    v2 /= v2.w(); // 齐次除法
    // Eigen::Vector3f ndc2(v2.x(), v2.y(), v2.z());
    screenCoords[2] = ndcToScreen(v2, 800, 600); // 假设屏幕大小为800x600

    return screenCoords;
}

Eigen::Vector3f Scene::ndcToScreen(const Eigen::Vector4f &ndc, int screenWidth, int screenHeight) const
{
    // 构造一个 4x4 的矩阵来处理 NDC 到屏幕坐标的转换
    Eigen::Matrix4f screenMatrix = Eigen::Matrix4f::Identity();

    // 设置齐次坐标的缩放和平移
    screenMatrix(0, 0) = 0.5f * screenWidth;  // x轴的缩放
    screenMatrix(1, 1) = 0.5f * screenHeight; // y轴的缩放
    screenMatrix(0, 3) = 0.5f * screenWidth;  // x轴的平移
    screenMatrix(1, 3) = 0.5f * screenHeight; // y轴的平移

    // y轴翻转的处理
    screenMatrix(1, 1) *= -1.0f;

    // 将 NDC 转换为屏幕坐标
    Eigen::Vector4f screenCoord = screenMatrix * ndc;  // 进行变换

    // 返回最终的屏幕坐标，只返回 x, y, z 作为 3D 坐标
    return Eigen::Vector3f(screenCoord.x(), screenCoord.y(), screenCoord.z());
}

