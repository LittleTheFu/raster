#include "scene.h"
#include "triangle.h"

Scene::Scene()
    : camera(Eigen::Vector3f(0.0f, 0.0f, -50.0f), // position
             Eigen::Vector3f(0.0f, 0.0f, 1.0f),   // target
             Eigen::Vector3f(0.0f, 1.0f, 0.0f)),  // up
      pipeline(800, 600)                          // 假设屏幕大小为800x600
{
    // 其他初始化代码
    triangle.setVertex(0, Eigen::Vector4f(0, 0, 10, 1.0f));
    triangle.setVertex(1, Eigen::Vector4f(-10, -20, 10, 1.0f));
    triangle.setVertex(2, Eigen::Vector4f(30, 10, 10, 1.0f));
}

std::array<Eigen::Vector3f, 3> Scene::getTriangleScreenCoords()
{
    static int count = 0;
    count += 1;
    count %= 1000000;

    // 使用整数除法确保 count / 10 取整数部分
    // float scaleFactor = abs(sin(count * 0.0001f));
    // float scale = 1 + scaleFactor;

    std::array<Eigen::Vector3f, 3> screenCoords;

    Eigen::Matrix4f viewMatrix = camera.getViewMatrix().inverse();
    Eigen::Matrix4f projectionMatrix = camera.getProjectionMatrix();

    pipeline.setModelMatrix(Eigen::Matrix4f::Identity()); // 模型矩阵为单位矩阵
    pipeline.setViewMatrix(viewMatrix);
    pipeline.setProjectionMatrix(projectionMatrix);

    screenCoords[0] = pipeline.getScreenCoords(triangle.vertex(0));
    screenCoords[1] = pipeline.getScreenCoords(triangle.vertex(1));
    screenCoords[2] = pipeline.getScreenCoords(triangle.vertex(2));

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
