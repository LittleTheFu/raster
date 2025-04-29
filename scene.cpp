#include "scene.h"
#include "triangle.h"

Scene::Scene()
    : camera(Eigen::Vector3f(0.0f, 0.0f, -5.0f), // position
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
    count %= 765;

    float scale = 0.002f * count;

    std::array<Eigen::Vector3f, 3> screenCoords;

    Eigen::Matrix4f viewMatrix = camera.getViewMatrix().inverse();
    Eigen::Matrix4f projectionMatrix = camera.getProjectionMatrix();

    Triangle::Vec4 v0 = triangle.vertex(0);
    v0 *= scale; // 缩放
    v0.w() = 1.0f; // 齐次坐标
    v0 = viewMatrix * v0; // 先变换到视图空间
    v0 = projectionMatrix * v0;
    v0 /= v0.w(); // 齐次除法
    Eigen::Vector3f ndc0(v0.x(), v0.y(), v0.z());
    screenCoords[0] = ndcToScreen(ndc0, 800, 600); // 假设屏幕大小为800x600

    Triangle::Vec4 v1 = triangle.vertex(1);
    v1 *= scale;
    v1.w() = 1.0f;
    v1 = viewMatrix * v1; // 先变换到视图空间
    v1 = projectionMatrix * v1;
    v1 /= v1.w(); // 齐次除法
    Eigen::Vector3f ndc1(v1.x(), v1.y(), v1.z());
    screenCoords[1] = ndcToScreen(ndc1, 800, 600); // 假设屏幕大小为800x600

    Triangle::Vec4 v2 = triangle.vertex(2);
    v2 *= scale;
    v2.w() = 1.0f;
    v2 = viewMatrix * v2; // 先变换到视图空间
    v2 = projectionMatrix * v2;
    v2 /= v2.w(); // 齐次除法
    Eigen::Vector3f ndc2(v2.x(), v2.y(), v2.z());
    screenCoords[2] = ndcToScreen(ndc2, 800, 600); // 假设屏幕大小为800x600

    return screenCoords;
}

Eigen::Vector3f Scene::ndcToScreen(const Eigen::Vector3f &ndc, int screenWidth, int screenHeight) const
{
    // 从 NDC 到屏幕坐标的变换
    float x_screen = (ndc.x() + 1.0f) * 0.5f * screenWidth;
    float y_screen = (1.0f - ndc.y()) * 0.5f * screenHeight; // y轴反转
    float z_screen = ndc.z();                                // z值通常保持不变，或者按需要进行调整

    return Eigen::Vector3f(x_screen, y_screen, z_screen);
}
